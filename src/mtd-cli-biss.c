/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-biss.c - Make Tax Digital - Business Income Source Summary
 *
 * Copyright (C) 2020 - 2022	Andrew Clayton <andrew@digital-domain.net>
 */

#include <libmtdac/mtd-biss.h>

#include "mtd-cli.h"

#define API	biss

#define API_NAME "Business Income Source Summary"
#define CMDS "get-summary"

static const struct endpoint endpoints[] = {
	{
		.name = "get-summary",
		.func_3 = mtd_biss_get_summary,
		.func = FUNC_3,
		.nr_req_args = 3,
		.args = "typeOfBusiness taxYear businessId"
	},

	{ }
};

const struct _endpoint ENDPOINT = {
	.endpoints = endpoints,
	.api_name = API_NAME,
	.cmds = CMDS
};
