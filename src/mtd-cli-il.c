/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-il.c - Make Tax Digital - Individual Loses
 *
 * Copyright (C) 2020		Andrew Clayton <andrew@digital-domain.net>
 */

#include <stdio.h>

#include <libmtdac/mtd-il.h>

#include "mtd-cli.h"

#define MTD_CLI_CMD	MTD_CLI " il "
#define API_NAME	"Individual Loses"

#define ENDPOINTS \
"Brought Forward Losses\n\n"\
"bf-list-loses bf-create-loss bf-get-loss bf-delete-loss bf-update-loss-amnt\n\n"\
"Loss Claims\n\n"\
"lc-list-loses lc-create-loss lc-get-loss lc-delete-loss lc-update-loss-type\n"\
"lc-update-loss-order"

static int print_endpoints(void)
{
	printf("Available " API_NAME " endpoints :-\n\n%s\n", ENDPOINTS);

	return -1;
}

static const struct endpoint endpoints[] = {
	/* Brought Forward Loses */
	{
		.name = "bf-list-loses",
		.api_func = {
			.func_1 = &mtd_il_bf_list_loses
		},
		.func = FUNC_1,
		.nr_req_args = 0,
		.use = MTD_CLI_CMD "bf-list-loses [[selfEmploymentId=][,[taxYear=YYYY-YY][,[typeOfLoss={self-employment,uk-property-fhl,uk-property-non-fhl}]]]]"
	},
	{
		.name = "bf-create-loss",
		.api_func = {
			.func_1 = &mtd_il_bf_create_loss
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = MTD_CLI_CMD "bf-create-loss <file>"
	},
	{
		.name = "bf-get-loss",
		.api_func = {
			.func_1 = &mtd_il_bf_get_loss
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = MTD_CLI_CMD "bf-get-loss lossId"
	},
	{
		.name = "bf-delete-loss",
		.api_func = {
			.func_1 = &mtd_il_bf_delete_loss
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = MTD_CLI_CMD "bf-delete-loss lossId"
	},
	{
		.name = "bf-update-loss-amnt",
		.api_func = {
			.func_2 = &mtd_il_bf_update_loss_amnt
		},
		.func = FUNC_2,
		.nr_req_args = 2,
		.use = MTD_CLI_CMD "bf-update-loss-amnt <file> lossaId"
	},
	/* Loass Claims */
	{
		.name = "lc-list-loses",
		.api_func = {
			.func_1 = &mtd_il_lc_list_loses
		},
		.func = FUNC_1,
		.nr_req_args = 0,
		.use = MTD_CLI_CMD "lc-list-loses [[selfEmploymentId=][,[taxYear=YYYY-YY][,[typeOfLoss={self-employment,uk-property-fhl,uk-property-non-fhl}][,[claimType=carry-sideways]]]]]"
	},
	{
		.name = "lc-create-loss",
		.api_func = {
			.func_1 = &mtd_il_lc_create_loss
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = MTD_CLI_CMD "lc-create-loss <file>"
	},
	{
		.name = "lc-get-loss",
		.api_func = {
			.func_1 = &mtd_il_lc_get_loss
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = MTD_CLI_CMD "lc-get-loss claimId"
	},
	{
		.name = "lc-delete-loss",
		.api_func = {
			.func_1 = &mtd_il_lc_delete_loss
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = MTD_CLI_CMD "lc-delete-loss claimId"
	},
	{
		.name = "lc-update-loss-type",
		.api_func = {
			.func_2 = &mtd_il_lc_update_loss_type
		},
		.func = FUNC_2,
		.nr_req_args = 2,
		.use = MTD_CLI_CMD "lc-update-loss-type <file> claimId"
	},
	{
		.name = "lc-update-loss-order",
		.api_func = {
			.func_1 = &mtd_il_lc_update_loss
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = MTD_CLI_CMD "lc-update-loss-order <file>"
	},
	{ NULL, { NULL }, 0, 0, NULL }
};

const struct _endpoint il_endpoint = {
	.endpoints = endpoints,
	.print_help = &print_endpoints
};
