/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-pb.c - Make Tax Digital - Property Business
 *
 * Copyright (C) 2025		Andrew Clayton <ac@sigsegv.uk>
 */

#include <stdbool.h>

#include <libmtdac/mtd.h>

#include "mtd-cli.h"

#define API	pb

#define API_NAME "Property Business"
#define CMDS \
"UK Property Business Annual Submission\n\n"\
"ukpbas-get ukpbas-create\n\n"\
"UK Property Income & Expenses Period Summary\n\n"\
"ukpieps-create ukpieps-get ukpieps-update\n\n"\
"UK Property Cumulative Period Summary\n\n"\
"ukpcps-get ukpcps-create\n\n"\
"Historic FHL UK Property Business Annual Submission\n\n"\
"hfhl-ukpbas-create hfhl-ukpbas-get hfhl-ukpbas-delete\n\n"\
"Historic non-FHL UK Property Business Annual Submission\n\n"\
"hnfhl-ukpbas-create hnfhl-ukpbas-get hnfhl-ukpbas-delete\n\n"\
"Historic FHL UK Property Income & Expenses Period Summary\n\n"\
"hfhl-ukpieps-list hfhl-ukpieps-create hfhl-ukpieps-update\n"\
"hfhl-ukpieps-get\n\n"\
"Historic non-FHL UK Property Income & Expenses Period Summary\n\n"\
"hnfhl-ukpieps-list hnfhl-ukpieps-create hnfhl-ukpieps-get\n"\
"hnfhl-ukpieps-update\n\n"\
"Foreign Property Income & Expenses Period Summary\n\n"\
"fpieps-create fpieps-get fpieps-update\n\n"\
"Foreign Property Cumulative Period Summary\n\n"\
"fpcps-get fpcps-update\n\n"\
"Foreign Property Annual Submission\n\n"\
"fpas-get fpas-update\n\n"\
"UK or Foreign Property Annual Submission Deletion\n\n"\
"as-delete\n\n"\
"UK or Foreign Property Income and Expenses Period Summaries List\n\n"\
"pieps-list"

