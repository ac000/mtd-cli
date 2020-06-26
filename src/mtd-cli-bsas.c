/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-bsas.c - Make Tax Digital - Business Source Adjustable Summary
 *
 * Copyright (C) 2020		Andrew Clayton <andrew@digital-domain.net>
 */

#include <stddef.h>

#include <libmtdac/mtd-bsas.h>

#include "mtd-cli.h"

#define MTD_CLI_CMD	MTD_CLI " bsas "

#define API_NAME "Business Source Adjustable Summary"
#define CMDS \
"bsas-list-summaries bsas-trigger-summary\n\n"\
"Self-Employment\n\n"\
"bsas-se-get-summary bsas-se-list-summary-adjustments\n"\
"bsas-se-update-summary-adjustments\n\n"\
"UK Property Business\n\n"\
"bsas-pb-get-summary bsas-pb-list-summary-adjustments\n"\
"bsas-pb-update-summary-adjustments"

static const struct endpoint endpoints[] = {
	{
		.name = "bsas-list-summaries",
		.api_func = {
			.func_1 = mtd_bsas_list_summaries
		},
		.func = FUNC_1,
		.nr_req_args = 0,
		.use = MTD_CLI_CMD "bsas-list-summaries [[selfEmploymentId=][,[typeOfBusiness={self-employment,uk-property-non-fhl,uk-property-fhl}][,[taxYear=YYYY-YY]]]]"
	},
	{
		.name = "bsas-trigger-summary",
		.api_func = {
			.func_1d = mtd_bsas_trigger_summary
		},
		.func = FUNC_1d,
		.nr_req_args = 1,
		.use = MTD_CLI_CMD "bsas-trigger-summary <file>"
	},
	{
		.name = "bsas-se-get-summary",
		.api_func = {
			.func_2 = mtd_bsas_se_get_summary
		},
		.func = FUNC_2,
		.nr_req_args = 1,
		.use = MTD_CLI_CMD "bsas-se-get-summary bsasId [adjustedStatus={true,false}]"
	},
	{
		.name = "bsas-se-list-summary-adjustments",
		.api_func = {
			.func_1 = mtd_bsas_se_list_summary_adjustments
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = MTD_CLI_CMD "bsas-se-list-summary-adjustments bsasId"
	},
	{
		.name = "bsas-se-update-summary-adjustments",
		.api_func = {
			.func_2d = mtd_bsas_se_update_summary_adjustments
		},
		.func = FUNC_2d,
		.nr_req_args = 2,
		.use = MTD_CLI_CMD "bsas-se-update-summary-adjustments <file> bsasId"
	},
	{
		.name = "bsas-pb-get-summary",
		.api_func = {
			.func_2 = mtd_bsas_pb_get_summary
		},
		.func = FUNC_2,
		.nr_req_args = 1,
		.use = MTD_CLI_CMD "bsas-pb-get-summary bsasId [adjustedStatus={true,false}]"
	},
	{
		.name = "bsas-pb-list-summary-adjustments",
		.api_func = {
			.func_1 = mtd_bsas_pb_list_summary_adjustments
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = MTD_CLI_CMD "bsas-pb-list-summary-adjustments bsasId"
	},
	{
		.name = "bsas-pb-update-summary-adjustments",
		.api_func = {
			.func_2d = mtd_bsas_pb_update_summary_adjustments
		},
		.func = FUNC_2d,
		.nr_req_args = 2,
		.use = MTD_CLI_CMD "bsas-pb-update-summary-adjustments <file> bsasId"
	},
	{ NULL, { NULL }, 0, 0, NULL}
};

const struct _endpoint bsas_endpoint = {
	.endpoints = endpoints,
	.api_name = API_NAME,
	.cmds = CMDS
};
