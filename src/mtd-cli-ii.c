/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-ii.c - Make Tax Digital - Individual Income
 *
 * Copyright (C) 2020		Andrew Clayton <andrew@digital-domain.net>
 */

#include <stddef.h>

#include <libmtdac/mtd-ii.h>

#include "mtd-cli.h"

#define MTD_CLI_CMD	MTD_CLI " ii "

#define API_NAME "Individual Income"
#define CMDS \
"get-annual-summary"

static const struct endpoint endpoints[] = {
	{
		.name = "get-annual-summary",
		.api_func = {
			.func_2 = mtd_ii_get_annual_summary
		},
		.func = FUNC_2,
		.nr_req_args = 2,
		.use = MTD_CLI_CMD "get-annual-summary utr taxYear"
	},
	{ NULL, { NULL }, 0, 0, NULL }
};

const struct _endpoint ii_endpoint = {
	.endpoints = endpoints,
	.api_name = API_NAME,
	.cmds = CMDS
};
