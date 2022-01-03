/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-vat.c - Make Tax Digital - VAT
 *
 * Copyright (C) 2020 - 2022	Andrew Clayton <andrew@digital-domain.net>
 */

#include <stddef.h>

#include <libmtdac/mtd-vat.h>

#include "mtd-cli.h"

#define API	vat

#define API_NAME "VAT"
#define CMDS \
"list-obligations submit-period get-period list-liabilities list-payments\n"

static const struct endpoint endpoints[] = {
	{
		.name = "list-obligations",
		.func_2 = mtd_vat_list_obligations,
		.func = FUNC_2,
		.nr_req_args = 1,
		.args = "vrn [from=YYY-MM-DD][,[to=YYYY-MM-DD]][,[status=O|F]]"
	}, {
		.name = "submit-period",
		.func_2d = mtd_vat_submit_period,
		.func = FUNC_2d,
		.nr_req_args = 2,
		.args = "<file> vrn"
	},
	{
		.name = "get-period",
		.func_2 = mtd_vat_get_period,
		.func = FUNC_2,
		.nr_req_args = 2,
		.args = "vrn periodKey"
	}, {
		.name = "list-liabilities",
		.func_2 = mtd_vat_list_liabilities,
		.func = FUNC_2,
		.nr_req_args = 2,
		.args = "vrn from=YYYY-MM-DD,to=YYYY-MM-DD"
	}, {
		.name = "list-payments",
		.func_2 = mtd_vat_list_payments,
		.func = FUNC_2,
		.nr_req_args = 2,
		.args = "vrn from=YYYY-MM-DD,to=YYYY-MM-DD"
	},

	{ }
};

const struct _endpoint ENDPOINT = {
	.endpoints = endpoints,
	.api_name = API_NAME,
	.cmds = CMDS
};
