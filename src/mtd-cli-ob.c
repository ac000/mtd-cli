/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-ob.c - Make Tax Digital - Obligations
 *
 * Copyright (C) 2021 - 2025	Andrew Clayton <ac@sigsegv.uk>
 */

#include <libmtdac/mtd.h>

#include "mtd-cli.h"

#define API	ob

#define API_NAME "Obligations"
#define CMDS \
"list-inc-and-exp-obligations list-final-decl-obligations"

static const struct endpoint endpoints[] = {
	{
		.name		= "list-inc-and-exp-obligations",
		.api_ep		= MTD_API_EP_OB_GET_IEO,
		.nr_req_args	= 0,
		.args		= "[[[typeOfBusiness={self-employment,uk-property,foreign-property}][,businessId=]][,[fromDate=YYYY-MM-DD,toDate=YYYY-MM-DD]][,[status={Oopen,fulfilled}]]]"
	}, {
		.name		= "list-final-decl-obligations",
		.api_ep		= MTD_API_EP_OB_GET_FDO,
		.nr_req_args	= 0,
		.args		= "[[taxYear=YYYY-MM],[status={open,fulfilled}]]"
	},

	{ }
};

const struct _endpoint ENDPOINT = {
	.endpoints = endpoints,
	.api_name = API_NAME,
	.cmds = CMDS
};
