/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-test-fph.c - Make Tax Digital - Test Fraud Prevention Headers
 *
 * Copyright (C) 2020		Andrew Clayton <andrew@digital-domain.net>
 */

#include <stdio.h>

#include <libmtdac/mtd-test-fph.h>

#include "mtd-cli.h"

#define MTD_CLI_CMD	MTD_CLI " test-fph "
#define API_NAME	"Test Fraud Prevention Headers"

#define ENDPOINTS	"validate"

static int print_endpoints(void)
{
	printf("Available " API_NAME " endpoints :-\n\n%s\n", ENDPOINTS);

	return -1;
}

static const struct endpoint endpoints[] = {
	{
		.name = "validate",
		.api_func = {
			.func_0 = &mtd_test_fph_validate
		},
		.nargs = 0,
		.use = MTD_CLI_CMD "validate"
	},
	{ NULL, { NULL }, 0, NULL}
};

const struct _endpoint test_fph_endpoint = {
	.endpoints = endpoints,
	.print_help = &print_endpoints
};
