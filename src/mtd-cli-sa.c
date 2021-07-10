/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-sa.c - Make Tax Digital - Self-Assessment
 *
 * Copyright (C) 2020 - 2021	Andrew Clayton <andrew@digital-domain.net>
 */

#include <stddef.h>

#include <libmtdac/mtd-sa.h>

#include "mtd-cli.h"

#define API	sa

#define API_NAME "Self-Assessment"
#define CMDS \
"Self-Employment\n\n"\
"se-create-employment se-list-periods se-create-period se-get-period\n"\
"se-update-period se-get-annual-summary se-update-annual-summary\n"\
"se-submit-end-of-period-statement\n\n"\
"UK Property Business\n\n"\
"pb-create-property pb-list-obligations pb-list-non-fhl-periods\n"\
"pb-create-non-fhl-period pb-get-non-fhl-period\n"\
"pb-update-non-fhl-period pb-get-non-fhl-annual-summary\n"\
"pb-update-non-fhl-annual-summary pb-list-fhl-periods\n"\
"pb-create-fhl-period pb-get-fhl-period pb-update-fhl-period\n"\
"pb-get-fhl-annual-summary pb-update-fhl-annual-summary\n"\
"pb-submit-end-of-period-statement pb-get-end-of-period-statement\n\n"\
"Dividends Income\n\n"\
"di-get-annual-summary di-update-annual-summary\n\n"\
"Savings Accounts\n\n"\
"sa-list-accounts sa-create-account sa-get-account sa-get-annual-summary\n"\
"sa-update-annual-summary\n\n"\
"Charitable Giving\n\n"\
"cg-get-charitable-giving cg-update-charitable-giving\n\n"\
"Crystallisation\n\n"\
"cr-intent-to-crystallise cr-crystallise"

