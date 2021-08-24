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
"se-update-period se-get-annual-summary se-update-annual-summary\n\n"\
"UK Property Business\n\n"\
"pb-create-property pb-list-non-fhl-periods\n"\
"pb-create-non-fhl-period pb-get-non-fhl-period\n"\
"pb-update-non-fhl-period pb-get-non-fhl-annual-summary\n"\
"pb-update-non-fhl-annual-summary pb-list-fhl-periods\n"\
"pb-create-fhl-period pb-get-fhl-period pb-update-fhl-period\n"\
"pb-get-fhl-annual-summary pb-update-fhl-annual-summary\n\n"\
"Dividends Income\n\n"\
"di-get-annual-summary di-update-annual-summary\n\n"\
"Savings Accounts\n\n"\
"sa-list-accounts sa-create-account sa-get-account sa-get-annual-summary\n"\
"sa-update-annual-summary\n\n"\
"Charitable Giving\n\n"\
"cg-get-charitable-giving cg-update-charitable-giving"

static const struct endpoint endpoints[] = {
	/* Self-Employment */
	{
		.name = "se-create-employment",
		.api_func = {
			.func_1d = mtd_sa_se_create_employment
		},
		.func = FUNC_1d,
		.nr_req_args = 1,
		.args = "<file>"
	}, {
		.name = "se-list-periods",
		.api_func = {
			.func_1 = mtd_sa_se_list_periods
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.args = "selfEmploymentId"
	}, {
		.name = "se-create-period",
		.api_func = {
			.func_2d = mtd_sa_se_create_period
		},
		.func = FUNC_2d,
		.nr_req_args = 2,
		.args = "<file> selfEmploymentId"
	}, {
		.name = "se-get-period",
		.api_func = {
			.func_2 = mtd_sa_se_get_period
		},
		.func = FUNC_2,
		.nr_req_args = 2,
		.args = "selfEmploymentId periodId"
	}, {
		.name = "se-update-period",
		.api_func = {
			.func_3d = mtd_sa_se_update_period
		},
		.func = FUNC_3d,
		.nr_req_args = 3,
		.args = "<file> selfEmploymentId periodId"
	}, {
		.name = "se-get-annual-summary",
		.api_func = {
			.func_2 = mtd_sa_se_get_annual_summary
		},
		.func = FUNC_2,
		.nr_req_args = 2,
		.args = "selfEmploymentId taxYear"
	}, {
		.name = "se-update-annual-summary",
		.api_func = {
			.func_3d = mtd_sa_se_update_annual_summary
		},
		.func = FUNC_3d,
		.nr_req_args = 3,
		.args = "<file> selfEmploymentId taxYear"
	},
	/* Self-Assessment - UK Property Business */
	{
		.name = "pb-create-property",
		.api_func = {
			.func_1d = mtd_sa_pb_create_property
		},
		.func = FUNC_1d,
		.nr_req_args = 1,
		.args = "<file>"
	}, {
		.name = "pb-list-non-fhl-periods",
		.api_func = {
			.func_0 = mtd_sa_pb_list_non_fhl_periods
		},
		.nr_req_args = 0,
		.args = ""
	}, {
		.name = "pb-create-non-fhl-period",
		.api_func = {
			.func_1d = mtd_sa_pb_create_non_fhl_period
		},
		.func = FUNC_1d,
		.nr_req_args = 1,
		.args = "<file>"
	}, {
		.name = "pb-get-non-fhl-period",
		.api_func = {
			.func_1 = mtd_sa_pb_get_non_fhl_period
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.args = "periodId"
	}, {
		.name = "pb-update-non-fhl-period",
		.api_func = {
			.func_2d = mtd_sa_pb_update_non_fhl_period
		},
		.func = FUNC_2d,
		.nr_req_args = 2,
		.args = "<file> periodId"
	}, {
		.name = "pb-get-non-fhl-annual-summary",
		.api_func = {
			.func_1 = mtd_sa_pb_get_non_fhl_annual_summary
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.args = "taxYear"
	}, {
		.name = "pb-update-non-fhl-annual-summary",
		.api_func = {
			.func_2d = mtd_sa_pb_update_non_fhl_annual_summary
		},
		.func = FUNC_2d,
		.nr_req_args = 2,
		.args = "<file> taxYear"
	}, {
		.name = "pb-list-fhl-periods",
		.api_func = {
			.func_0 = mtd_sa_pb_list_fhl_periods
		},
		.func = FUNC_0,
		.nr_req_args = 0,
		.args = ""
	}, {
		.name = "pb-create-fhl-period",
		.api_func = {
			.func_1d = mtd_sa_pb_create_fhl_period
		},
		.func = FUNC_1d,
		.nr_req_args = 1,
		.args = "<file>"
	}, {
		.name = "pb-get-fhl-period",
		.api_func = {
			.func_1 = mtd_sa_pb_get_fhl_period
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.args = "periodId"
	}, {
		.name = "pb-update-fhl-period",
		.api_func = {
			.func_2d = mtd_sa_pb_update_fhl_period
		},
		.func = FUNC_2d,
		.nr_req_args = 2,
		.args = "<file> periodId"
	}, {
		.name = "pb-get-fhl-annual-summary",
		.api_func = {
			.func_1 = mtd_sa_pb_get_fhl_annual_summary
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.args = "taxYear"
	}, {
		.name = "pb-update-fhl-annual-summary",
		.api_func = {
			.func_2d = mtd_sa_pb_update_fhl_annual_summary
		},
		.func = FUNC_2d,
		.nr_req_args = 2,
		.args = "<file> taxYear"
	},
	/* Dividends Income */
	{
		.name = "di-get-annual-summary",
		.api_func = {
			.func_1 = mtd_sa_di_get_annual_summary
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.args = "taxYear"
	}, {
		.name = "di-update-annual-summary",
		.api_func = {
			.func_2d = mtd_sa_di_update_annual_summary
		},
		.func = FUNC_2d,
		.nr_req_args = 2,
		.args = "<file> taxYear"
	},
	/* Savings Accounts */
	{
		.name = "sa-list-accounts",
		.api_func = {
			.func_0 = mtd_sa_sa_list_accounts
		},
		.func = FUNC_0,
		.nr_req_args = 0,
		.args = ""
	}, {
		.name = "sa-create-account",
		.api_func = {
			.func_1d = mtd_sa_sa_create_account
		},
		.func = FUNC_1d,
		.nr_req_args = 1,
		.args = "<file>"
	}, {
		.name = "sa-get-account",
		.api_func = {
			.func_1 = mtd_sa_sa_get_account
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.args = "savingsAccountId"
	}, {
		.name = "sa-get-annual-summary",
		.api_func = {
			.func_2 = mtd_sa_sa_get_annual_summary
		},
		.func = FUNC_2,
		.nr_req_args = 2,
		.args = "savingsAccountId taxYear"
	}, {
		.name = "sa-update-annual-summary",
		.api_func = {
			.func_3d = mtd_sa_sa_update_annual_summary
		},
		.func = FUNC_3d,
		.nr_req_args = 3,
		.args = "<file> savingsAccountId taxYear"
	},
	/* Charitable Giving */
	{
		.name = "cg-get-charitable-giving",
		.api_func = {
			.func_1 = mtd_sa_cg_get_charitable_giving
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.args = "taxYear"
	}, {
		.name = "cg-update-charitable-giving",
		.api_func = {
			.func_2d = mtd_sa_cg_update_charitable_giving
		},
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
