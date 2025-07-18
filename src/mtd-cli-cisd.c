/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-cisd.c - Make Tax Digital - CIS Deductions
 *
 * Copyright (C) 2025		Andrew Clayton <ac@sigsegv.uk>
 */

#include <stdbool.h>

#include <libmtdac/mtd.h>

#include "mtd-cli.h"

#define API	cisd

#define API_NAME "CIS Deductions"
#define CMDS \
"get create amend delete"

static const struct endpoint endpoints[] = {
	{
		.name		= "get",
		.api_ep		= MTD_API_EP_CISD_GET,
		.nr_req_args	= 2,
		.args		= "taxYear source"
	}, {
		.name		= "create",
		.api_ep		= MTD_API_EP_CISD_CREATE,
		.nr_req_args	= 1,
		.file_data	= true,
		.args		= "<file>"
	}, {
		.name		= "amend",
		.api_ep		= MTD_API_EP_CISD_AMEND,
		.nr_req_args	= 2,
		.file_data	= true,
		.args		= "<file> submissionId"
	}, {
		.name		= "delete",
		.api_ep		= MTD_API_EP_CISD_DELETE,
		.nr_req_args	= 2,
		.args		= "submissionId taxYear"
	},

	{ }
};

const struct _endpoint ENDPOINT = {
	.endpoints = endpoints,
	.api_name = API_NAME,
	.cmds = CMDS
};
