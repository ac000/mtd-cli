/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-ir.c - Make Tax Digital - Individuals Reliefs
 *
 * Copyright (C) 2025		Andrew Clayton <ac@sigsegv.uk>
 */

#include <stdbool.h>

#include <libmtdac/mtd.h>

#include "mtd-cli.h"

#define API	ir

#define API_NAME "Individuals Reliefs"
#define CMDS \
"Relief Investments\n\n"\
"ri-get ri-amend ri-delete\n\n"\
"Other Reliefs\n\n"\
"or-get or-amend or-delete\n\n"\
"Foreign Reliefs\n\n"\
"fr-get fr-amend fr-delete\n\n"\
"Pensions Reliefs\n\n"\
"pr-get pr-amend pr-delete\n\n"\
"Charitable Givings\n\n"\
"cg-get cg-amend cg-delete\n\n"\

static const struct endpoint endpoints[] = {
	/* Relief Investments */
	{
		.name		= "ri-get",
		.api_ep		= MTD_API_EP_IR_RI_GET,
		.nr_req_args	= 1,
		.args		= "taxYear"
	}, {
		.name		= "ri-amend",
		.api_ep		= MTD_API_EP_IR_RI_AMEND,
		.nr_req_args	= 2,
		.file_data	= true,
		.args		= "<file> taxYear"
	}, {
		.name		= "ri-delete",
		.api_ep		= MTD_API_EP_IR_RI_DELETE,
		.nr_req_args	= 1,
		.args		= "taxYear"
	},
	/* Other Reliefs */
	{
		.name		= "or-get",
		.api_ep		= MTD_API_EP_IR_OR_GET,
		.nr_req_args	= 1,
		.args		= "taxYear"
	}, {
		.name		= "or-amend",
		.api_ep		= MTD_API_EP_IR_OR_AMEND,
		.nr_req_args	= 2,
		.file_data	= true,
		.args		= "<file> taxYear"
	}, {
		.name		= "or-delete",
		.api_ep		= MTD_API_EP_IR_OR_DELETE,
		.nr_req_args	= 1,
		.args		= "taxYear"
	},
	/* Foreign Reliefs */
	{
		.name		= "fr-get",
		.api_ep		= MTD_API_EP_IR_FR_GET,
		.nr_req_args	= 1,
		.args		= "taxYear"
	}, {
		.name		= "fr-amend",
		.api_ep		= MTD_API_EP_IR_FR_AMEND,
		.nr_req_args	= 2,
		.file_data	= true,
		.args		= "<file> taxYear"
	}, {
		.name		= "fr-delete",
		.api_ep		= MTD_API_EP_IR_FR_DELETE,
		.nr_req_args	= 1,
		.args		= "taxYear"
	},
	/* Pensions Reliefs */
	{
		.name		= "pr-get",
		.api_ep		= MTD_API_EP_IR_PR_GET,
		.nr_req_args	= 1,
		.args		= "taxYear"
	}, {
		.name		= "pr-amend",
		.api_ep		= MTD_API_EP_IR_PR_AMEND,
		.nr_req_args	= 2,
		.file_data	= true,
		.args		= "<file> taxYear"
	}, {
		.name		= "pr-delete",
		.api_ep		= MTD_API_EP_IR_PR_DELETE,
		.nr_req_args	= 1,
		.args		= "taxYear"
	},
	/* Charitable Givings */
	{
		.name		= "cg-get",
		.api_ep		= MTD_API_EP_IR_CG_GET,
		.nr_req_args	= 1,
		.args		= "taxYear"
	}, {
		.name		= "cg-amend",
		.api_ep		= MTD_API_EP_IR_CG_AMEND,
		.nr_req_args	= 2,
		.file_data	= true,
		.args		= "<file> taxYear"
	}, {
		.name		= "cg-delete",
		.api_ep		= MTD_API_EP_IR_CG_DELETE,
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
