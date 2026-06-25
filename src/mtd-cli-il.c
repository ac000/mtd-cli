/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-il.c - Make Tax Digital - Individuals Losses
 *
 * Copyright (C) 2020 - 2026	Andrew Clayton <ac@sigsegv.uk>
 */

#include <stdbool.h>

#include <libmtdac/mtd.h>

#include "mtd-cli.h"

#define API	il

#define API_NAME "Individuals Losses"
#define CMDS \
"get amend delete\n\n"\

static const struct endpoint endpoints[] = {
	{
		.name		= "get",
		.api_ep		= MTD_API_EP_IL_GET,
		.nr_req_args	= 2,
		.args		= "businessId taxYear"
	}, {
		.name		= "amend",
		.api_ep		= MTD_API_EP_IL_AMEND,
		.nr_req_args	= 3,
		.file_data	= true,
		.args		= "<file> businessId taxYear"
	}, {
		.name		= "delete",
		.api_ep		= MTD_API_EP_IL_DELETE,
		.nr_req_args	= 2,
		.args		= "businessId taxYear"
	},

	{ }
};

const struct _endpoint ENDPOINT = {
	.endpoints = endpoints,
	.api_name = API_NAME,
	.cmds = CMDS
};
