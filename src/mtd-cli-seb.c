/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-seb.c - Make Tax Digital - Self Employment Business
 *
 * Copyright (C) 2025		Andrew Clayton <ac@sigsegv.uk>
 */

#include <stdbool.h>

#include <libmtdac/mtd.h>

#include "mtd-cli.h"

#define API	seb

#define API_NAME "Self Employment Business"
#define CMDS \
"Annual Submission\n\n"\
"as-update as-get as-delete\n\n"\
"Period Summaries\n\n"\
"ps-create ps-list ps-update ps-get\n\n"\
"Cumulative Period Summary\n\n"\
"cps-update cps-get"

static const struct endpoint endpoints[] = {
	/* Annual Submission */
	{
		.name		= "as-update",
		.api_ep		= MTD_API_EP_SEB_SEAS_AMEND,
		.nr_req_args	= 3,
		.file_data	= true,
		.args		= "<file> businessId taxYear"
	}, {
		.name		= "as-get",
		.api_ep		= MTD_API_EP_SEB_SEAS_GET,
		.nr_req_args	= 2,
		.args		= "businessId taxYear"
	}, {
		.name		= "as-delete",
		.api_ep		= MTD_API_EP_SEB_SEAS_DELETE,
		.nr_req_args	= 2,
		.args		= "businessId taxYear"
	},
	/* Period Summaries */
	{
		.name		= "ps-create",
		.api_ep		= MTD_API_EP_SEB_SEPS_CREATE,
		.nr_req_args	= 2,
		.file_data	= true,
		.args		= "<file> businessId"
	}, {
		.name		= "ps-list",
		.api_ep		= MTD_API_EP_SEB_SEPS_LIST,
		.nr_req_args	= 2,
		.args		= "businessId taxYear"
	}, {
		.name		= "ps-update",
		.api_ep		= MTD_API_EP_SEB_SEPS_AMEND,
		.nr_req_args	= 4,
		.file_data	= true,
		.args		= "<file> businessId taxYear periodId"
	}, {
		.name		= "ps-get",
		.api_ep		= MTD_API_EP_SEB_SEPS_GET,
		.nr_req_args	= 3,
		.args		= "businessId taxYear periodId"
	},
	/* Cumulative Period Summary */
	{
		.name		= "cps-update",
		.api_ep		= MTD_API_EP_SEB_SECPS_AMEND,
		.nr_req_args	= 3,
		.file_data	= true,
		.args		= "<file> businessId taxYear"
	}, {
		.name		= "cps-get",
		.api_ep		= MTD_API_EP_SEB_SECPS_GET,
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
