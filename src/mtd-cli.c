/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli.c - Make Tax Digital CLI
 *
 * Copyright (C) 2020 - 2025	Andrew Clayton <ac@sigsgev.uk>
 */

#define _GNU_SOURCE	/* asprintf(3) */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

#include <libmtdac/mtd.h>

#include "mtd-cli.h"
#include "endpoints.h"

#define PROD_NAME	"mtd-cli"

#define MTD_CLI		"mtd-cli"

#define MAX_ARGV	7

#define EP_MAP_ENT(ep)	{ .api = #ep, .endpoint = &ep##_endpoint }

static const struct api_ep {
	const char *api;
	const struct _endpoint *endpoint;
} api_ep_map[] = {
	EP_MAP_ENT(bd),
	EP_MAP_ENT(biss),
	EP_MAP_ENT(bsas),
	EP_MAP_ENT(cisd),
	EP_MAP_ENT(ical),
	EP_MAP_ENT(id),
	EP_MAP_ENT(idi),
	EP_MAP_ENT(ie),
	EP_MAP_ENT(iei),
	EP_MAP_ENT(ifi),
	EP_MAP_ENT(iipi),
	EP_MAP_ENT(ilos),
	EP_MAP_ENT(ioi),
	EP_MAP_ENT(ipi),
	EP_MAP_ENT(isb),
	EP_MAP_ENT(isi),
	EP_MAP_ENT(ob),
	EP_MAP_ENT(pb),
	EP_MAP_ENT(saa),
	EP_MAP_ENT(saass),
	EP_MAP_ENT(said),
	EP_MAP_ENT(seb),

	EP_MAP_ENT(vat),

	EP_MAP_ENT(test_cu),
	EP_MAP_ENT(test_fph),
	EP_MAP_ENT(test_sa),

	{ }
};

enum error {
	ERR_UNKNOWN_CMD = 1001,
	ERR_IGNORE,
};

static int print_api_help(void)
{
	const struct api_ep *ep = api_ep_map;

	printf("Available APIs :-\n\n");
	printf("init init-creds init-oauth init-nino");

	for ( ; ep->api != NULL; ep++)
		printf(" %s", ep->api);
	printf("\n");

	return -1;
}

static char *gen_query_string(const char *src, char *dst, size_t len)
{
	char *ptr = dst;
	size_t i = 1;

	*(dst++) = '?';
	while (*src && i++ < len - 1) {
		if (*src == ',')
			*dst = '&';
		else
			*dst = *src;
		src++;
		dst++;
	}
	*dst = '\0';

	return ptr;
}

static int check_args(int argc, char *argv[], const char *api,
		      const struct _endpoint *ep)
{
	int i = 0;
	const char *name = argv[0];
	const struct endpoint *eps = ep->endpoints;

	if (!name)
		goto out_help;

	for ( ; eps[i].name != NULL; i++) {
		if (strcmp(eps[i].name, name) != 0)
			continue;

		if (argc >= eps[i].nr_req_args && *argv[argc] != '?')
			return 0;

		printf("Usage: %s %s %s %s\n", MTD_CLI, api, eps[i].name,
		       eps[i].args);

		return ERR_IGNORE;
	}

out_help:
	printf("Available %s endpoints :-\n\n%s\n", ep->api_name, ep->cmds);

	return ERR_IGNORE;
}

static int do_api_func(const struct endpoint *ep, int argc, char *argv[],
		       char **buf)
{
	int i;
	const char *args[MAX_ARGV] = {};
	const struct endpoint *eps = ep;
	char *ptr;
	char qs[129];

	for (i = 0; i < argc && i < MAX_ARGV; i++) {
		ptr = argv[i + 1];

		/* format the query string if provided */
		if (strchr(ptr, '=')) {
			gen_query_string(ptr, qs, sizeof(qs));
			ptr = qs;
		}

		args[i] = ptr;
	}

	for ( ; eps->name != NULL; eps++) {
		struct mtd_dsrc_ctx dsctx;

		if (strcmp(eps->name, argv[0]) != 0)
			continue;

		if (eps->file_data) {
			dsctx.data_src.file = args[0];
			dsctx.src_type = MTD_DATA_SRC_FILE;
		}

		return mtd_ep(eps->api_ep, eps->file_data ? &dsctx : NULL, buf,
			      args + eps->file_data);
	}

	/* I don't think we can ever reach here... */
	return 0;
}

