/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-tesst-cu.c - Make Tax Digital - Create Test User
 *
 * Copyright (C) 2020 - 2025	Andrew Clayton <ac@sigsegv.uk>
 */

#include <stdbool.h>

#include <libmtdac/mtd.h>

#include "mtd-cli.h"

#define API	test_cu

#define API_NAME "Create Test User"
#define CMDS "create-individual create-organisation create-agent list-services"

static const struct endpoint endpoints[] = {
	{
		.name		= "create-individual",
		.api_ep		= MTD_API_EP_TEST_CU_CREATE_INDIVIDUAL,
		.nr_req_args	= 1,
		.file_data	= true,
		.args		= "<file>"
	}, {
		.name		= "create-organisation",
		.api_ep		= MTD_API_EP_TEST_CU_CREATE_ORGANISATION,
		.nr_req_args	= 1,
		.file_data	= true,
		.args		= "<file>"
	}, {
		.name		= "create-agent",
		.api_ep		= MTD_API_EP_TEST_CU_CREATE_AGENT,
		.nr_req_args	= 1,
		.file_data	= true,
		.args		= "<file>"
	}, {
		.name		= "list-services",
		.api_ep		= MTD_API_EP_TEST_CU_LIST_SERVICES,
		.nr_req_args	= 0,
		.args		= ""
	},

	{ }
};

const struct _endpoint ENDPOINT = {
	.endpoints = endpoints,
	.api_name = API_NAME,
	.cmds = CMDS
};
