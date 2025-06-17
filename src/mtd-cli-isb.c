/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-isb.c - Make Tax Digital - Individuals State Benefits
 *
 * Copyright (C) 2025		Andrew Clayton <ac@sigsegv.uk>
 */

#include <stdbool.h>

#include <libmtdac/mtd.h>

#include "mtd-cli.h"

#define API	isb

#define API_NAME "Individuals State Benefits"
#define CMDS \
"Individuals State Benefits\n\n"\
"create list amend delete amend-amnts delete-amnts ignore unignore"

static const struct endpoint endpoints[] = {
	{
		.name		= "create",
		.api_ep		= MTD_API_EP_ISB_CREATE,
		.nr_req_args	= 2,
		.file_data	= true,
		.args		= "<file> taxYear"
	}, {
		.name		= "list",
		.api_ep		= MTD_API_EP_ISB_LIST,
		.nr_req_args	= 1,
		.args		= "taxYear [benefitId=]"
	}, {
		.name		= "amend",
		.api_ep		= MTD_API_EP_ISB_AMEND,
		.nr_req_args	= 3,
		.file_data	= true,
		.args		= "<file> taxYear benefitId"
	}, {
		.name		= "delete",
		.api_ep		= MTD_API_EP_ISB_DELETE,
		.nr_req_args	= 2,
		.args		= "taxYear benefitId"
	}, {
		.name		= "amend-amnts",
		.api_ep		= MTD_API_EP_ISB_AMEND_AMNTS,
		.nr_req_args	= 3,
		.file_data	= true,
		.args		= "<file> taxYear benefitId"
	}, {
		.name		= "delete-amnts",
		.api_ep		= MTD_API_EP_ISB_DELETE_AMNTS,
		.nr_req_args	= 2,
		.args		= "taxYear benefitId"
	}, {
		.name		= "ignore",
		.api_ep		= MTD_API_EP_ISB_IGNORE,
		.nr_req_args	= 2,
		.args		= "taxYear benefitId"
	}, {
		.name		= "unignore",
		.api_ep		= MTD_API_EP_ISB_UNIGNORE,
		.nr_req_args	= 2,
		.args		= "taxYear benefitId"
	},

	{ }
};

const struct _endpoint ENDPOINT = {
	.endpoints = endpoints,
	.api_name = API_NAME,
	.cmds = CMDS
};
