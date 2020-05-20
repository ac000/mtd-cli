/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-ic.c - Make Tax Digital - Individual Calculations
 *
 * Copyright (C) 2020		Andrew Clayton <andrew@digital-domain.net>
 */

#include <stdio.h>

#include <libmtdac/mtd-ic.h>

#include "mtd-cli.h"

#define MTD_CLI_CMD	" ic "
#define API_NAME	"Individual Calculations"

#define ENDPOINTS \
"list-calculations trigger-calculation get-calculation-metadata\n"\
"get-income-tax-nics-calc get-taxable-income get-allowances-deductions-reliefs\n"\
"get-end-of-year-estimate get-messages"

static int print_endpoints(void)
{
	printf("Available " API_NAME " endpoints :-\n\n%s\n", ENDPOINTS);

	return -1;
}

static const struct endpoint endpoints[] = {
	{
		.name = "list-calculations",
		.api_func = {
			.func_0 = &mtd_ic_list_calculations
		},
		.nargs = 0,
		.use = MTD_CLI_CMD "list-calculations"
	},
	{
		.name = "trigger-calculation",
		.api_func = {
			.func_1 = &mtd_ic_trigger_calculation
		},
		.nargs = 1,
		.use = MTD_CLI_CMD "trigger-calculation <file>"
	},
	{
		.name = "get-calculation-metadata",
		.api_func = {
			.func_1 = &mtd_ic_get_calculation_meta
		},
		.nargs = 1,
		.use = MTD_CLI_CMD "get-calculation-metadata calculationId"
	},
	{
		.name = "get-income-tax-nics-calc",
		.api_func = {
			.func_1 = &mtd_ic_get_income_tax_nics_calc
		},
		.nargs = 1,
		.use = MTD_CLI_CMD "get-income-tax-nics-calc calculationId"
	},
	{
		.name = "get-taxable-income",
		.api_func = {
			.func_1 = &mtd_ic_get_taxable_income
		},
		.nargs = 1,
		.use = MTD_CLI_CMD "create-period calculationId"
	},
	{
		.name = "get-allowances-deductions-reliefs",
		.api_func = {
			.func_1 = &mtd_ic_get_allowances_deductions_reliefs
		},
		.nargs = 1,
		.use = MTD_CLI_CMD "get-allowances-deductions-reliefs calculationId"
	},
	{
		.name = "get-end-of-year-estimate",
		.api_func = {
			.func_1 = &mtd_ic_get_end_of_year_est
		},
		.nargs = 1,
		.use = MTD_CLI_CMD "get-end-of-year-estimate calculationId"
	},
	{
		.name = "get-messages",
		.api_func = {
			.func_1 = &mtd_ic_get_messages
		},
		.nargs = 1,
		.use = MTD_CLI_CMD "get-messages calculationId"
	},
	{ NULL, { NULL }, 0, NULL }
};

const struct _endpoint ic_endpoint = {
	.endpoints = endpoints,
	.print_help = &print_endpoints
};
