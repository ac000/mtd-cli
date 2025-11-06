/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-icgi.c - Make Tax Digital - Individuals Capital Gains Income
 *
 * Copyright (C) 2025		Andrew Clayton <ac@sigsegv.uk>
 */

#include <stdbool.h>

#include <libmtdac/mtd.h>

#include "mtd-cli.h"

#define API	icgi

#define API_NAME "Individuals Capital Gains Income"
#define CMDS \
"Residential Property Disposals\n\n"\
"rpd-get non-ppd-amend non-ppd-delete ppd-amend ppd-delete\n\n"\
"Other Capital Gains and Disposals\n\n"\
"o-get o-amend o-delete"

static const struct endpoint endpoints[] = {
	/* Residential Property Disposals */
	{
		.name		= "rpd-get",
		.api_ep		= MTD_API_EP_ICGI_RPD_GET,
		.nr_req_args	= 1,
		.args		= "taxYear [source={user,hmrc-held,latest}]"
	}, {
		.name		= "non-ppd-amend",
		.api_ep		= MTD_API_EP_ICGI_RPD_N_PPD_AMEND,
		.nr_req_args	= 2,
		.file_data	= true,
		.args		= "<file> taxYear"
	}, {
		.name		= "non-ppd-delete",
		.api_ep		= MTD_API_EP_ICGI_RPD_N_PPD_DELETE,
		.nr_req_args	= 1,
		.args		= "taxYear"
	}, {
		.name		= "ppd-amend",
		.api_ep		= MTD_API_EP_ICGI_RPD_PPD_AMEND,
		.nr_req_args	= 2,
		.file_data	= true,
		.args		= "<file> taxYear"
	}, {
		.name		= "ppd-delete",
		.api_ep		= MTD_API_EP_ICGI_RPD_PPD_DELETE,
		.nr_req_args	= 1,
		.args		= "taxYear"
	},
	/* Other Capital Gains and Disposals */
	{
		.name		= "o-get",
		.api_ep		= MTD_API_EP_ICGI_O_GET,
		.nr_req_args	= 1,
		.args		= "taxYear"
	}, {
		.name		= "o-amend",
		.api_ep		= MTD_API_EP_ICGI_O_AMEND,
		.nr_req_args	= 2,
		.file_data	= true,
		.args		= "<file> taxYear"
	}, {
		.name		= "o-delete",
		.api_ep		= MTD_API_EP_ICGI_O_DELETE,
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
