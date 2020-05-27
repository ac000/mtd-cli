/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-sa.c - Make Tax Digital - Self-Assessment
 *
 * Copyright (C) 2020		Andrew Clayton <andrew@digital-domain.net>
 */

#include <stdio.h>

#include <libmtdac/mtd-sa.h>

#include "mtd-cli.h"

#define MTD_CLI_CMD	MTD_CLI " sa "
#define API_NAME	"Self-Assessment"

#define ENDPOINTS \
"Self-Employment\n\n"\
"se-list-employments se-create-employment se-get-employment\n"\
"se-list-obligations se-list-periods se-create-period se-get-period\n"\
"se-update-period se-get-annual-summary se-update-annual-summary\n"\
"se-submit-end-of-period-statement se-get-end-of-period-statement\n\n"\
"Dividends Income\n\n"\
"di-get-annual-summary di-update-annual-summary\n\n"\
"Savings Accounts\n\n"\
"sa-list-accounts sa-create-account sa-get-account sa-get-annual-summary\n"\
"sa-update-annual-summary\n\n"\
"Charitable Giving\n\n"\
"cg-get-charitable-giving cg-update-charitable-giving\n\n"\
"Tax Calculations\n\n"\
"tc-calculate tc-get-calculation tc-get-validation-msgs\n\n"\
"Crystallisation\n\n"\
"cr-intent-to-crystallise cr-crystallise cr-list-obligations"

static int print_endpoints(void)
{
	printf("Available " API_NAME " endpoints :-\n\n%s\n", ENDPOINTS);

	return -1;
}

