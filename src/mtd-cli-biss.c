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
#define CMDS "get-self-employment get-uk-property get-foreign-property"

static const struct endpoint endpoints[] = {
	{
		.name = "get-self-employment",
		.func_1 = mtd_biss_get_self_employment,
		.func = FUNC_1,
		.nr_req_args = 1,
		.args = "selfEmploymentId=[,taxYear=YYYY-YY]"
	}, {
		.name = "get-uk-property",
		.func_1 = mtd_biss_get_uk_property,
		.func = FUNC_1,
		.nr_req_args = 1,
		.args = "typeOfBusiness={uk-property-non-fhl,uk-property-fhl}[,taxYear=YYYY-YY]"
	}, {
		.name = "get-foreign-property",
		.func_1 = mtd_biss_get_foreign_property,
		.func = FUNC_1,
		.nr_req_args = 1,
		.args = "businessId=,typeOfBusiness={foreign-property-fhl-eea,foreign-property}[,taxYear=YYYY-YY]"
	},

	{ }
};

const struct _endpoint ENDPOINT = {
	.endpoints = endpoints,
	.api_name = API_NAME,
	.cmds = CMDS
};
