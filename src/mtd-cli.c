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

#include "mtd-cli.h"
#include "mtd-cli-sa.h"
#include "mtd-cli-saac.h"
#include "mtd-cli-ic.h"
#include "mtd-cli-ni.h"
#include "mtd-cli-test-cu.h"
#include "mtd-cli-test-fph.h"

#define MAX_ARGV	7

#define APIS		"init oauth config sa saac ic ni test-cu test-fph"

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
		.api = "ni",
		.endpoint = &ni_endpoint
	},
	{
		.api = "test-cu",
		.endpoint = &test_cu_endpoint
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

int check_args(int argc, const char *name, const struct endpoint *ep,
	       int (*print_help)(void))
{
	int i = 0;

	if (!name)
		goto out_help;

	for ( ; ep[i].name != NULL; i++) {
		if (strcmp(ep[i].name, name) != 0)
			continue;

		if (ep[i].nr_req_args == argc)
			return 0;

		printf("Usage: %s\n", ep[i].use);

		return -1;
	}

out_help:
	print_help();

	return -1;
}

int do_api_func(const struct endpoint *ep, int argc, char *argv[], char **buf)
{
	int i;
	const char *args[MAX_ARGV] = { NULL };

	for (i = 0; i < argc && i < MAX_ARGV; i++)
		args[i] = argv[i + 1];

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
		const struct endpoint *ep = api_ep_map[i].endpoint->endpoints;

		if (strcmp(api_ep_map[i].api, name) != 0)
			continue;

		err = check_args(argc, argv[0], ep,
				 api_ep_map[i].endpoint->print_help);
		if (err)
			return err;
		err = do_api_func(ep, argc, argv, &buf);

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

static int do_config(void)
{
	return mtd_init_config();
}

static int do_oauth(void)
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
	err = mtd_init_auth();
	if (err)
		return err;

	printf("\nInitialisation complete. Re-run command if something looks "
	       "wrong.\n");

	return err;
}


#define IS_API(api)		(strcmp(api, ep) == 0)
static int dispatcher(int argc, char *argv[])
{
	const char *ep = argv[0];
	int err = -1;

	if (IS_API("init"))
		err = do_init();
	else if (IS_API("oauth"))
		err = do_oauth();
	else if (IS_API("config"))
		err = do_config();
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

	err = mtd_init(opt_log_level|opt_snd_fph_hdrs);
	if (err && strcmp(argv[1], "init") != 0) {
		if (err == MTD_ERR_MISSING_CONFIG)
			fprintf(stderr, "Please run 'mtd-cli init\n");
		exit(EXIT_FAILURE);
	}

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
