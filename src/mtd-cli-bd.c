/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-bd.c - Make Tax Digital - Business Details
 *
 * Copyright (C) 2021 - 2025	Andrew Clayton <ac@sigsegv.uk>
 */

#include <stdbool.h>

#include <libmtdac/mtd.h>

#include "mtd-cli.h"

#define API	bd

#define API_NAME "Business Details"
#define CMDS "list get amend-qpt"

static const struct endpoint endpoints[] = {
	{
		.name		= "list",
		.api_ep		= MTD_API_EP_BD_LIST,
		.nr_req_args	= 0,
		.args		= ""
	}, {
		.name		= "get",
		.api_ep		= MTD_API_EP_BD_GET,
		.nr_req_args	= 1,
		.args		= "businessId"
	}, {
		.name		= "amend-qpt",
		.api_ep		= MTD_API_EP_BD_AMEND_QPT,
		.nr_req_args	= 3,
		.file_data	= true,
		.args		= "<file> businessId taxYear"
	},

	{ }
};

const struct _endpoint ENDPOINT = {
	.endpoints = endpoints,
	.api_name = API_NAME,
	.cmds = CMDS
};
