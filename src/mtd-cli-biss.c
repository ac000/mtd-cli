/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-biss.c - Make Tax Digital - Business Income Source Summary
 *
 * Copyright (C) 2020		Andrew Clayton <andrew@digital-domain.net>
 */

#include <stddef.h>

#include <libmtdac/mtd-biss.h>

#include "mtd-cli.h"

#define MTD_CLI_CMD	MTD_CLI " biss "

#define API_NAME "Business Income Source Summary"
#define CMDS "get-self-employment get-property"

static const struct endpoint endpoints[] = {
	{
		.name = "get-self-employment",
		.api_func = {
			.func_1 = mtd_biss_get_self_employment
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = MTD_CLI_CMD "get-self-employment selfEmploymentId=[,taxYear=YYYY-YY]"
	},
	{
		.name = "get-property",
		.api_func = {
			.func_1 = mtd_biss_get_property
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = MTD_CLI_CMD "get-property typeOfBusiness={uk-property-non-fhl,uk-property-fhl}[,taxYear=YYYY-YY]"
	},
	{ NULL, { NULL }, 0, 0, NULL}
};

const struct _endpoint biss_endpoint = {
	.endpoints = endpoints,
	.api_name = API_NAME,
	.cmds = CMDS
};
