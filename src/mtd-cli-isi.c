/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-isi.c - Make Tax Digital - Individuals Savings Income
 *
 * Copyright (C) 2025		Andrew Clayton <ac@sigsegv.uk>
 */

#include <stdbool.h>

#include <libmtdac/mtd.h>

#include "mtd-cli.h"

#define API	isi

#define API_NAME "Individuals Savings Income"
#define CMDS \
"UK Savings Account\n\n"\
"ua-list ua-add ua-get-annual-summary ua-update-annual-summary\n\n"\
"Savings Income\n\n"\
"si-get si-update si-delete"

static const struct endpoint endpoints[] = {
	/* UK Savings Account */
	{
		.name		= "ua-list",
		.api_ep		= MTD_API_EP_ISI_SI_UK_LIST,
		.nr_req_args	= 0,
		.args		= "[savingsAccountId=^[A-Za-z0-9]{15}$]"
	}, {
		.name		= "ua-add",
		.api_ep		= MTD_API_EP_ISI_SI_UK_ADD,
		.nr_req_args	= 1,
		.file_data	= true,
		.args		= "<file>"
	}, {
		.name		= "ua-get-annual-summary",
		.api_ep		= MTD_API_EP_ISI_SI_UK_GET_AS,
		.nr_req_args	= 2,
		.args		= "taxYear savingsAccountId"
	}, {
		.name		= "ua-update-annual-summary",
		.api_ep		= MTD_API_EP_ISI_SI_UK_UPDATE_AS,
		.nr_req_args	= 3,
		.file_data	= true,
		.args		= "<file> taxYear savingsAccountId"
	},

	/* Savings Income */
	{
		.name		= "si-get",
		.api_ep		= MTD_API_EP_ISI_SI_O_GET,
		.nr_req_args	= 1,
		.args		= "taxYear"
	}, {
		.name		= "si-update",
		.api_ep		= MTD_API_EP_ISI_SI_O_UPDATE,
		.nr_req_args	= 2,
		.file_data	= true,
		.args		= "<file> taxYear"
	}, {
		.name		= "si-delete",
		.api_ep		= MTD_API_EP_ISI_SI_O_DELETE,
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