static int do_mtd_api(const char *name, int argc, char *argv[])
{
	char *buf = NULL;
	const struct api_ep *apis = api_ep_map;
	int err = ERR_UNKNOWN_CMD;

	for ( ; apis->api != NULL; apis++) {
		const struct _endpoint *ep = apis->endpoint;

		if (strcmp(apis->api, name) != 0)
			continue;

		err = check_args(argc, argv, apis->api, ep);
		if (err)
			return err;
		err = do_api_func(ep->endpoints, argc, argv, &buf);

		break;
	}

	if (!buf)
		return err;

	printf("%s\n", buf);
	free(buf);

	return err;
}

static int init_creds(int argc, char *argv[])
{
	int err;
	enum mtd_api_scope api = MTD_API_SCOPE_ADD;

	if (argc == 0)
		goto out_usage;

	if (strcmp(argv[0], "itsa") == 0)
		api |= MTD_API_SCOPE_SA;
	else if (strcmp(argv[0], "itsa-assist") == 0)
		api |= MTD_API_SCOPE_SAASS;
	else if (strcmp(argv[0], "vat") == 0)
		api |= MTD_API_SCOPE_VAT;
	else
		goto out_usage;

	err = mtd_init_creds(api);
	if (err)
		return err;

	return 0;

out_usage:
	printf("Usage: mtd-cli init-creds itsa|itsa-assist|vat\n");
	return ERR_IGNORE;
}

#define ITSA_SCOPES		(MTD_SCOPE_RD_SA|MTD_SCOPE_WR_SA)
#define ITSA_ASSIST_SCOPES	(MTD_SCOPE_RD_SAASS|MTD_SCOPE_WR_SAASS)
#define VAT_SCOPES		(MTD_SCOPE_RD_VAT|MTD_SCOPE_WR_VAT)
static int init_auth(int argc, char *argv[])
{
	int err;
	enum mtd_scope scopes;
	enum mtd_api_scope api = MTD_API_SCOPE_ADD;

	if (argc == 0)
		goto out_usage;

	if (strcmp(argv[0], "itsa") == 0) {
		scopes = ITSA_SCOPES;
		api |= MTD_API_SCOPE_SA;
	} else if (strcmp(argv[0], "itsa-assist") == 0) {
		scopes = ITSA_ASSIST_SCOPES;
		api |= MTD_API_SCOPE_SAASS;
	} else if (strcmp(argv[0], "vat") == 0) {
		scopes = VAT_SCOPES;
		api |= MTD_API_SCOPE_VAT;
	} else {
		goto out_usage;
	}

	err = mtd_init_auth(api, scopes);
	if (err)
		return err;

	return 0;

out_usage:
	printf("Usage: mtd-cli init-auth itsa|itsa-assist|vat\n");
	return ERR_IGNORE;
}

static int do_init_all(int argc, char *argv[])
{
	int err;
	char *api = argv[0];

	if (argc == 0)
		goto out_usage;

	if (strcmp(api, "itsa") != 0 && strcmp(api, "itsa-assist") != 0 &&
	    strcmp(api, "vat") != 0)
		goto out_usage;

	printf("Initialising...\n\n");
	err = init_creds(1, (char *[1]){api});
	if (err)
		return err;

	if (strcmp(api, "itsa") == 0) {
		printf("\n");
		err = mtd_init_nino();
		if (err)
			return err;
	}

	printf("\n");
	err = init_auth(1, (char *[1]){api});
	if (err)
		return err;

	printf("\nInitialisation complete. Re-run command if something looks "
	       "wrong.\n");

	return 0;

out_usage:
	printf("Usage: mtd-cli init itsa|itsa-assist|vat\n");
	return ERR_IGNORE;
}

#define IS_API(api)		(strcmp(api, ep) == 0)
static int dispatcher(int argc, char *argv[])
{
	const char *ep = argv[0];

	argc -= 1;
	argv++;

	if (IS_API("init"))
		return do_init_all(argc, argv);
	if (IS_API("init-oauth"))
		return init_auth(argc, argv);
	if (IS_API("init-creds"))
		return init_creds(argc, argv);
	if (IS_API("init-nino"))
		return mtd_init_nino();

	return do_mtd_api(ep, argc - 1, argv);
}

