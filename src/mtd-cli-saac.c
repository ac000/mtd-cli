/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-saac.c - Make Tax Digital - Self-Assessment Accounts
 *
 * Copyright (C) 2020 - 2022	Andrew Clayton <andrew@digital-domain.net>
 */

#include <stddef.h>

#include <libmtdac/mtd-saac.h>

#include "mtd-cli.h"

#define API	saac

#define API_NAME "Self-Assessment Accounts"
#define CMDS \
"Payments and Liabilities\n\n"\
"get-balance list-transactions get-transaction list-charges get-charge\n"\
"list-payments get-payment\n\n"\
"Coding Out Underpayments and Debts\n\n"\
"co-get co-set co-delete"

static const struct endpoint endpoints[] = {
	/* Payments and Liabilities */
	{
		.name = "get-balance",
		.func_0 = mtd_saac_get_balance,
		.func = FUNC_0,
		.nr_req_args = 0,
		.args = ""
	}, {
		.name = "list-transactions",
		.func_1 = mtd_saac_list_transactions,
		.func = FUNC_1,
		.nr_req_args = 1,
		.args = "from=YYYY-MM-DD,to=YYYY-MM-DD"
	}, {
		.name = "get-transaction",
		.func_1 = mtd_saac_get_transaction,
		.func = FUNC_1,
		.nr_req_args = 1,
		.args = "transactionId"
	}, {
		.name = "list-charges",
		.func_1 = mtd_saac_list_charges,
		.func = FUNC_1,
		.nr_req_args = 1,
		.args = "from=YYYY-MM-DD,to=YYYY-MM-DD"
	}, {
		.name = "get-charge",
		.func_1 = mtd_saac_get_charge,
		.func = FUNC_1,
		.nr_req_args = 1,
		.args = "transactionId"
	}, {
		.name = "list-payments",
		.func_1 = mtd_saac_list_payments,
		.func = FUNC_1,
		.nr_req_args = 1,
		.args = "from=YYYY-MM-DD,to=YYYY-MM-DD"
	}, {
		.name = "get-payment",
			.func_1 = mtd_saac_get_payment,
		.func = FUNC_1,
		.nr_req_args = 1,
		.args = "paymentId"
	},
	/* Coding Out Underpayments and Debts */
	{
		.name = "co-get",
		.func_1 = mtd_saac_get_coding_out_uda,
		.func = FUNC_1,
		.nr_req_args = 1,
		.args = "taxYear"
	}, {
		.name = "co-set",
		.func_2d = mtd_saac_set_coding_out_uda,
		.func = FUNC_2d,
		.nr_req_args = 2,
		.args = "<file> taxYear"
	}, {
		.name = "co-delete",
		.func_1 = mtd_saac_delete_coding_out_uda,
		.func = FUNC_1,
		.nr_req_args = 1,
		.args = "taxYear"
	},

	{ }
};

const struct _endpoint ENDPOINT = {
	.endpoints = endpoints,
	.api_name = API_NAME,
	.cmds = CMDS
};
