/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-ni.c - make Tax Digital - National Insurance
 *
 * Copyright (C) 2020		Andrew Clayton <andrew@digital-domain.net>
 */

#include <stdio.h>

#include <libmtdac/mtd-ni.h>

#include "mtd-cli.h"

#define MTD_CLI_CMD	MTD_CLI " ni "
#define API_NAME	"National Insurance"

#define ENDPOINTS	"get-annual-summary"

static int print_endpoints(void)
{
	printf("Available " API_NAME " endpoints :-\n\n%s\n", ENDPOINTS);

	return -1;
}

static const struct endpoint endpoints[] = {
	{
		.name = "get-annual-summary",
		.api_func = {
			.func_2 = &mtd_ni_get_annual_summary
		},
		.nargs = 2,
		.use = MTD_CLI_CMD "get-annual-summary utr taxYear"
	},
	{ NULL, { NULL }, 0, NULL}
};

const struct _endpoint ni_endpoint = {
	.endpoints = endpoints,
	.print_help = &print_endpoints
};
