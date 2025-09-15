/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-ic.c - Make Tax Digital - Individuals Charges
 *
 * Copyright (C) 2025          Andrew Clayton <ac@sigsegv.uk>
 */

#include <stdbool.h>

#include <libmtdac/mtd.h>

#include "mtd-cli.h"

#define API    ic

#define API_NAME "Individuals Charges"
#define CMDS \
"Pension Charges\n\n"\
"pc-get pc-amend pc-delete\n\n"\
"High Income Child Benefit Charge Submission\n\n"\
"hicbcs-get hicbcs-amend hicbcs-delete"

static const struct endpoint endpoints[] = {
	/* Pension Charges */
	{
		.name           = "pc-get",
		.api_ep         = MTD_API_EP_IC_PC_GET,
		.nr_req_args    = 1,
		.args           = "taxYear"
	}, {
		.name           = "pc-amend",
		.api_ep         = MTD_API_EP_IC_PC_AMEND,
		.nr_req_args    = 2,
		.file_data      = true,
		.args           = "<file> taxYear"
	}, {
		.name           = "pc-delete",
		.api_ep         = MTD_API_EP_IC_PC_DELETE,
		.nr_req_args    = 1,
		.args           = "taxYear"
	},
	/* High Income Child Benefit Charge Submission */
	{
		.name           = "hicbcs-get",
		.api_ep         = MTD_API_EP_IC_HICBCS_GET,
		.nr_req_args    = 1,
		.args           = "taxYear"
	}, {
		.name           = "hicbcs-amend",
		.api_ep         = MTD_API_EP_IC_HICBCS_AMEND,
		.nr_req_args    = 2,
		.file_data      = true,
		.args           = "<file> taxYear"
	}, {
		.name           = "hicbcs-delete",
		.api_ep         = MTD_API_EP_IC_HICBCS_DELETE,
		.nr_req_args    = 1,
		.args           = "taxYear"
	},

	{ }
};

const struct _endpoint ENDPOINT = {
	.endpoints = endpoints,
	.api_name = API_NAME,
	.cmds = CMDS
};
