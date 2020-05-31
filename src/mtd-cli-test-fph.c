/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-test-fph.c - Make Tax Digital - Test Fraud Prevention Headers
 *
 * Copyright (C) 2020		Andrew Clayton <andrew@digital-domain.net>
 */

#include <stddef.h>

#include <libmtdac/mtd-test-fph.h>

#include "mtd-cli.h"

#define MTD_CLI_CMD	MTD_CLI " test-fph "

#define API_NAME "Test Fraud Prevention Headers"
#define CMDS "validate"

static const struct endpoint endpoints[] = {
	{
		.name = "validate",
		.api_func = {
			.func_0 = mtd_test_fph_validate
		},
		.func = FUNC_0,
		.nr_req_args = 0,
		.use = MTD_CLI_CMD "validate"
	},
	{ NULL, { NULL }, 0, 0, NULL}
};

const struct _endpoint test_fph_endpoint = {
	.endpoints = endpoints,
	.api_name = API_NAME,
	.cmds = CMDS
};