static const struct endpoint endpoints[] = {
	/* UK Property Business Annual Submission */
	{
		.name		= "ukpbas-get",
		.api_ep		= MTD_API_EP_PB_UKPBAS_GET,
		.nr_req_args	= 2,
		.args		= "businessId taxYear"
	}, {
		.name		= "ukpbas-create",
		.api_ep		= MTD_API_EP_PB_UKPBAS_CREATE,
		.nr_req_args	= 3,
		.file_data	= true,
		.args		= "<file> businessId taxYear"
	},
	/* UK Property Income & Expenses Period Summary */
	{
		.name		= "ukpieps-create",
		.api_ep		= MTD_API_EP_PB_UKPIEPS_CREATE,
		.nr_req_args	= 3,
		.file_data	= true,
		.args		= "<file> businessId taxYear"
	}, {
		.name		= "ukpieps-get",
		.api_ep		= MTD_API_EP_PB_UKPIEPS_GET,
		.nr_req_args	= 3,
		.args		= "businessId taxYear submissionId"
	}, {
		.name		= "ukpieps-update",
		.api_ep		= MTD_API_EP_PB_UKPIEPS_AMEND,
		.nr_req_args	= 3,
		.file_data	= true,
		.args		= "<file> businessId taxYear submissionId"
	},
	/* UK Property Cumulative Period Summary */
	{
		.name		= "ukpcps-get",
		.api_ep		= MTD_API_EP_PB_UKPCPS_GET,
		.nr_req_args	= 2,
		.args		= "businessId taxYear"
	}, {
		.name		= "ukpcps-create",
		.api_ep		= MTD_API_EP_PB_UKPCPS_CREATE,
		.nr_req_args	= 3,
		.file_data	= true,
		.args		= "<file> businessId taxYear"
	},
	/* Historic FHL UK Property Business Annual Submission */
	{
		.name		= "hfhl-ukpbas-create",
		.api_ep		= MTD_API_EP_PB_HFHL_UKPBAS_CREATE,
		.nr_req_args	= 1,
		.file_data	= true,
		.args		= "<file> taxYear"
	}, {
		.name		= "hfhl-ukpbas-get",
		.api_ep		= MTD_API_EP_PB_HFHL_UKPBAS_GET,
		.nr_req_args	= 1,
		.args		= "taxYear"
	}, {
		.name		= "hfhl-ukpbas-delete",
		.api_ep		= MTD_API_EP_PB_HFHL_UKPBAS_DELETE,
		.nr_req_args	= 1,
		.args		= "taxYear"
	},
	/* Historic non-FHL UK Property Business Annual Submission */
	{
		.name		= "hnfhl-ukpbas-create",
		.api_ep		= MTD_API_EP_PB_HNFHL_UKPBAS_CREATE,
		.nr_req_args	= 2,
		.file_data	= true,
		.args		= "<file> taxYear"
	}, {
		.name		= "hnfhl-ukpbas-get",
		.api_ep		= MTD_API_EP_PB_HNFHL_UKPBAS_GET,
		.nr_req_args	= 1,
		.args		= "taxYear"
	}, {
		.name		= "hnfhl-ukpbas-delete",
		.api_ep		= MTD_API_EP_PB_HNFHL_UKPBAS_DELETE,
		.nr_req_args	= 1,
		.args		= "taxYear"
	},
	/* Historic FHL UK Property Income & Expenses Period Summary */
	{
		.name		= "hfhl-ukpieps-list",
		.api_ep		= MTD_API_EP_PB_HFHL_UKPIEPS_LIST,
		.nr_req_args	= 0,
		.args		= ""
	}, {
		.name		= "hfhl-ukpieps-create",
		.api_ep		= MTD_API_EP_PB_HFHL_UKPIEPS_CREATE,
		.nr_req_args	= 1,
		.file_data	= true,
		.args		= "<file>"
	}, {
		.name		= "hfhl-ukpieps-update",
		.api_ep		= MTD_API_EP_PB_HFHL_UKPIEPS_AMEND,
		.nr_req_args	= 2,
		.file_data	= true,
		.args		= "<file> periodId"
	}, {
		.name		= "hfhl-ukpieps-get",
		.api_ep		= MTD_API_EP_PB_HFHL_UKPIEPS_GET,
		.nr_req_args	= 1,
		.args		= "periodId"
	},
	/* Historic non-FHL UK Property Income & Expenses Period Summary */
	{
		.name		= "hnfhl-ukpieps-list",
		.api_ep		= MTD_API_EP_PB_HNFHL_UKPIEPS_LIST,
		.nr_req_args	= 0,
		.args		= ""
	}, {
		.name		= "hnfhl-ukpieps-create",
		.api_ep		= MTD_API_EP_PB_HNFHL_UKPIEPS_CREATE,
		.nr_req_args	= 1,
		.file_data	= true,
		.args		= "<file>"
	}, {
		.name		= "hnfhl-ukpieps-get",
		.api_ep		= MTD_API_EP_PB_HNFHL_UKPIEPS_GET,
		.nr_req_args	= 2,
		.args		= "periodId"
	}, {
		.name		= "hnfhl-ukpieps-update",
		.api_ep		= MTD_API_EP_PB_HNFHL_UKPIEPS_AMEND,
		.nr_req_args	= 2,
		.file_data	= true,
		.args		= "<file> periodId"
	},
	/* Foreign Property Income & Expenses Period Summary */
	{
		.name		= "fpieps-create",
		.api_ep		= MTD_API_EP_PB_FPIEPS_CREATE,
		.nr_req_args	= 3,
		.file_data	= true,
		.args		= "<file> businessId taxYear"
	}, {
		.name		= "fpieps-get",
		.api_ep		= MTD_API_EP_PB_FPIEPS_GET,
		.nr_req_args	= 3,
		.args		= "businessId taxYear submissionId"
	}, {
		.name		= "fpieps-update",
		.api_ep		= MTD_API_EP_PB_FPIEPS_AMEND,
		.nr_req_args	= 4,
		.file_data	= true,
		.args		= "<file> businessId taxYear submissionId"
	},
	/* Foreign Property Cumulative Period Summary */
	{
		.name		= "fpcps-get",
		.api_ep		= MTD_API_EP_PB_FPCPS_GET,
		.nr_req_args	= 2,
		.args		= "businessId taxYear"
	}, {
		.name		= "fpcps-update",
		.api_ep		= MTD_API_EP_PB_FPCPS_AMEND,
		.nr_req_args	= 3,
		.file_data	= true,
		.args		= "<file> businessId taxYear"
	},
	/* Foreign Property Annual Submission */
	{
		.name		= "fpas-get",
		.api_ep		= MTD_API_EP_PB_FPAS_GET,
		.nr_req_args	= 2,
		.args		= "businessId taxYear"
	}, {
		.name		= "fpas-update",
		.api_ep		= MTD_API_EP_PB_FPAS_AMEND,
		.nr_req_args	= 3,
		.file_data	= true,
		.args		= "<file> businessId taxYear"
	},
	/* UK or Foreign Property Annual Submission Deletion */
	{
		.name		= "as-delete",
		.api_ep		= MTD_API_EP_PB_AS_DELETE,
		.nr_req_args	= 2,
		.args		= "businessId taxYear"
	},
	/* UK or Foreign Property Income and Expenses Period Summaries List */
	{
		.name		= "pieps-list",
		.api_ep		= MTD_API_EP_PB_PIEPS_LIST,
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
