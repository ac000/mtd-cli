/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-vat.c - Make Tax Digital - VAT
 *
 * Copyright (C) 2020 - 2025	Andrew Clayton <ac@sigsegv.uk>
 */

#include <libmtdac/mtd.h>

#include "mtd-cli.h"

#define API	vat

#define API_NAME "VAT"
#define CMDS \
"list-obligations submit-period view-return get-liabilities get-payments\n"\
"get-penalties get-financial-details"

static const struct endpoint endpoints[] = {
	{
		.name		= "list-obligations",
		.api_ep		= MTD_API_EP_VAT_LIST_OBLIGATIONS,
		.nr_req_args	= 1,
		.args		= "vrn [from=YYY-MM-DD][,[to=YYYY-MM-DD]][,[status=O|F]]"
	}, {
		.name		= "submit-period",
		.api_ep		= MTD_API_EP_VAT_SUBMIT,
		.nr_req_args	= 2,
		.args		= "<file> vrn"
	}, {
		.name		= "view-return",
		.api_ep		= MTD_API_EP_VAT_VIEW_RETURN,
		.nr_req_args	= 2,
		.args		= "vrn periodKey"
	}, {
		.name		= "get-liabilities",
		.api_ep		= MTD_API_EP_VAT_GET_LIABILITIES,
		.nr_req_args	= 2,
		.args		= "vrn from=YYYY-MM-DD,to=YYYY-MM-DD"
	}, {
		.name		= "get-payments",
		.api_ep		= MTD_API_EP_VAT_GET_PAYMENTS,
		.nr_req_args	= 2,
		.args		= "vrn from=YYYY-MM-DD,to=YYYY-MM-DD"
	}, {
		.name		= "get-penalties",
		.api_ep		= MTD_API_EP_VAT_GET_PENALTIES,
		.nr_req_args	= 1,
		.args		= "vrn"
	}, {
		.name		= "get-financial-details",
		.api_ep		= MTD_API_EP_VAT_GET_FINANCIAL_DETAILS,
		.nr_req_args	= 2,
		.args		= "vrn penaltyChargeReference"
	},

	{ }
};

const struct _endpoint ENDPOINT = {
	.endpoints = endpoints,
	.api_name = API_NAME,
	.cmds = CMDS
};
