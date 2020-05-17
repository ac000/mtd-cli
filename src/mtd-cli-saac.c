/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-saac.c - make Tax Digital - Self-Assessment Accounts
 *
 * Copyright (C) 2020		Andrew Clayton <andrew@digital-domain.net>
 */

#include <stdio.h>

#include <libmtdac/mtd-saac.h>

#include "mtd-cli.h"

#define MTD_CLI_SAAC	MTD_CLI " saac "

#define SAAC_ENDPOINTS \
"get-balance list-transactions get-transaction list-charges get-charge\n"\
"list-payments get-payment"\

static const struct endpoint_help saac_endpoint_help[] = {
	{ "get-balance", MTD_CLI_SAAC "get-balance", 0 },
	{ "list-transactions", MTD_CLI_SAAC "list-transactions from to", 2 },
	{ "get-transaction", MTD_CLI_SAAC "get-transaction transactionId", 1 },
	{ "list-charges", MTD_CLI_SAAC "list-charges from to", 2 },
	{ "get-charge", MTD_CLI_SAAC "get-charge transactionId", 1 },
	{ "list-payments", MTD_CLI_SAAC "list-payments from to", 2 },
	{ "get-payment", MTD_CLI_SAAC "get-payment paymentId", 1 },
	{ NULL, NULL, 0 }
};

static int print_saac_endpoints(void)
{
	printf("Available self-assessment accounts endpoints :-\n\n%s\n",
	       SAAC_ENDPOINTS);

	return -1;
}

int do_saac(int argc, char *argv[], char **buf)
{
	int err;

	err = check_args(argc, argv[0], saac_endpoint_help,
			 print_saac_endpoints);
	if (err)
		return err;

	if (IS_EP("get-balance"))
		return mtd_saac_get_balance(buf);
	else if (IS_EP("list-transactions"))
		return mtd_saac_list_transactions(argv[1], argv[2], buf);
	else if (IS_EP("get-transaction"))
		return mtd_saac_get_transaction(argv[1], buf);
	else if (IS_EP("list-charges"))
		return mtd_saac_list_charges(argv[1], argv[2], buf);
	else if (IS_EP("get-charge"))
		return mtd_saac_get_charge(argv[1], buf);
	else if (IS_EP("list-payments"))
		return mtd_saac_list_payments(argv[1], argv[2], buf);
	else if (IS_EP("get-payment"))
		return mtd_saac_get_payment(argv[1], buf);

	return -1;
}
