/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-idi.c - Make Tax Digital - Individuals Dividends Income
 *
 * Copyright (C) 2025		Andrew Clayton <ac@sigsegv.uk>
 */

#include <stdbool.h>

#include <libmtdac/mtd.h>

#include "mtd-cli.h"

#define API	idi

#define API_NAME "Individuals Dividends Income"
#define CMDS \
"Dividends Income\n\n"\
"di-get di-amend di-delete\n\n"\
"UK Dividends Income\n\n"\
"ukdi-get ukdi-amend ukdi-delete\n\n"\
"Additional Directorship and Dividend Information\n\n"\
"addi-get addi-amend addi-delete"

static const struct endpoint endpoints[] = {
	/* Dividends Income */
	{
		.name		= "di-get",
		.api_ep		= MTD_API_EP_IDI_DI_GET,
		.nr_req_args	= 1,
		.args		= "taxYear"
	}, {
		.name		= "di-amend",
		.api_ep		= MTD_API_EP_IDI_DI_AMEND,
		.nr_req_args	= 2,
		.file_data	= true,
		.args		= "<file> taxYear"
	}, {
		.name		= "di-delete",
		.api_ep		= MTD_API_EP_IDI_DI_DELETE,
		.nr_req_args	= 1,
		.args		= "taxYear"
	},
	/* UK Dividends Income */
	{
		.name		= "ukdi-get",
		.api_ep		= MTD_API_EP_IDI_UKDI_GET,
		.nr_req_args	= 1,
		.args		= "taxYear"
	}, {
		.name		= "ukdi-amend",
		.api_ep		= MTD_API_EP_IDI_UKDI_AMEND,
		.nr_req_args	= 2,
		.file_data	= true,
		.args		= "<file> taxYear"
	}, {
		.name		= "ukdi-delete",
		.api_ep		= MTD_API_EP_IDI_UKDI_DELETE,
		.nr_req_args	= 1,
		.args		= "taxYear"
	},
	/* Additional Directorship and Dividend Information */
	{
		.name		= "addi-get",
		.api_ep		= MTD_API_EP_IDI_ADDI_GET,
		.nr_req_args	= 2,
		.args		= "taxYear employmentId"
	}, {
		.name		= "addi-amend",
		.api_ep		= MTD_API_EP_IDI_ADDI_AMEND,
		.nr_req_args	= 3,
		.file_data	= true,
		.args		= "<file> taxYear employmentId"
	}, {
		.name		= "addi-delete",
		.api_ep		= MTD_API_EP_IDI_ADDI_DELETE,
		.nr_req_args	= 2,
		.args		= "taxYear employmentId"
	},

	{ }
};

const struct _endpoint ENDPOINT = {
	.endpoints = endpoints,
	.api_name = API_NAME,
	.cmds = CMDS
};
