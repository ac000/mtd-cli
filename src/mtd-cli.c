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
#include "mtd-cli-ni.h"

#define APIS		"init oauth config sa saac ni"

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
		.api = "ni",
		.endpoint = &ni_endpoint
	},
	{ NULL, NULL }
};

static int print_api_help(void)
{
	printf("Available APIs :-\n\n%s\n", APIS);

	return -1;
}

int check_args(int argc, const char *name, const struct endpoint *ep,
	       int (*print_help)(void))
{
	int ret = -1;
	unsigned i = 0;
	bool found = false;

	if (!name)
		goto out_not_found;

	for ( ; ep[i].name != NULL; i++) {
		if (strcmp(ep[i].name, name) == 0) {
			if (ep[i].nargs == argc)
				return 0;

			found = true;
			printf("Usage:\t%s\n", ep[i].use);
		}
	}

out_not_found:
	if (!found)
		print_help();

	return ret;
}

int do_api_func(const struct endpoint *ep, char *argv[], char **buf)
{
	int i = 0;

	for ( ; ep[i].name != NULL; i++) {
		if (strcmp(ep[i].name, argv[0]) != 0)
			continue;

		switch (ep[i].nargs) {
		case 0:
			return ep[i].api_func.func_0(buf);
		case 1:
			return ep[i].api_func.func_1(argv[1], buf);
		case 2:
			return ep[i].api_func.func_2(argv[1], argv[2], buf);
		case 3:
			return ep[i].api_func.func_3(argv[1], argv[2], argv[3],
						     buf);
		case 4:
			return ep[i].api_func.func_4(argv[1], argv[2], argv[3],
						     argv[4], buf);
		}
	}

	return -1;
}

static int do_mtd_api(const char *name, int argc, char *argv[])
{
	char *buf = NULL;
	json_t *rootbuf;
	int i = 0;
	int err = -1;

	for ( ; api_ep_map[i].api != NULL; i++) {
		const struct endpoint *ep = api_ep_map[i].endpoint->endpoints;

		if (strcmp(api_ep_map[i].api, name) != 0)
			continue;

		err = check_args(argc, argv[0], ep,
				 api_ep_map[i].endpoint->print_help);
		if (err)
			return err;
		err = do_api_func(ep, argv, &buf);

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

	if (argc == 1) {
		print_api_help();
		exit(EXIT_FAILURE);
	}

	err = mtd_init(MTD_OPT_LOG_ERR);
	if (err && strcmp(argv[1], "init") != 0) {
		if (err == MTD_ERR_MISSING_CONFIG)
			fprintf(stderr, "Please run 'mtd-cli init\n");
		exit(EXIT_FAILURE);
	}

	err = dispatcher(argc - 1, argv + 1);
	if (err) {
	       if (err == MTD_ERR_NEEDS_AUTHORISATION)
		       fprintf(stderr, "Please run 'mtd-cli oauth\n");
	       ret = EXIT_FAILURE;
	}

	mtd_deinit();

	exit(ret);
}
