/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-ic.c - Make Tax Digital - Individual Calculations
 *
 * Copyright (C) 2020		Andrew Clayton <andrew@digital-domain.net>
 */

#include <stddef.h>

#include <libmtdac/mtd-ic.h>

#include "mtd-cli.h"

#define MTD_CLI_CMD	" ic "

static const char * const API_NAME = "Individual Calculations";
static const char * const CMDS =
"list-calculations trigger-calculation get-calculation-metadata\n"\
"get-income-tax-nics-calc get-taxable-income get-allowances-deductions-reliefs\n"\
"get-end-of-year-estimate get-messages";

static const struct endpoint endpoints[] = {
	{
		.name = "list-calculations",
		.api_func = {
			.func_0 = mtd_ic_list_calculations
		},
		.func = FUNC_0,
		.nr_req_args = 0,
		.use = MTD_CLI_CMD "list-calculations"
	},
	{
		.name = "trigger-calculation",
		.api_func = {
			.func_1 = mtd_ic_trigger_calculation
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = MTD_CLI_CMD "trigger-calculation <file>"
	},
	{
		.name = "get-calculation-metadata",
		.api_func = {
			.func_1 = mtd_ic_get_calculation_meta
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = MTD_CLI_CMD "get-calculation-metadata calculationId"
	},
	{
		.name = "get-income-tax-nics-calc",
		.api_func = {
			.func_1 = mtd_ic_get_income_tax_nics_calc
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = MTD_CLI_CMD "get-income-tax-nics-calc calculationId"
	},
	{
		.name = "get-taxable-income",
		.api_func = {
			.func_1 = mtd_ic_get_taxable_income
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = MTD_CLI_CMD "create-period calculationId"
	},
	{
		.name = "get-allowances-deductions-reliefs",
		.api_func = {
			.func_1 = mtd_ic_get_allowances_deductions_reliefs
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = MTD_CLI_CMD "get-allowances-deductions-reliefs calculationId"
	},
	{
		.name = "get-end-of-year-estimate",
		.api_func = {
			.func_1 = mtd_ic_get_end_of_year_est
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = MTD_CLI_CMD "get-end-of-year-estimate calculationId"
	},
	{
		.name = "get-messages",
		.api_func = {
			.func_1 = mtd_ic_get_messages
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = MTD_CLI_CMD "get-messages calculationId"
	},
	{ NULL, { NULL }, 0, 0, NULL }
};

const struct _endpoint ic_endpoint = {
	.endpoints = endpoints,
	.api_name = API_NAME,
	.cmds = CMDS
};