static const struct endpoint endpoints[] = {
	/* Self-Employment */
	{
		.name = "se-list-employments",
		.api_func = {
			.func_0 = &mtd_sa_se_list_employments
		},
		.func = FUNC_0,
		.nr_req_args = 0,
		.use = MTD_CLI_CMD "se-list-employments"
	},
	{
		.name = "se-create-employment",
		.api_func = {
			.func_1 = &mtd_sa_se_create_employment
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = MTD_CLI_CMD "se-create-employment <file>"
	},
	{
		.name = "se-get-employment",
		.api_func = {
			.func_1 = &mtd_sa_se_get_employment
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = MTD_CLI_CMD "se-get-employment selfEmploymentId"
	},
	{
		.name = "se-list-obligations",
		.api_func = {
			.func_1 = &mtd_sa_se_list_obligations
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = MTD_CLI_CMD "se-list-obligations selfEmploymentId"
	},
	{
		.name = "se-list-periods",
		.api_func = {
			.func_1 = &mtd_sa_se_list_periods
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = MTD_CLI_CMD "se-list-periods selfEmploymentId"
	},
	{
		.name = "se-create-period",
		.api_func = {
			.func_2 = &mtd_sa_se_create_period
		},
		.func = FUNC_2,
		.nr_req_args = 2,
		.use = MTD_CLI_CMD "se-create-period <file> selfEmploymentId"
	},
	{
		.name = "se-get-period",
		.api_func = {
			.func_2 = &mtd_sa_se_get_period
		},
		.func = FUNC_2,
		.nr_req_args = 2,
		.use = MTD_CLI_CMD "se-get-period selfEmploymentId periodId"
	},
	{
		.name = "se-update-period",
		.api_func = {
			.func_3 = &mtd_sa_se_update_period
		},
		.func = FUNC_3,
		.nr_req_args = 3,
		.use = MTD_CLI_CMD "se-update-period <file> selfEmploymentId periodId"
	},
	{
		.name = "se-get-annual-summary",
		.api_func = {
			.func_2 = &mtd_sa_se_get_annual_summary
		},
		.func = FUNC_2,
		.nr_req_args = 2,
		.use = MTD_CLI_CMD "se-get-annual-summary selfEmploymentId taxYear"
	},
	{
		.name = "se-update-annual-summary",
		.api_func = {
			.func_3 = &mtd_sa_se_update_annual_summary
		},
		.func = FUNC_3,
		.nr_req_args = 3,
		.use = MTD_CLI_CMD "se-update-annual-summary <file> selfEmploymentId taxYear"
	},
	{
		.name = "se-submit-end-of-period-statement",
		.api_func = {
			.func_4 = &mtd_sa_se_submit_end_of_period_statement
		},
		.func = FUNC_4,
		.nr_req_args = 4,
		.use = MTD_CLI_CMD "se-submit-end-of-period-statement <file> selfEmploymentId start end"
	},
	{
		.name = "se-get-end-of-period-statement",
		.api_func = {
			.func_2 = &mtd_sa_se_get_end_of_period_statement
		},
		.func = FUNC_2,
		.nr_req_args = 1,
		.use = MTD_CLI_CMD "se-get-end-of-period-statement selfEmploymentId [[from=YYYY-MM-DD][,[to=YYYY-MM-DD]]]"
	},
	/* Dividends Income */
	{
		.name = "di-get-annual-summary",
		.api_func = {
			.func_1 = &mtd_sa_di_get_annual_summary
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = MTD_CLI_CMD "di-get-annual-summary taxYear"
	},
	{
		.name = "di-update-annual-summary",
		.api_func = {
			.func_2 = &mtd_sa_di_update_annual_summary
		},
		.func = FUNC_2,
		.nr_req_args = 2,
		.use = MTD_CLI_CMD "di-get-annual-summary <file> taxYear"
	},
	/* Savings Accounts */
	{
		.name = "sa-list-accounts",
		.api_func = {
			.func_0 = &mtd_sa_sa_list_accounts
		},
		.func = FUNC_0,
		.nr_req_args = 0,
		.use = MTD_CLI_CMD "sa-list-accounts"
	},
	{
		.name = "sa-create-account",
		.api_func = {
			.func_1 = &mtd_sa_sa_create_account
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = MTD_CLI_CMD "sa-create-account <file>"
	},
	{
		.name = "sa-get-account",
		.api_func = {
			.func_1 = &mtd_sa_sa_get_account
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = MTD_CLI_CMD "sa-get-account savingsAccountId"
	},
	{
		.name = "sa-get-annual-summary",
		.api_func = {
			.func_2 = &mtd_sa_sa_get_annual_summary
		},
		.func = FUNC_2,
		.nr_req_args = 2,
		.use = MTD_CLI_CMD "sa-get-annual-summary savingsAccountId taxYear"
	},
	{
		.name = "sa-update-annual-summary",
		.api_func = {
			.func_3 = &mtd_sa_sa_update_annual_summary
		},
		.func = FUNC_3,
		.nr_req_args = 3,
		.use = MTD_CLI_CMD "sa-update-annual-summary <file> savingsAccountId taxYear"
	},
	/* Charitable Giving */
	{
		.name = "cg-get-charitable-giving",
		.api_func = {
			.func_1 = &mtd_sa_cg_get_charitable_giving
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = MTD_CLI_CMD "cg-get-charitable-giving taxYear"
	},
	{
		.name = "cg-update-charitable-giving",
		.api_func = {
			.func_2 = &mtd_sa_cg_update_charitable_giving
		},
		.func = FUNC_2,
		.nr_req_args = 2,
		.use = MTD_CLI_CMD "cg-get-charitable-giving <file> taxYear"
	},
	/* Tax Calculations - EOL Jul 2020 */
	{
		.name = "tc-calculate",
		.api_func = {
			.func_1 = &mtd_sa_tc_calculate
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = MTD_CLI_CMD "tc-calculate <file>"
	},
	{
		.name = "tc-get-calculation",
		.api_func = {
			.func_1 =  &mtd_sa_tc_get_calculation
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = MTD_CLI_CMD "tc-get-calculation calculationId"
	},
	{
		.name = "tc-get-validation-msgs",
		.api_func = {
			.func_1 = &mtd_sa_tc_get_validation_msgs
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = MTD_CLI_CMD "tc-get-validation-msgs calculationId"
	},
	/* Crystallisation */
	{
		.name = "cr-intent-to-crystallise",
		.api_func = {
			.func_1 = &mtd_sa_cr_intent_to_crystallise
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = MTD_CLI_CMD "cr-intent-to-crystallise taxYear"
	},
	{
		.name = "cr-crystallise",
		.api_func = {
			.func_1 = &mtd_sa_cr_crystallise
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = MTD_CLI_CMD "cr-crystallise taxYear"
	},
	{
		.name = "cr-list-obligations",
		.api_func = {
			.func_1 = &mtd_sa_cr_list_obligations
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = MTD_CLI_CMD "cr-list-obligations from=YYYY-MM-DD,to=YYYY-MM-DD"
	},
	{ NULL, { NULL }, 0, 0, NULL }
};

const struct _endpoint sa_endpoint = {
	.endpoints = endpoints,
	.print_help = &print_endpoints
};
