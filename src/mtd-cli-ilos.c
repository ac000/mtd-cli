/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-ilos.c - Make Tax Digital - Individual Loses
 *
 * Copyright (C) 2020 - 2025	Andrew Clayton <ac@sigsegv.uk>
 */

#include <stdbool.h>

#include <libmtdac/mtd.h>

#include "mtd-cli.h"

#define API	ilos

#define API_NAME "Individual Loses"
#define CMDS \
"Brought Forward Losses\n\n"\
"bf-list bf-create bf-get bf-delete bf-update-amnt\n\n"\
"Loss Claims\n\n"\
"lc-list lc-create lc-get lc-delete lc-update-type lc-update-order"

static const struct endpoint endpoints[] = {
	/* Brought Forward Loses */
	{
		.name		= "bf-list",
		.api_ep		= MTD_API_EP_ILOS_BF_LIST,
		.nr_req_args	= 1,
		.args		= "taxYearBroughtForwardFrom [[businessId=][,[typeOfLoss={self-employment,uk-property-fhl,uk-property,foreign-property-fhl-eea,foreign-property}]]]"
	}, {
		.name		= "bf-create",
		.api_ep		= MTD_API_EP_ILOS_BF_CREATE,
		.nr_req_args	= 2,
		.file_data	= true,
		.args		= "<file> taxYear"
	}, {
		.name		= "bf-get",
		.api_ep		= MTD_API_EP_ILOS_BF_GET,
		.nr_req_args	= 1,
		.args		= "lossId"
	}, {
		.name		= "bf-delete",
		.api_ep		= MTD_API_EP_ILOS_BF_DELETE,
		.nr_req_args	= 2,
		.args		= "lossId taxYear"
	}, {
		.name		= "bf-update-amnt",
		.api_ep		= MTD_API_EP_ILOS_BF_AMEND_AMNT,
		.nr_req_args	= 3,
		.file_data	= true,
		.args		= "<file> lossId taxYear"
	},
	/* Loss Claims */
	{
		.name		= "lc-list",
		.api_ep		= MTD_API_EP_ILOS_LC_LIST,
		.nr_req_args	= 1,
		.args		= "taxYearClaimedFor [[businessId=][,[typeOfLoss={self-employment,uk-property,foreign-property}][,[typeOfClaim={carry_forward,carry-sideways}]]]]"
	}, {
		.name		= "lc-create",
		.api_ep		= MTD_API_EP_ILOS_LC_CREATE,
		.nr_req_args	= 1,
		.file_data	= true,
		.args		= "<file>"
	}, {
		.name		= "lc-get",
		.api_ep		= MTD_API_EP_ILOS_LC_GET,
		.nr_req_args	= 1,
		.args		= "claimId"
	}, {
		.name		= "lc-delete",
		.api_ep		= MTD_API_EP_ILOS_LC_DELETE,
		.nr_req_args	= 2,
		.args		= "claimId taxYearClaimedFor"
	}, {
		.name		= "lc-update-type",
		.api_ep		= MTD_API_EP_ILOS_LC_AMEND_TYPE,
		.nr_req_args	= 3,
		.file_data	= true,
		.args		= "<file> claimId taxYearClaimedFor"
	},
	{
		.name		= "lc-update-order",
		.api_ep		= MTD_API_EP_ILOS_LC_AMEND_ORDER,
		.nr_req_args	= 2,
		.file_data	= true,
		.args		= "<file> taxYearClaimedFor"
	},

	{ }
};

const struct _endpoint ENDPOINT = {
	.endpoints = endpoints,
	.api_name = API_NAME,
	.cmds = CMDS
};
