/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli.c - Make Tax Digital CLI
 *
 * Copyright (C) 2020           Andrew Clayton <andrew@digital-domain.net>
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <linux/limits.h>

#include <libmtdac/mtd.h>

#include <jansson.h>

#include "utils.h"
#include "mtd-cli.h"
#include "mtd-cli-sa.h"
#include "mtd-cli-saac.h"
#include "mtd-cli-ic.h"
#include "mtd-cli-il.h"
#include "mtd-cli-ni.h"
#include "mtd-cli-biss.h"
#include "mtd-cli-bsas.h"
#include "mtd-cli-test-cu.h"
#include "mtd-cli-test-ni.h"
#include "mtd-cli-test-fph.h"

#define MAX_ARGV	7

#define APIS		"init init-oauth init-config init-nino "\
			"sa saac ic il ni biss bsas "\
			"test-cu test-ni test-fph"

static const struct api_ep {
	const char *api;
	const struct _endpoint *endpoint;
} api_ep_map[] = {
	{
		.api = "sa",
		.endpoint = &sa_endpoint
	},
	{
		.api = "saac",
		.endpoint = &saac_endpoint
	},
	{
		.api = "ic",
		.endpoint = &ic_endpoint
	},
	{
		.api = "il",
		.endpoint = &il_endpoint
	},
	{
		.api = "ni",
		.endpoint = &ni_endpoint
	},
	{
		.api = "biss",
		.endpoint = &biss_endpoint
	},
	{
		.api = "bsas",
		.endpoint = &bsas_endpoint
	},
	{
		.api = "test-cu",
		.endpoint = &test_cu_endpoint
	},
	{
		.api = "test-ni",
		.endpoint = &test_ni_endpoint
	},
	{
		.api = "test-fph",
		.endpoint = &test_fph_endpoint
	},
	{ NULL, NULL }
};

enum error {
	ERR_UNKNOWN_CMD = 1001,
};

static int print_api_help(void)
{
	printf("Available APIs :-\n\n%s\n", APIS);

	return -1;
}

int check_args(int argc, char *argv[], const struct _endpoint *ep)
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

		printf("Usage: %s\n", eps[i].use);

		return -1;
	}

out_help:
	printf("Available %s endpoints :-\n\n%s\n", ep->api_name, ep->cmds);

	return -1;
}

int do_api_func(const struct endpoint *ep, int argc, char *argv[], char **buf)
{
	int i;
	const char *args[MAX_ARGV] = { NULL };
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

	for (i = 0; ep[i].name != NULL; i++) {
		if (strcmp(ep[i].name, argv[0]) != 0)
			continue;

		switch (ep[i].func) {
		case FUNC_0:
			return ep[i].api_func.func_0(buf);
		case FUNC_1:
			return ep[i].api_func.func_1(args[0], buf);
		case FUNC_2:
			return ep[i].api_func.func_2(args[0], args[1], buf);
		case FUNC_3:
			return ep[i].api_func.func_3(args[0], args[1], args[2],
						     buf);
		case FUNC_4:
			return ep[i].api_func.func_4(args[0], args[1], args[2],
						     args[3], buf);
		}
	}

	return -1;
}

static int do_mtd_api(const char *name, int argc, char *argv[])
{
	char *buf = NULL;
	json_t *rootbuf;
	int i = 0;
	int err = ERR_UNKNOWN_CMD;

	for ( ; api_ep_map[i].api != NULL; i++) {
		const struct _endpoint *ep = api_ep_map[i].endpoint;

		if (strcmp(api_ep_map[i].api, name) != 0)
			continue;

		err = check_args(argc, argv, ep);
		if (err)
			return err;
		err = do_api_func(ep->endpoints, argc, argv, &buf);

		break;
	}

	if (!buf)
		return err;

	rootbuf = json_loads(buf, 0, NULL);
	json_dumpf(rootbuf, stdout, JSON_INDENT(4));
	printf("\n");
	json_decref(rootbuf);

	free(buf);

	return err;
}

static int do_init_nino(void)
{
	return mtd_init_nino();
}

static int do_init_config(void)
{
	return mtd_init_config();
}

static int do_init_oauth(void)
{
	return mtd_init_auth();
}

static int do_init(void)
{
	int err;

	printf("Initialising...\n\n");
	err = mtd_init_config();
	if (err)
		return err;

	printf("\n");
	err = mtd_init_nino();
	if (err)
		return err;

	printf("\n");
	err = mtd_init_auth();
	if (err)
		return err;

	printf("\nInitialisation complete. Re-run command if something looks "
	       "wrong.\n");

	return 0;
}


#define IS_API(api)		(strcmp(api, ep) == 0)
static int dispatcher(int argc, char *argv[])
{
	const char *ep = argv[0];
	int err = -1;

	if (IS_API("init"))
		err = do_init();
	else if (IS_API("init-oauth"))
		err = do_init_oauth();
	else if (IS_API("init-config"))
		err = do_init_config();
	else if (IS_API("init-nino"))
		err = do_init_nino();
	else
		err = do_mtd_api(ep, argc - 2, argv + 1);

	return err;
}

int main(int argc, char *argv[])
{
	int err;
	int ret = EXIT_SUCCESS;
	int opt_snd_fph_hdrs = 0;
	int opt_log_level = MTD_OPT_LOG_ERR;
	char *snd_fph_hdrs = getenv("MTD_CLI_OPT_SND_FPH_HDRS");
	char *log_level = getenv("MTD_CLI_OPT_LOG_LEVEL");
	const char *hdrs[2] = { NULL };

	if (argc == 1) {
		print_api_help();
		exit(EXIT_FAILURE);
	}

	if (snd_fph_hdrs && (*snd_fph_hdrs == 't' || *snd_fph_hdrs == '1'))
		opt_snd_fph_hdrs = MTD_OPT_SND_ANTI_FRAUD_HDRS;
	if (log_level && *log_level == 'd')
		opt_log_level = MTD_OPT_LOG_DEBUG;
	else if (log_level && *log_level == 'i')
		opt_log_level = MTD_OPT_LOG_INFO;

	err = mtd_init(opt_log_level|opt_snd_fph_hdrs|MTD_OPT_GLOBAL_INIT);
	if (err)
		exit(EXIT_FAILURE);

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
	if (hdrs[0])
		mtd_hdrs_add(hdrs);

	err = dispatcher(argc - 1, argv + 1);
	if (err) {
	       if (err == MTD_ERR_NEEDS_AUTHORISATION)
		       fprintf(stderr, "Please run 'mtd-cli oauth\n");
	       else if (err == ERR_UNKNOWN_CMD)
		       print_api_help();

	       ret = EXIT_FAILURE;
	}

	mtd_deinit();

	exit(ret);
}
