/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-ie.c - Make Tax Digital - Individuals Expenses
 *
 * Copyright (C) 2025		Andrew Clayton <ac@sigsegv.uk>
 */

#include <stdbool.h>

#include <libmtdac/mtd.h>

#include "mtd-cli.h"

#define API	ie

#define API_NAME "Individuals Expenses"
#define CMDS \
"Employment Expenses\n\n"\
"amend get delete ignore\n\n"\
"Other Expenses\n\n"\
"oe-amend oe-get oe-delete"

static const struct endpoint endpoints[] = {
	/* Employment Expenses */
	{
		.name		= "amend",
		.api_ep		= MTD_API_EP_IE_EE_AMEND,
		.nr_req_args	= 2,
		.file_data	= true,
		.args		= "<file> taxYear"
	}, {
		.name		= "get",
		.api_ep		= MTD_API_EP_IE_EE_GET,
		.nr_req_args	= 1,
		.args		= "taxYear [source={user,hmrcHeld,latest}]"
	}, {
		.name		= "delete",
		.api_ep		= MTD_API_EP_IE_EE_DELETE,
		.nr_req_args	= 1,
		.args		= "taxYear"
	}, {
		.name		= "ignore",
		.api_ep		= MTD_API_EP_IE_EE_IGNORE,
		.nr_req_args	= 1,
		.args		= "taxYear"
	},
	/* Other Expenses */
	{
		.name		= "oe-amend",
		.api_ep		= MTD_API_EP_IE_OE_AMEND,
		.nr_req_args	= 2,
		.file_data	= true,
		.args		= "<file> taxYear"
	}, {
		.name		= "oe-get",
		.api_ep		= MTD_API_EP_IE_OE_GET,
		.nr_req_args	= 1,
		.args		= "taxYear"
	}, {
		.name		= "oe-delete",
		.api_ep		= MTD_API_EP_IE_OE_DELETE,
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
