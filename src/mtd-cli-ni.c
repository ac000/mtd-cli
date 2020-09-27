/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-ni.c - Make Tax Digital - National Insurance
 *
 * Copyright (C) 2020		Andrew Clayton <andrew@digital-domain.net>
 */

#include <stddef.h>

#include <libmtdac/mtd-ni.h>

#include "mtd-cli.h"

#define API	ni

#define API_NAME "National Insurance"
#define CMDS "get-annual-summary"

static const struct endpoint endpoints[] = {
	{
		.name = "get-annual-summary",
		.api_func = {
			.func_2 = mtd_ni_get_annual_summary
		},
		.func = FUNC_2,
		.nr_req_args = 2,
		.use = "get-annual-summary utr taxYear"
	},
	{ NULL, { NULL }, 0, 0, NULL}
};

const struct _endpoint ENDPOINT = {
	.endpoints = endpoints,
	.api_name = API_NAME,
	.cmds = CMDS
};
