/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-il.c - Make Tax Digital - Individual Loses
 *
 * Copyright (C) 2020 - 2022	Andrew Clayton <andrew@digital-domain.net>
 */

#include <libmtdac/mtd-il.h>

#include "mtd-cli.h"

#define API	il

#define API_NAME "Individual Loses"
#define CMDS \
"Brought Forward Losses\n\n"\
"bf-list-loses bf-create-loss bf-get-loss bf-delete-loss bf-update-loss-amnt\n\n"\
"Loss Claims\n\n"\
"lc-list-loses lc-create-loss lc-get-loss lc-delete-loss lc-update-loss-type\n"\
"lc-update-loss-order"

static const struct endpoint endpoints[] = {
	/* Brought Forward Loses */
	{
		.name = "bf-list-loses",
		.func_1 = mtd_il_bf_list_loses,
		.func = FUNC_1,
		.nr_req_args = 0,
		.args = "[[businessId=][,[taxYearBroughtForwardFrom=YYYY-YY][,[typeOfLoss={self-employment,uk-property-fhl,uk-property-non-fhl}]]]]"
	}, {
		.name = "bf-create-loss",
		.func_1d = mtd_il_bf_create_loss,
		.func = FUNC_1d,
		.nr_req_args = 1,
		.args = "<file>"
	}, {
		.name = "bf-get-loss",
		.func_1 = mtd_il_bf_get_loss,
		.func = FUNC_1,
		.nr_req_args = 1,
		.args = "lossId"
	}, {
		.name = "bf-delete-loss",
		.func_1 = mtd_il_bf_delete_loss,
		.func = FUNC_1,
		.nr_req_args = 1,
		.args = "lossId"
	}, {
		.name = "bf-update-loss-amnt",
		.func_2d = mtd_il_bf_update_loss_amnt,
		.func = FUNC_2d,
		.nr_req_args = 2,
		.args = "<file> lossId"
	},
	/* Loss Claims */
	{
		.name = "lc-list-loses",
		.func_1 = mtd_il_lc_list_loses,
		.func = FUNC_1,
		.nr_req_args = 0,
		.args = "[[businessId=][,[taxYearClaimedFor=YYYY-YY][,[typeOfLoss={self-employment,uk-property-non-fhl,foreign-property}][,[typeOfClaim=carry-sideways]]]]]"
	}, {
		.name = "lc-create-loss",
		.func_1d = mtd_il_lc_create_loss,
		.func = FUNC_1d,
		.nr_req_args = 1,
		.args = "<file>"
	}, {
		.name = "lc-get-loss",
		.func_1 = mtd_il_lc_get_loss,
		.func = FUNC_1,
		.nr_req_args = 1,
		.args = "claimId"
	}, {
		.name = "lc-delete-loss",
		.func_1 = mtd_il_lc_delete_loss,
		.func = FUNC_1,
		.nr_req_args = 1,
		.args = "claimId"
	}, {
		.name = "lc-update-loss-type",
		.func_2d = mtd_il_lc_update_loss_type,
		.func = FUNC_2d,
		.nr_req_args = 2,
		.args = "<file> claimId"
	},
	{
		.name = "lc-update-loss-order",
		.func_2d = mtd_il_lc_update_loss_order,
		.func = FUNC_2d,
		.nr_req_args = 2,
		.args = "<file> taxYearClaimedFor"
	},

	{ }
};

const struct _endpoint ENDPOINT = {
	.endpoints = endpoints,
	.api_name = API_NAME,
	.cmds = CMDS
};