static char *set_ver_cli(void *user_data __attribute__((unused)))
{
	char *buf;
	char *encname;
	char *encver;
	int len;

	encname = mtd_percent_encode("mtd-cli", -1);
	encver = mtd_percent_encode(GIT_VERSION, -1);

	len = asprintf(&buf, "%s=%s", encname, encver);
	if (len == -1) {
		perror("asprintf");
		buf = NULL;
	}

	free(encname);
	free(encver);

	return buf;
}

static char *set_prod_name(void *user_data __attribute__((unused)))
{
	return strdup(PROD_NAME);
}

static const char *conf_dir(char *path)
{
	const char *home_dir = getenv("HOME");
	struct stat sb;
	int dfd;
	int err;

	snprintf(path, PATH_MAX, "%s/.config/mtd-cli", home_dir);
	dfd = open(home_dir, O_PATH|O_DIRECTORY);
	if (dfd == -1) {
		fprintf(stderr, "openat: Can't open %s\n", home_dir);
		exit(EXIT_FAILURE);
	}

	err = fstatat(dfd, ".config", &sb, 0);
	if (err)
		mkdirat(dfd, ".config", 0777);
	err = fstatat(dfd, ".config/mtd-cli", &sb, 0);
	if (err)
		mkdirat(dfd, ".config/mtd-cli", 0700);

	close(dfd);

	return path;
}

static const FILE *set_log_fp(const char *log_level)
{
	char *ptr;
	char *ptrm;
	const char *mode = "we";

	if (!log_level || !strchr(log_level, ':'))
		return NULL;

	ptr = strchr(log_level, ':');
	ptr++;

	ptrm = strchr(log_level, '+');
	if (!ptrm)
		goto out;

	*(ptrm++) = '\0';

	if (*ptrm != '\0' && *ptrm == 'a')
		mode = "ae";

out:
	return fopen(ptr, mode);
}

int main(int argc, char *argv[])
{
	int err;
	int ret = EXIT_SUCCESS;
	unsigned int flags = MTD_OPT_GLOBAL_INIT;
	char conf_dir_path[PATH_MAX];
	const char *snd_fph_hdrs = getenv("MTD_CLI_OPT_NO_FPH_HDRS");
	const char *log_level = getenv("MTD_CLI_OPT_LOG_LEVEL");
	const char *hdrs[2] = {};
	const struct mtd_fph_ops fph_ops = {
		.fph_version_cli = set_ver_cli,
		.fph_prod_name = set_prod_name
	};
	const struct mtd_cfg cfg = {
		.config_dir = conf_dir(conf_dir_path),
		.fph_ops = &fph_ops,
		.extra_hdrs = hdrs,
		.log_fp = set_log_fp(log_level)
	};

	if (argc == 1) {
		print_api_help();
		exit(EXIT_FAILURE);
	}

	if (snd_fph_hdrs && (*snd_fph_hdrs == 't' || *snd_fph_hdrs == '1'))
		flags |= MTD_OPT_NO_ANTI_FRAUD_HDRS;
	if (log_level && *log_level == 'd')
		flags |= MTD_OPT_LOG_DEBUG;
	else if (log_level && *log_level == 'i')
		flags |= MTD_OPT_LOG_INFO;

	/*
	 * Set any extra user supplied http headers.
	 *
	 * Currently just one header is supported which should be
	 * enough for adding a Gov-Test-Scenario header in the
	 * Test API.
	 *
	 * The underlying libmtdac supports however many you set
	 * in the array.
	 */
	hdrs[0] = getenv("MTD_CLI_HDRS");

	err = mtd_init(flags, &cfg);
	if (err)
		exit(EXIT_FAILURE);

	err = dispatcher(argc - 1, argv + 1);
	if (err) {
	       if (err == MTD_ERR_NEEDS_AUTHORISATION)
		       fprintf(stderr, "[Error] Please run 'mtd-cli oauth'\n");
	       else if (err == ERR_UNKNOWN_CMD)
		       print_api_help();
	       else if (err != ERR_IGNORE)
		       fprintf(stderr, "[Error] %s%s%s: %s\n", argv[1],
			       argc > 2 ? " " : "", argc > 2 ? argv[2] : "",
			       mtd_err2str(err));

	       ret = EXIT_FAILURE;
	}

	mtd_deinit();

	exit(ret);
}
