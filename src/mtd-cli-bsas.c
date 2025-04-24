/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-bsas.c - Make Tax Digital - Business Source Adjustable Summary
 *
 * Copyright (C) 2020 - 2025	Andrew Clayton <ac@sigsegv.uk>
 */

#include <stdbool.h>

#include <libmtdac/mtd.h>

#include "mtd-cli.h"

#define API	bsas

#define API_NAME "Business Source Adjustable Summary"
#define CMDS \
"list trigger\n\n"\
"Self-Employment\n\n"\
"se-get-summary se-update-summary-adjustments\n\n"\
"UK Property Business\n\n"\
"pb-get-summary pb-update-summary-adjustments\n\n"\
"Foreign Property Business\n\n"\
"fp-get-summary fp-update-summary-adjustments"

static const struct endpoint endpoints[] = {
	{
		.name		= "list",
		.api_ep		= MTD_API_EP_BSAS_LIST,
		.nr_req_args	= 1,
		.args		= "taxYear [typeOfBusiness={self-employment,uk-property-non-fhl,uk-property-fhl,foreign-property-fhl-eea,foreign-property}]"
	}, {
		.name		= "trigger",
		.api_ep		= MTD_API_EP_BSAS_TRIGGER,
		.nr_req_args	= 1,
		.file_data	= true,
		.args		= "<file>"
	}, {
		.name		= "se-get-summary",
		.api_ep		= MTD_API_EP_BSAS_SE_GET,
		.nr_req_args	= 2,
		.args		= "calculationId taxYear"
	}, {
		.name		= "se-update-summary-adjustments",
		.api_ep		= MTD_API_EP_BSAS_SE_SUBMIT,
		.nr_req_args	= 3,
		.file_data	= true,
		.args		= "<file> calculationId taxYear"
	}, {
		.name		= "pb-get-summary",
		.api_ep		= MTD_API_EP_BSAS_PB_GET,
		.nr_req_args	= 2,
		.args		= "calculationId taxYear"
	}, {
		.name		= "pb-update-summary-adjustments",
		.api_ep		= MTD_API_EP_BSAS_PB_SUBMIT,
		.nr_req_args	= 3,
		.args		= "<file> calculationId taxYear"
	}, {
		.name		= "fp-get-summary",
		.api_ep		= MTD_API_EP_BSAS_FP_GET,
		.nr_req_args	= 2,
		.args		= "calculationId taxYear"
	}, {
		.name		= "fp-update-summary-adjustments",
		.api_ep		= MTD_API_EP_BSAS_FP_SUBMIT,
		.nr_req_args	= 3,
		.file_data	= true,
		.args		= "<file> calculationId taxYear"
	},

	{ }
};

const struct _endpoint ENDPOINT = {
	.endpoints = endpoints,
	.api_name = API_NAME,
	.cmds = CMDS
};
