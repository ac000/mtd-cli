/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-iei.c - Make Tax Digital - Individuals Employments Income
 *
 * Copyright (C) 2025		Andrew Clayton <ac@sigsegv.uk>
 */

#include <stdbool.h>

#include <libmtdac/mtd.h>

#include "mtd-cli.h"

#define API	iei

#define API_NAME "Individuals Employments Income"
#define CMDS \
"Employments\n\n"\
"list add get amend delete ignore unignore efd-get efd-amend efd-delete\n\n"\
"Non-PAYE Employment Income\n\n"\
"npe-get npe-amend npe-delete\n\n"\
"Other Employment Income\n\n"\
"oe-get oe-amend oe-delete"

static const struct endpoint endpoints[] = {
	/* Employments */
	{
		.name		= "list",
		.api_ep		= MTD_API_EP_IEI_E_LIST,
		.nr_req_args	= 1,
		.args		= "taxYear"
	}, {
		.name		= "add",
		.api_ep		= MTD_API_EP_IEI_E_ADD,
		.nr_req_args	= 1,
		.args		= "taxYear"
	}, {
		.name		= "get",
		.api_ep		= MTD_API_EP_IEI_E_GET,
		.nr_req_args	= 2,
		.args		= "taxYear employmentId"
	}, {
		.name		= "amend",
		.api_ep		= MTD_API_EP_IEI_E_AMEND,
		.nr_req_args	= 3,
		.file_data	= true,
		.args		= "<file> taxYear employmentId"
	}, {
		.name		= "delete",
		.api_ep		= MTD_API_EP_IEI_E_DELETE,
		.nr_req_args	= 2,
		.args		= "taxYear employmentId"
	}, {
		.name		= "ignore",
		.api_ep		= MTD_API_EP_IEI_E_IGNORE,
		.nr_req_args	= 2,
		.args		= "taxYear employmentId"
	}, {
		.name		= "unignore",
		.api_ep		= MTD_API_EP_IEI_E_UNIGNORE,
		.nr_req_args	= 2,
		.args		= "taxYear employmentId"
	}, {
		.name		= "efd-get",
		.api_ep		= MTD_API_EP_IEI_E_EFD_GET,
		.nr_req_args	= 2,
		.args		= "taxYear employmentId [source={user,hmrc-held,latest}]"
	}, {
		.name		= "efd-amend",
		.api_ep		= MTD_API_EP_IEI_E_EFD_AMEND,
		.nr_req_args	= 3,
		.file_data	= true,
		.args		= "<file> taxYear employmentId"
	}, {
		.name		= "efd-delete",
		.api_ep		= MTD_API_EP_IEI_E_EFD_DELETE,
		.nr_req_args	= 2,
		.args		= "taxYear employmentId"
	},
	/* Non-PAYE Employment Income */
	{
		.name		= "npe-get",
		.api_ep		= MTD_API_EP_IEI_NPE_GET,
		.nr_req_args	= 1,
		.args		= "taxYear [source={user,hmrc-held,latest}]"
	}, {
		.name		= "mpe-amend",
		.api_ep		= MTD_API_EP_IEI_NPE_AMEND,
		.nr_req_args	= 2,
		.file_data	= true,
		.args		= "<file> taxYear"
	}, {
		.name		= "npe-delete",
		.api_ep		= MTD_API_EP_IEI_NPE_DELETE,
		.nr_req_args	= 1,
		.args		= "taxYear"
	},
	/* Other Employment Income */
	{
		.name		= "oe-get",
		.api_ep		= MTD_API_EP_IEI_OE_GET,
		.nr_req_args	= 1,
		.args		= "taxYear"
	}, {
		.name		= "oe-amend",
		.api_ep		= MTD_API_EP_IEI_OE_AMEND,
		.nr_req_args	= 2,
		.file_data	= true,
		.args		= "<file> taxYear"
	}, {
		.name		= "oe-delete",
		.api_ep		= MTD_API_EP_IEI_OE_DELETE,
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
