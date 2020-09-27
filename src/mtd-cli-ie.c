/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-ie.c - Make Tax Digital - Individual Employment
 *
 * Copyright (C) 2020		Andrew Clayton <andrew@digital-domain.net>
 */

#include <stddef.h>

#include <libmtdac/mtd-ie.h>

#include "mtd-cli.h"

#define API	ie

#define API_NAME "Individual Employment"
#define CMDS \
"get-annual-summary"

static const struct endpoint endpoints[] = {
	{
		.name = "get-annual-summary",
		.api_func = {
			.func_2 = mtd_ie_get_annual_summary
		},
		.func = FUNC_2,
		.nr_req_args = 2,
		.use = "get-annual-summary utr taxYear"
	},
	{ NULL, { NULL }, 0, 0, NULL }
};

const struct _endpoint ENDPOINT = {
	.endpoints = endpoints,
	.api_name = API_NAME,
	.cmds = CMDS
};
