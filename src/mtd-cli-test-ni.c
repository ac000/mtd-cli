/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-test-fph.c - Make Tax Digital - National Insurance Test Support
 *
 * Copyright (C) 2020		Andrew Clayton <andrew@digital-domain.net>
 */

#include <stddef.h>

#include <libmtdac/mtd-test-ni.h>

#include "mtd-cli.h"

#define API	test_ni
#define API_CMD	"test-ni"

#define API_NAME "National Insurance Test Support"
#define CMDS "create-annual-summary"

static const struct endpoint endpoints[] = {
	{
		.name = "create-annual-summary",
		.api_func = {
			.func_3d = mtd_test_ni_create_annual_summary
		},
		.func = FUNC_3d,
		.nr_req_args = 3,
		.use = "create-annual-summary <file> utr taxYear"
	},
	{ NULL, { NULL }, 0, 0, NULL}
};

const struct _endpoint ENDPOINT = {
	.endpoints = endpoints,
	.api_name = API_NAME,
	.cmds = CMDS
};