static const struct endpoint endpoints[] = {
	/* Self-Employment */
	{
		.name = "se-create-employment",
		.api_func = {
			.func_1d = mtd_sa_se_create_employment
		},
		.func = FUNC_1d,
		.nr_req_args = 1,
		.use = "se-create-employment <file>"
	},
	{
		.name = "se-list-periods",
		.api_func = {
			.func_1 = mtd_sa_se_list_periods
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = "se-list-periods selfEmploymentId"
	},
	{
		.name = "se-create-period",
		.api_func = {
			.func_2d = mtd_sa_se_create_period
		},
		.func = FUNC_2d,
		.nr_req_args = 2,
		.use = "se-create-period <file> selfEmploymentId"
	},
	{
		.name = "se-get-period",
		.api_func = {
			.func_2 = mtd_sa_se_get_period
		},
		.func = FUNC_2,
		.nr_req_args = 2,
		.use = "se-get-period selfEmploymentId periodId"
	},
	{
		.name = "se-update-period",
		.api_func = {
			.func_3d = mtd_sa_se_update_period
		},
		.func = FUNC_3d,
		.nr_req_args = 3,
		.use = "se-update-period <file> selfEmploymentId periodId"
	},
	{
		.name = "se-get-annual-summary",
		.api_func = {
			.func_2 = mtd_sa_se_get_annual_summary
		},
		.func = FUNC_2,
		.nr_req_args = 2,
		.use = "se-get-annual-summary selfEmploymentId taxYear"
	},
	{
		.name = "se-update-annual-summary",
		.api_func = {
			.func_3d = mtd_sa_se_update_annual_summary
		},
		.func = FUNC_3d,
		.nr_req_args = 3,
		.use = "se-update-annual-summary <file> selfEmploymentId taxYear"
	},
	{
		.name = "se-submit-end-of-period-statement",
		.api_func = {
			.func_4d = mtd_sa_se_submit_end_of_period_statement
		},
		.func = FUNC_4d,
		.nr_req_args = 4,
		.use = "se-submit-end-of-period-statement <file> selfEmploymentId start end"
	},
	/* Self-Assessment - UK Property Business */
	{
		.name = "pb-create-property",
		.api_func = {
			.func_1d = mtd_sa_pb_create_property
		},
		.func = FUNC_1d,
		.nr_req_args = 1,
		.use = "pb-create-property <file>"
	},
	{
		.name = "pb-list-obligations",
		.api_func = {
			.func_0 = mtd_sa_pb_list_obligations
		},
		.func = FUNC_0,
		.nr_req_args = 0,
		.use = "pb-list-obligations"
	},
	{
		.name = "pb-list-non-fhl-periods",
		.api_func = {
			.func_0 = mtd_sa_pb_list_non_fhl_periods
		},
		.nr_req_args = 0,
		.use = "pb-list-non-fhl-periods"
	},
	{
		.name = "pb-create-non-fhl-period",
		.api_func = {
			.func_1d = mtd_sa_pb_create_non_fhl_period
		},
		.func = FUNC_1d,
		.nr_req_args = 1,
		.use = "pb-create-non-fhl-period <file>"
	},
	{
		.name = "pb-get-non-fhl-period",
		.api_func = {
			.func_1 = mtd_sa_pb_get_non_fhl_period
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = "pb-get-non-fhl-period periodId"
	},
	{
		.name = "pb-update-non-fhl-period",
		.api_func = {
			.func_2d = mtd_sa_pb_update_non_fhl_period
		},
		.func = FUNC_2d,
		.nr_req_args = 2,
		.use = "pb-update-non-fhl-period <file> periodId"
	},
	{
		.name = "pb-get-non-fhl-annual-summary",
		.api_func = {
			.func_1 = mtd_sa_pb_get_non_fhl_annual_summary
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = "pb-get-non-fhl-annual-summary taxYear"
	},
	{
		.name = "pb-update-non-fhl-annual-summary",
		.api_func = {
			.func_2d = mtd_sa_pb_update_non_fhl_annual_summary
		},
		.func = FUNC_2d,
		.nr_req_args = 2,
		.use = "pb-update-non-fhl-annual-summary <file> taxYear"
	},
	{
		.name = "pb-list-fhl-periods",
		.api_func = {
			.func_0 = mtd_sa_pb_list_fhl_periods
		},
		.func = FUNC_0,
		.nr_req_args = 0,
		.use = "pb-list-fhl-periods"
	},
	{
		.name = "pb-create-fhl-period",
		.api_func = {
			.func_1d = mtd_sa_pb_create_fhl_period
		},
		.func = FUNC_1d,
		.nr_req_args = 1,
		.use = "pb-create-fhl-period <file>"
	},
	{
		.name = "pb-get-fhl-period",
		.api_func = {
			.func_1 = mtd_sa_pb_get_fhl_period
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = "pb-get-fhl-period periodId"
	},
	{
		.name = "pb-update-fhl-period",
		.api_func = {
			.func_2d = mtd_sa_pb_update_fhl_period
		},
		.func = FUNC_2d,
		.nr_req_args = 2,
		.use = "pb-update-fhl-period <file> periodId"
	},
	{
		.name = "pb-get-fhl-annual-summary",
		.api_func = {
			.func_1 = mtd_sa_pb_get_fhl_annual_summary
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = "pb-get-fhl-annual-summary taxYear"
	},
	{
		.name = "pb-update-fhl-annual-summary",
		.api_func = {
			.func_2d = mtd_sa_pb_update_fhl_annual_summary
		},
		.func = FUNC_2d,
		.nr_req_args = 2,
		.use = "pb-update-fhl-annual-summary <file> taxYear"
	},
	{
		.name = "pb-submit-end-of-period-statement",
		.api_func = {
			.func_3d = mtd_sa_pb_submit_end_of_period_statement
		},
		.func = FUNC_3d,
		.nr_req_args = 3,
		.use = "pb-submit-end-of-period-statement <file> start end"
	},
	{
		.name = "pb-get-end-of-period-statement",
		.api_func = {
			.func_1 = mtd_sa_pb_get_end_of_period_statement
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = "pb-get-end-of-period-statement from=YYYY-MM-DD,to=YYYY-MM-DD"
	},
	/* Dividends Income */
	{
		.name = "di-get-annual-summary",
		.api_func = {
			.func_1 = mtd_sa_di_get_annual_summary
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = "di-get-annual-summary taxYear"
	},
	{
		.name = "di-update-annual-summary",
		.api_func = {
			.func_2d = mtd_sa_di_update_annual_summary
		},
		.func = FUNC_2d,
		.nr_req_args = 2,
		.use = "di-get-annual-summary <file> taxYear"
	},
	/* Savings Accounts */
	{
		.name = "sa-list-accounts",
		.api_func = {
			.func_0 = mtd_sa_sa_list_accounts
		},
		.func = FUNC_0,
		.nr_req_args = 0,
		.use = "sa-list-accounts"
	},
	{
		.name = "sa-create-account",
		.api_func = {
			.func_1d = mtd_sa_sa_create_account
		},
		.func = FUNC_1d,
		.nr_req_args = 1,
		.use = "sa-create-account <file>"
	},
	{
		.name = "sa-get-account",
		.api_func = {
			.func_1 = mtd_sa_sa_get_account
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = "sa-get-account savingsAccountId"
	},
	{
		.name = "sa-get-annual-summary",
		.api_func = {
			.func_2 = mtd_sa_sa_get_annual_summary
		},
		.func = FUNC_2,
		.nr_req_args = 2,
		.use = "sa-get-annual-summary savingsAccountId taxYear"
	},
	{
		.name = "sa-update-annual-summary",
		.api_func = {
			.func_3d = mtd_sa_sa_update_annual_summary
		},
		.func = FUNC_3d,
		.nr_req_args = 3,
		.use = "sa-update-annual-summary <file> savingsAccountId taxYear"
	},
	/* Charitable Giving */
	{
		.name = "cg-get-charitable-giving",
		.api_func = {
			.func_1 = mtd_sa_cg_get_charitable_giving
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = "cg-get-charitable-giving taxYear"
	},
	{
		.name = "cg-update-charitable-giving",
		.api_func = {
			.func_2d = mtd_sa_cg_update_charitable_giving
		},
		.func = FUNC_2d,
		.nr_req_args = 2,
		.use = "cg-get-charitable-giving <file> taxYear"
	},
	/* Crystallisation */
	{
		.name = "cr-intent-to-crystallise",
		/* While this is a POST request, it doesn't send any body */
		.api_func = {
			.func_1 = mtd_sa_cr_intent_to_crystallise
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = "cr-intent-to-crystallise taxYear"
	},
	{
		.name = "cr-crystallise",
		.api_func = {
			.func_2d = mtd_sa_cr_crystallise
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
