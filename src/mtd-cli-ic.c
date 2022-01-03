/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-ic.c - Make Tax Digital - Individual Calculations
 *
 * Copyright (C) 2020 - 2021	Andrew Clayton <andrew@digital-domain.net>
 */

#include <stddef.h>

#include <libmtdac/mtd-ic.h>

#include "mtd-cli.h"

#define API	ic

#define API_NAME "Individual Calculations"
#define CMDS \
"Self-Assessment\n\n"\
"sa-list-calculations sa-trigger-calculation sa-get-calculation-metadata\n"\
"sa-get-income-tax-nics-calc sa-get-taxable-income\n"\
"sa-get-allowances-deductions-reliefs sa-get-end-of-year-estimate\n"\
"sa-get-messages\n\n"\
"Crystallisation\n\n"\
"cr-intent-to-crystallise cr-crystallise"


static const struct endpoint endpoints[] = {
	{
		.name = "sa-list-calculations",
		.func_1 = mtd_ic_sa_list_calculations,
		.func = FUNC_1,
		.nr_req_args = 0,
		.args = "[taxYear=YYYY-YY]"
	}, {
		.name = "sa-trigger-calculation",
		.func_1d = mtd_ic_sa_trigger_calculation,
		.func = FUNC_1d,
		.nr_req_args = 1,
		.args = "<file>"
	}, {
		.name = "sa-get-calculation-metadata",
		.func_1 = mtd_ic_sa_get_calculation_meta,
		.func = FUNC_1,
		.nr_req_args = 1,
		.args = "calculationId"
	}, {
		.name = "sa-get-income-tax-nics-calc",
		.func_1 = mtd_ic_sa_get_income_tax_nics_calc,
		.func = FUNC_1,
		.nr_req_args = 1,
		.args = "calculationId"
	}, {
		.name = "sa-get-taxable-income",
		.func_1 = mtd_ic_sa_get_taxable_income,
		.func = FUNC_1,
		.nr_req_args = 1,
		.args = "calculationId"
	}, {
		.name = "sa-get-allowances-deductions-reliefs",
		.func_1 = mtd_ic_sa_get_allowances_deductions_reliefs,
		.func = FUNC_1,
		.nr_req_args = 1,
		.args = "calculationId"
	}, {
		.name = "sa-get-end-of-year-estimate",
		.func_1 = mtd_ic_sa_get_end_of_year_est,
		.func = FUNC_1,
		.nr_req_args = 1,
		.args = "calculationId"
	}, {
		.name = "sa-get-messages",
		.func_2 = mtd_ic_sa_get_messages,
		.func = FUNC_2,
		.nr_req_args = 1,
		.args = "calculationId [[type={info,warning,error}], ...]"
	}, {
		.name = "cr-intent-to-crystallise",
		.func_1 = mtd_ic_cr_intent_to_crystallise,
		.func = FUNC_1,
		.nr_req_args = 1,
		.args = "taxYear"
	}, {
		.name = "cr-crystallise",
		.func_2d = mtd_ic_cr_crystallise,
		.func = FUNC_2d,
		.nr_req_args = 2,
		.args = "<file> taxYear"
	},

	{ }
};

const struct _endpoint ENDPOINT = {
	.endpoints = endpoints,
	.api_name = API_NAME,
	.cmds = CMDS
};
