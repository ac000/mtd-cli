/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-biss.c - Make Tax Digital - Business Income Source Summary
 *
 * Copyright (C) 2025		Andrew Clayton <ac@sigsegv.uk>
 */

#include <libmtdac/mtd.h>

#include "mtd-cli.h"

#define API	biss

#define API_NAME "Business Income Source Summary"
#define CMDS \
"get"

static const struct endpoint endpoints[] = {
	{
		.name		= "get",
		.api_ep		= MTD_API_EP_BISS_GET,
		.nr_req_args	= 3,
		.args		= "typeOfBusiness taxYear businessId"
	},

	{ }
};

const struct _endpoint ENDPOINT = {
	.endpoints = endpoints,
	.api_name = API_NAME,
	.cmds = CMDS
};
