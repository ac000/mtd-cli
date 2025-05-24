/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-test-sa.c - Make Tax Digital - Self Assessment Test Support
 *
 * Copyright (C) 2025		Andrew Clayton <ac@sigsegv.uk>
 */

#include <libmtdac/mtd.h>

#include "mtd-cli.h"

#define API	test_sa

#define API_NAME "Self Assessment Test Support"
#define CMDS \
"delete\n\n"\
"Checkpoint for Vendor Data\n\n"\
"chkpt-list chkpt-create chkpt-delete chkpt-restore\n\n"\
"Business Income Source\n\n"\
"bis-create bis-delete\n\n"\
"ITSA Status\n\n"\
"is-amend"

static const struct endpoint endpoints[] = {
	{
		.name		= "delete",
		.api_ep		= MTD_API_EP_TEST_SATS_DELETE,
		.nr_req_args	= 0,
		.args		= "[nino=]"
	},
	/* Self Assessment Test Support Checkpoint for Vendor Data */
	{
		.name		= "chkpt-list",
		.api_ep		= MTD_API_EP_TEST_SATS_CHKPT_LIST,
		.nr_req_args	= 0,
		.args		= "[nino=]"
	}, {
		.name		= "chkpt-create",
		.api_ep		= MTD_API_EP_TEST_SATS_CHKPT_CREATE,
		.nr_req_args	= 0,
		.args		= "[nino=]"
	}, {
		.name		= "chkpt-delete",
		.api_ep		= MTD_API_EP_TEST_SATS_CHKPT_DELETE,
		.nr_req_args	= 1,
		.args		= "checkpointId"
	}, {
		.name		= "chkpt-restore",
		.api_ep		= MTD_API_EP_TEST_SATS_CHKPT_RESTORE,
		.nr_req_args	= 1,
		.args		= "checkpointId"
	},
	/* Self Assessment Test Support Business Income Source */
	{
		.name		= "bis-create",
		.api_ep		= MTD_API_EP_TEST_SATS_BIS_CREATE,
		.nr_req_args	= 0,
		.args		= ""
	}, {
		.name		= "bis-delete",
		.api_ep		= MTD_API_EP_TEST_SATS_BIS_DELETE,
		.nr_req_args	= 1,
		.args		= "businessId"
	},
	/* Self Assessment Test Support ITSA Status */
	{
		.name		= "is-amend",
		.api_ep		= MTD_API_EP_TEST_SATS_IS_AMEND,
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
