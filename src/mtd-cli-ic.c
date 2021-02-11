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
		.api_func = {
			.func_1 = mtd_ic_sa_list_calculations
		},
		.func = FUNC_1,
		.nr_req_args = 0,
		.use = "sa-list-calculations [taxYear=YYYY-YY]"
	},
	{
		.name = "sa-trigger-calculation",
		.api_func = {
			.func_1d = mtd_ic_sa_trigger_calculation
		},
		.func = FUNC_1d,
		.nr_req_args = 1,
		.use = "sa-trigger-calculation <file>"
	},
	{
		.name = "sa-get-calculation-metadata",
		.api_func = {
			.func_1 = mtd_ic_sa_get_calculation_meta
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = "sa-get-calculation-metadata calculationId"
	},
	{
		.name = "sa-get-income-tax-nics-calc",
		.api_func = {
			.func_1 = mtd_ic_sa_get_income_tax_nics_calc
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = "sa-get-income-tax-nics-calc calculationId"
	},
	{
		.name = "sa-get-taxable-income",
		.api_func = {
			.func_1 = mtd_ic_sa_get_taxable_income
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = "sa-create-period calculationId"
	},
	{
		.name = "sa-get-allowances-deductions-reliefs",
		.api_func = {
			.func_1 = mtd_ic_sa_get_allowances_deductions_reliefs
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = "sa-get-allowances-deductions-reliefs calculationId"
	},
	{
		.name = "sa-get-end-of-year-estimate",
		.api_func = {
			.func_1 = mtd_ic_sa_get_end_of_year_est
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = "sa-get-end-of-year-estimate calculationId"
	},
	{
		.name = "sa-get-messages",
		.api_func = {
			.func_2 = mtd_ic_sa_get_messages
		},
		.func = FUNC_2,
		.nr_req_args = 1,
		.use = "sa-get-messages calculationId [[type={info,warning,error}], ...]"
	},
	{
		.name = "cr-intent-to-crystallise",
		.api_func = {
			.func_1 = mtd_ic_cr_intent_to_crystallise
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = "cr-intent-to-crystallise taxYear"
	},
	{
		.name = "cr-crystallise",
		.api_func = {
			.func_2d = mtd_ic_cr_crystallise
		},
		.func = FUNC_2d,
		.nr_req_args = 2,
		.use = "cr-crystallise <file> taxYear"
	},

	{ }
};

const struct _endpoint ENDPOINT = {
	.endpoints = endpoints,
	.api_name = API_NAME,
	.cmds = CMDS
};
