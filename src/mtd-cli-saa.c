/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-saa.c - Make Tax Digital - Self Assessment Accounts
 *
 * Copyright (C) 2025		Andrew Clayton <ac@sigsegv.uk>
 */

#include <stdbool.h>

#include <libmtdac/mtd.h>

#include "mtd-cli.h"

#define API	saa

#define API_NAME "Self Assessment Accounts"
#define CMDS \
"Payments and Liabilities\n\n"\
"history get-by-trans-id get-by-charge-ref get-bal-trans pa-list\n\n"\
"Coding Out Underpayments and Debts\n\n"\
"coud-get coud-amend coud-delete\n\n"\
"Coding Out Status\n\n"\
"cos-opt-out cos-opt-in cos-opt-status"

static const struct endpoint endpoints[] = {
	/* Payments and Liabilities */
	{
		.name		= "history",
		.api_ep		= MTD_API_EP_SAA_PL_HIST,
		.nr_req_args	= 1,
		.args		= "transactionId"
	}, {
		.name		= "get-by-trans-id",
		.api_ep		= MTD_API_EP_SAA_PL_GET_BY_TID,
		.nr_req_args	= 1,
		.args		= "transactionId"
	}, {
		.name		= "get-by-charge-ref",
		.api_ep		= MTD_API_EP_SAA_PL_GET_BY_CR,
		.nr_req_args	= 1,
		.args		= "chargeReference"
	}, {
		.name		= "get-bal-trans",
		.api_ep		= MTD_API_EP_SAA_PL_GET_BAL_TRANS,
		.nr_req_args	= 1,
		.args		= "[docNumber=][,][fromDate=][,][toDate=][,][onlyOpenItems={true|false}][,][includeLocks={true|false}][,][calculateAccruedInterest={true|false}][,][removePOA={true|false}][,][customerPaymentInformation={true|false}][,][includeEstimatedCharges={true|false}]"
	}, {
		.name		= "pa-list",
		.api_ep		= MTD_API_EP_SAA_PL_PA_LIST,
		.nr_req_args	= 0,
		.args		= "[[fromDate=][,][toDate=][,][paymentLot=][,][paymentLotItem=}]]"
	},
	/* Coding Out Underpayments and Debts */
	{
		.name		= "coud-get",
		.api_ep		= MTD_API_EP_SAA_COUD_GET,
		.nr_req_args	= 1,
		.args		= "taxYear [source={hmrcHeld,user,latest}]"
	}, {
		.name		= "coud-amend",
		.api_ep		= MTD_API_EP_SAA_COUD_AMEND,
		.nr_req_args	= 2,
		.file_data	= true,
		.args		= "<file> taxYear"
	}, {
		.name		= "coud-delete",
		.api_ep		= MTD_API_EP_SAA_COUD_DELETE,
		.nr_req_args	= 1,
		.args		= "taxYear"
	},
	/* Coding Out Status */
	{
		.name		= "cos-opt-out",
		.api_ep		= MTD_API_EP_SAA_COS_OPT_OUT,
		.nr_req_args	= 1,
		.args		= "taxYear"
	}, {
		.name		= "cos-opt-in",
		.api_ep		= MTD_API_EP_SAA_COS_OPT_IN,
		.nr_req_args	= 1,
		.args		= "taxYear"
	}, {
		.name		= "cos-opt-status",
		.api_ep		= MTD_API_EP_SAA_COS_OPT_STATUS,
		.nr_req_args	= 1,
		.args		= "taxYear"
	},

	{ }
};

const struct _endpoint ENDPOINT = {
	.endpoints = endpoints,
	.api_name = API_NAME,
	.cmds = CMDS
};
