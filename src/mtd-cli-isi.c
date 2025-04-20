/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-isi.c - Make Tax Digital - Individual Savings Income
 *
 * Copyright (C) 2025		Andrew Clayton <ac@sigsegv.uk>
 */

#include <stdbool.h>

#include <libmtdac/mtd-isi.h>

#include "mtd-cli.h"

#define API	isi

#define API_NAME "Individual Savings Income"
#define CMDS \
"UK Savings Account\n\n"\
"ua-list ua-add ua-get-annual-summary ua-update-annual-summary\n\n"\
"Savings Income\n\n"\
"si-get si-update si-delete"

static const struct endpoint endpoints[] = {
	/* UK Savings Account */
	{
		.name = "ua-list",
		.func_1 = mtd_isi_si_ua_list,
		.func = FUNC_1,
		.nr_req_args = 0,
		.args = "[savingsAccountId=^[A-Za-z0-9]{15}$]"
	}, {
		.name = "ua-add",
		.func_1d = mtd_isi_si_ua_add,
		.func = FUNC_1d,
		.nr_req_args = 1,
		.args = "<file>"
	}, {
		.name = "ua-get-annual-summary",
		.func_2 = mtd_isi_si_ua_get_annual_summary,
		.func = FUNC_2,
		.nr_req_args = 2,
		.args = "taxYear savingsAccountId"
	}, {
		.name = "ua-update-annual-summary",
		.func_3d = mtd_isi_si_ua_update_annual_summary,
		.func = FUNC_3d,
		.nr_req_args = 3,
		.args = "<file> taxYear savingsAccountId"
	},
	/* Savings Income */
	{
		.name = "si-get",
		.func_1 = mtd_isi_si_o_get,
		.func = FUNC_1,
		.nr_req_args = 1,
		.args = "taxYear"
	}, {
		.name = "si-update",
		.func_2d = mtd_isi_si_o_update,
		.func = FUNC_2d,
		.nr_req_args = 2,
		.args = "<file> taxYear"
	}, {
		.name = "si-delete",
		.func_1 = mtd_isi_si_o_delete,
		.func = FUNC_1,
		.nr_req_args = 1,
		.args = "taxYear"
	},

	{ }
};

const struct _endpoint ENDPOINT = {
	.endpoints = endpoints,
	.api_name = API_NAME,
	.cmds = CMDS
};
