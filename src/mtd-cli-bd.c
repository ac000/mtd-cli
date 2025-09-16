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
#define CMDS \
"Support\n\n"\
"list get amend-qpt\n\n"\
"Accounting Type\n\n"\
"at-get at-amend\n\n"\
"Periods of Account\n\n"\
"poa-get poa-amend\n\n"\
"Late Accounting Date Rule\n\n"\
"ladr-get ladr-disapply ladr-withdraw"

static const struct endpoint endpoints[] = {
	/* Support */
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
	/* Accounting Type */
	{
		.name		= "at-get",
		.api_ep		= MTD_API_EP_BD_AT_GET,
		.nr_req_args	= 2,
		.args		= "businessId taxYear"
	}, {
		.name		= "at-amend",
		.api_ep		= MTD_API_EP_BD_AT_AMEND,
		.nr_req_args	= 3,
		.file_data	= true,
		.args		= "<file> businessId taxYear"
	},
	/* Periods of Account */
	{
		.name		= "poa-get",
		.api_ep		= MTD_API_EP_BD_POA_GET,
		.nr_req_args	= 2,
		.args		= "businessId taxYear"
	}, {
		.name		= "poa-amend",
		.api_ep		= MTD_API_EP_BD_POA_AMEND,
		.nr_req_args	= 3,
		.file_data	= true,
		.args		= "<file> businessId taxYear"
	},
	/* Late Accounting Date Rule */
	{
		.name		= "ladr-get",
		.api_ep		= MTD_API_EP_BD_LADR_GET,
		.nr_req_args	= 2,
		.args		= "businessId taxYear"
	}, {
		.name		= "ladr-disapply",
		.api_ep		= MTD_API_EP_BD_LADR_DISAPPLY,
		.nr_req_args	= 2,
		.args		= "businessId taxYear"
	}, {
		.name		= "ladr-withdraw",
		.api_ep		= MTD_API_EP_BD_LADR_WITHDRAW,
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
