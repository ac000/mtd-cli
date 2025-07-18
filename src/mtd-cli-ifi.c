/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-ifi.c - Make Tax Digital - Individuals Foreign Income
 *
 * Copyright (C) 2025		Andrew Clayton <ac@sigsegv.uk>
 */

#include <stdbool.h>

#include <libmtdac/mtd.h>

#include "mtd-cli.h"

#define API	ifi

#define API_NAME "Individuals Foreign Income"
#define CMDS \
"get amend delete"

static const struct endpoint endpoints[] = {
	{
		.name		= "get",
		.api_ep		= MTD_API_EP_IFI_GET,
		.nr_req_args	= 1,
		.args		= "taxYear"
	}, {
		.name		= "amend",
		.api_ep		= MTD_API_EP_IFI_AMEND,
		.nr_req_args	= 2,
		.file_data	= true,
		.args		= "<file> taxYear"
	}, {
		.name		= "delete",
		.api_ep		= MTD_API_EP_IFI_DELETE,
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
