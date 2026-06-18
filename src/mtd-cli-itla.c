/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-itla.c - Make Tax Digital - Individuals Tax Liability Adjustments
 *
 * Copyright (C) 2026		Andrew Clayton <ac@sigsegv.uk>
 */

#include <stdbool.h>

#include <libmtdac/mtd.h>

#include "mtd-cli.h"

#define API	itla

#define API_NAME "Individuals Tax Liability Adjustments"
#define CMDS \
"get update delete"

static const struct endpoint endpoints[] = {
	{
		.name		= "get",
		.api_ep		= MTD_API_EP_ITLA_GET,
		.nr_req_args	= 1,
		.args		= "taxYear"
	}, {
		.name		= "update",
		.api_ep		= MTD_API_EP_ITLA_UPDATE,
		.nr_req_args	= 2,
		.file_data	= true,
		.args		= "<file> taxYear"
	}, {
		.name		= "delete",
		.api_ep		= MTD_API_EP_ITLA_DELETE,
		.nr_req_args	= 1,
		.args		= "taxYear"
	},

	{}
};

const struct _endpoint ENDPOINT = {
	.endpoints = endpoints,
	.api_name = API_NAME,
	.cmds = CMDS
};
