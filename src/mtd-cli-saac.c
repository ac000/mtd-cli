/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-saac.c - Make Tax Digital - Self-Assessment Accounts
 *
 * Copyright (C) 2020		Andrew Clayton <andrew@digital-domain.net>
 */

#include <stdio.h>

#include <libmtdac/mtd-saac.h>

#include "mtd-cli.h"

#define MTD_CLI_CMD	MTD_CLI " saac "
#define API_NAME	"Self-Assessment Accounts"

#define ENDPOINTS \
"get-balance list-transactions get-transaction list-charges get-charge\n"\
"list-payments get-payment"

static int print_endpoints(void)
{
	printf("Available " API_NAME " endpoints :-\n\n%s\n", ENDPOINTS);

	return -1;
}

static const struct endpoint endpoints[] = {
	{
		.name = "get-balance",
		.api_func = {
			.func_0 = &mtd_saac_get_balance
		},
		.func = FUNC_0,
		.nr_req_args = 0,
		.use = MTD_CLI_CMD "get-balance"
	},
	{
		.name = "list-transactions",
		.api_func = {
			.func_2 = &mtd_saac_list_transactions
		},
		.func = FUNC_2,
		.nr_req_args = 2,
		.use = MTD_CLI_CMD "list-transactions from to"
	},
	{
		.name = "get-transaction",
		.api_func = {
			.func_1 = &mtd_saac_get_transaction
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = MTD_CLI_CMD "get-transaction transactionId"
	},
	{
		.name = "list-charges",
		.api_func = {
			.func_2 = &mtd_saac_list_charges
		},
		.func = FUNC_2,
		.nr_req_args = 2,
		.use = MTD_CLI_CMD "list-charges from to"
	},
	{
		.name = "get-charge",
		.api_func = {
			.func_1 = &mtd_saac_get_charge
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = MTD_CLI_CMD "get-charge transactionId" },
	{
		.name = "list-payments",
		.api_func = {
			.func_2 = &mtd_saac_list_payments
		},
		.func = FUNC_2,
		.nr_req_args = 2,
		.use = MTD_CLI_CMD "list-payments from to" },
	{
		.name = "get-payment",
		.api_func = {
			.func_1 = &mtd_saac_get_payment
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = MTD_CLI_CMD "get-payment paymentId"
	},
	{ NULL, { NULL }, 0, 0, NULL }
};

const struct _endpoint saac_endpoint = {
	.endpoints = endpoints,
	.print_help = &print_endpoints
};
