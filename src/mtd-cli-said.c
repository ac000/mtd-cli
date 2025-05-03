/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-said.c - Make Tax Digital - Self Assessment Individual Details
 *
 * Copyright (C) 2025		Andrew Clayton <ac@sigsegv.uk>
 */

#include <libmtdac/mtd.h>

#include "mtd-cli.h"

#define API	said

#define API_NAME "Self Assessment Individual Details"
#define CMDS \
"ITSA Status\n\n"\
"status"

static const struct endpoint endpoints[] = {
	{
		.name		= "status",
		.api_ep		= MTD_API_EP_SAID_STATUS,
		.nr_req_args	= 1,
		.args		= "taxYear [[futureYears=true|false][,[history=true|false]]]"
	},

	{ }
};

const struct _endpoint ENDPOINT = {
	.endpoints = endpoints,
	.api_name = API_NAME,
	.cmds = CMDS
};
