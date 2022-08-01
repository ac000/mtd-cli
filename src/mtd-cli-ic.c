/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-ic.c - Make Tax Digital - Individual Calculations
 *
 * Copyright (C) 2020 - 2022	Andrew Clayton <andrew@digital-domain.net>
 */

#include <stdbool.h>

#include <libmtdac/mtd-ic.h>

#include "mtd-cli.h"

#define API	ic

#define API_NAME "Individual Calculations"
#define CMDS \
"TAX Calclations\n\n"\
"list-calculations trigger-calculation get-calculation\n\n"\
"Final Declaration\n\n"\
"final-declaration"

static const struct endpoint endpoints[] = {
	{
		.name = "list-calculations",
		.func_1 = mtd_ic_list_calculations,
		.func = FUNC_1,
		.nr_req_args = 0,
		.args = "[taxYear=YYYY-YY]"
	}, {
		.name = "trigger-calculation",
		.func_2 = mtd_ic_trigger_calculation,
		.func = FUNC_2,
		.nr_req_args = 1,
		.args = "taxYear [finalDeclaration={true,false}]"
	}, {
		.name = "get-calculation",
		.func_2 = mtd_ic_get_calculation,
		.func = FUNC_2,
		.nr_req_args = 2,
		.args = "taxYear calculationId"
	}, {
		.name = "final-declaration",
		.func_2 = mtd_ic_final_decl,
		.func = FUNC_2,
		.nr_req_args = 2,
		.args = "taxYear calculationId"
	},

	{ }
};

const struct _endpoint ENDPOINT = {
	.endpoints = endpoints,
	.api_name = API_NAME,
	.cmds = CMDS
};
