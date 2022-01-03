/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-ibeops.c - Make Tax Digital - Individuals Business End of Period Statement
 *
 * Copyright (C) 2021 - 2022	Andrew Clayton <andrew@digital-domain.net>
 */

#include <stddef.h>

#include <libmtdac/mtd-ibeops.h>

#include "mtd-cli.h"

#define API	ibeops

#define API_NAME "Individuals Business End of Period Statement"
#define CMDS "submit-end-of-period-statement"

static const struct endpoint endpoints[] = {
	{
		.name = "submit-end-of-period-statement",
		.func_1d = mtd_ibeops_submit_eops,
		.func = FUNC_1d,
		.nr_req_args = 1,
		.args = "<file>"
	},

	{ }
};

const struct _endpoint ENDPOINT = {
	.endpoints = endpoints,
	.api_name = API_NAME,
	.cmds = CMDS
};
