/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-saac.c - Make Tax Digital - Self-Assessment Accounts
 *
 * Copyright (C) 2020 - 2021	Andrew Clayton <andrew@digital-domain.net>
 */

#include <stddef.h>

#include <libmtdac/mtd-saac.h>

#include "mtd-cli.h"

#define API	saac

#define API_NAME "Self-Assessment Accounts"
#define CMDS \
"get-balance list-transactions get-transaction list-charges get-charge\n"\
"list-payments get-payment"

static const struct endpoint endpoints[] = {
	{
		.name = "get-balance",
		.api_func = {
			.func_0 = mtd_saac_get_balance
		},
		.func = FUNC_0,
		.nr_req_args = 0,
		.use = "get-balance"
	},
	{
		.name = "list-transactions",
		.api_func = {
			.func_1 = mtd_saac_list_transactions
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = "list-transactions from=YYYY-MM-DD,to=YYYY-MM-DD"
	},
	{
		.name = "get-transaction",
		.api_func = {
			.func_1 = mtd_saac_get_transaction
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = "get-transaction transactionId"
	},
	{
		.name = "list-charges",
		.api_func = {
			.func_1 = mtd_saac_list_charges
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = "list-charges from=YYYY-MM-DD,to=YYYY-MM-DD"
	},
	{
		.name = "get-charge",
		.api_func = {
			.func_1 = mtd_saac_get_charge
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = "get-charge transactionId"
	},
	{
		.name = "list-payments",
		.api_func = {
			.func_1 = mtd_saac_list_payments
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = "list-payments from=YYYY-MM-DD,to=YYYY-MM-DD"
	},
	{
		.name = "get-payment",
		.api_func = {
			.func_1 = mtd_saac_get_payment
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = "get-payment paymentId"
	},

	{ }
};

const struct _endpoint ENDPOINT = {
	.endpoints = endpoints,
	.api_name = API_NAME,
	.cmds = CMDS
};
