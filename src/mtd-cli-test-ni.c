/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-test-fph.c - Make Tax Digital - National Insurance Test Support
 *
 * Copyright (C) 2020		Andrew Clayton <andrew@digital-domain.net>
 */

#include <stddef.h>

#include <libmtdac/mtd-test-ni.h>

#include "mtd-cli.h"

#define MTD_CLI_CMD	MTD_CLI " test-ni "

#define API_NAME "National Insurance Test Support"
#define CMDS "create-annual-summary"

static const struct endpoint endpoints[] = {
	{
		.name = "create-annual-summary",
		.api_func = {
			.func_3 = mtd_test_ni_create_annual_summary
		},
		.func = FUNC_3,
		.nr_req_args = 3,
		.use = MTD_CLI_CMD "create-annual-summary <file> utr taxYear"
	},
	{ NULL, { NULL }, 0, 0, NULL}
};

const struct _endpoint test_ni_endpoint = {
	.endpoints = endpoints,
	.api_name = API_NAME,
	.cmds = CMDS
};
