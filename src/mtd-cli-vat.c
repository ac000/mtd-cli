/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-vat.c - Make Tax Digital - VAT
 *
 * Copyright (C) 2020		Andrew Clayton <andrew@digital-domain.net>
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
		.api_func = {
			.func_2 = mtd_vat_list_obligations
		},
		.func = FUNC_2,
		.nr_req_args = 1,
		.use = "list-obligations vrn [from=YYY-MM-DD][,[to=YYYY-MM-DD]][,[status=O|F]]"
	},
	{
		.name = "submit-period",
		.api_func = {
			.func_2d = mtd_vat_submit_period
		},
		.func = FUNC_2d,
		.nr_req_args = 2,
		.use = "submit-period <file> vrn"
	},
	{
		.name = "get-period",
		.api_func = {
			.func_2 = mtd_vat_get_period
		},
		.func = FUNC_2,
		.nr_req_args = 2,
		.use = "get-period vrn periodKey"
	},
	{
		.name = "list-liabilities",
		.api_func = {
			.func_2 = mtd_vat_list_liabilities
		},
		.func = FUNC_2,
		.nr_req_args = 2,
		.use = "list-liabilities vrn from=YYYY-MM-DD,to=YYYY-MM-DD"
	},
	{
		.name = "list-payments",
		.api_func = {
			.func_2 = mtd_vat_list_payments
		},
		.func = FUNC_2,
		.nr_req_args = 2,
		.use = "list-payments vrn from=YYYY-MM-DD,to=YYYY-MM-DD"
	},
	{ NULL, { NULL }, 0, 0, NULL }
};

const struct _endpoint ENDPOINT = {
	.endpoints = endpoints,
	.api_name = API_NAME,
	.cmds = CMDS
};
