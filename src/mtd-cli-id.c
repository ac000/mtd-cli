/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-ie.c - Make Tax Digital - Individuals Disclosures
 *
 * Copyright (C) 2025		Andrew Clayton <ac@sigsegv.uk>
 */

#include <stdbool.h>

#include <libmtdac/mtd.h>

#include "mtd-cli.h"

#define API	id

#define API_NAME "Individuals Disclosures"
#define CMDS \
"Marriage Allowance\n\n"\
"ma-create\n\n"\
"Disclosures\n\n"\
"d-get d-amend d-delete"

static const struct endpoint endpoints[] = {
	/* Marriage Allowance */
	{
		.name		= "ma-create",
		.api_ep		= MTD_API_EP_ID_MA_CREATE,
		.nr_req_args	= 1,
		.file_data	= true,
		.args		= "<file>"
	},
	/* Disclosures */
	{
		.name		= "d-get",
		.api_ep		= MTD_API_EP_ID_D_GET,
		.nr_req_args	= 1,
		.args		= "taxYear"
	}, {
		.name		= "d-amend",
		.api_ep		= MTD_API_EP_ID_D_AMEND,
		.nr_req_args	= 2,
		.file_data	= true,
		.args		= "<file> taxYear"
	}, {
		.name		= "d-delete",
		.api_ep		= MTD_API_EP_ID_D_DELETE,
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
