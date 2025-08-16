/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-od.c - Make Tax Digital - Other Deductions
 *
 * Copyright (C) 2025		Andrew Clayton <ac@sigsegv.uk>
 */

#include <stdbool.h>

#include <libmtdac/mtd.h>

#include "mtd-cli.h"

#define API	od

#define API_NAME "Other Deductions"
#define CMDS \
"amend get delete"

static const struct endpoint endpoints[] = {
	{
		.name		= "amend",
		.api_ep		= MTD_API_EP_OD_AMEND,
		.nr_req_args	= 2,
		.file_data	= true,
		.args		= "<file> taxYear"
	}, {
		.name		= "get",
		.api_ep		= MTD_API_EP_OD_GET,
		.nr_req_args	= 1,
		.args		= "taxYear"
	}, {
		.name		= "delete",
		.api_ep		= MTD_API_EP_OD_DELETE,
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
