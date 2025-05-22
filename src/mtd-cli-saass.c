/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-ipi.c - Make Tax Digital - Self Assessment Assist
 *
 * Copyright (C) 2025		Andrew Clayton <ac@sigsegv.uk>
 */

#include <libmtdac/mtd.h>

#include "mtd-cli.h"

#define API	saass

#define API_NAME "Self Assessment Assist"
#define CMDS \
"gen-report ack-report"

static const struct endpoint endpoints[] = {
	{
		.name		= "gen-report",
		.api_ep		= MTD_API_EP_SAASS_REPORT_GEN,
		.nr_req_args	= 2,
		.args		= "taxYear calculationId"
	}, {
		.name		= "ack-report",
		.api_ep		= MTD_API_EP_SAASS_REPORT_ACK,
		.nr_req_args	= 2,
		.args		= "taxYear correlationId"
	},

	{ }
};

const struct _endpoint ENDPOINT = {
	.endpoints = endpoints,
	.api_name = API_NAME,
	.cmds = CMDS
};
