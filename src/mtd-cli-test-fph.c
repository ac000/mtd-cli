/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-test-fph.c - Make Tax Digital - Test Fraud Prevention Headers
 *
 * Copyright (C) 2020 - 2025	Andrew Clayton <ac@sigsegv.uk>
 */

#include <libmtdac/mtd.h>

#include "mtd-cli.h"

#define API	test_fph

#define API_NAME "Test Fraud Prevention Headers"
#define CMDS "validate feedback"

static const struct endpoint endpoints[] = {
	{
		.name		= "validate",
		.api_ep		= MTD_API_EP_TEST_FPH_VALIDATE,
		.nr_req_args	= 0,
		.args		= ""
	}, {
		.name		= "feedback",
		.api_ep		= MTD_API_EP_TEST_FPH_FEEDBACK,
		.nr_req_args	= 1,
		.args		= "api [connectionMethod=]"
	},

	{ }
};

const struct _endpoint ENDPOINT = {
	.endpoints = endpoints,
	.api_name = API_NAME,
	.cmds = CMDS
};
