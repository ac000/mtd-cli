/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-ical.c - Make Tax Digital - Individual Calculations
 *
 * Copyright (C) 2020 - 2025	Andrew Clayton <ac@sigsegv.uk>
 */

#include <libmtdac/mtd.h>

#include "mtd-cli.h"

#define API	ical

#define API_NAME "Individual Calculations"
#define CMDS \
"TAX Calculations\n\n"\
"list-calculations-old list-calculations trigger-calculation\n"\
"get-calculation\n\n"\
"Final Declaration\n\n"\
"final-declaration"

static const struct endpoint endpoints[] = {
	{
		.name		= "list-calculations-old",
		.api_ep		= MTD_API_EP_ICAL_LIST_OLD,
		.nr_req_args	= 1,
		.args		= "taxYear=YYYY-YY"
	}, {
		.name		= "list-calculations",
		.api_ep		= MTD_API_EP_ICAL_LIST,
		.nr_req_args	= 1,
		.args		= "taxYear [calculationType=in-year|intent-to-finalise|intent-to-amend|final-declaration|confirm-amendment]",
	}, {
		.name		= "trigger-calculation",
		.api_ep		= MTD_API_EP_ICAL_TRIGGER,
		.nr_req_args	= 2,
		.args		= "taxYear calculationType"
	}, {
		.name		= "get-calculation",
		.api_ep		= MTD_API_EP_ICAL_GET,
		.nr_req_args	= 2,
		.args		= "taxYear calculationId"
	}, {
		.name		= "final-declaration",
		.api_ep		= MTD_API_EP_ICAL_FINAL_DECLARATION,
		.nr_req_args	= 3,
		.args		= "taxYear calculationId calculationType"
	},

	{ }
};

const struct _endpoint ENDPOINT = {
	.endpoints = endpoints,
	.api_name = API_NAME,
	.cmds = CMDS
};
