/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-bsas.c - Make Tax Digital - Business Source Adjustable Summary
 *
 * Copyright (C) 2020 - 2021	Andrew Clayton <andrew@digital-domain.net>
 */

#include <stddef.h>

#include <libmtdac/mtd-bsas.h>

#include "mtd-cli.h"

#define API	bsas

#define API_NAME "Business Source Adjustable Summary"
#define CMDS \
"list-summaries trigger-summary\n\n"\
"Self-Employment\n\n"\
"se-get-summary se-list-summary-adjustments se-update-summary-adjustments\n\n"\
"UK Property Business\n\n"\
"pb-get-summary pb-list-summary-adjustments pb-update-summary-adjustments\n\n"\
"Foreign Property Business\n\n"\
"fp-get-summary fp-list-summary-adjustments fp-update-summary-adjustments"

static const struct endpoint endpoints[] = {
	{
		.name = "list-summaries",
		.api_func = {
			.func_1 = mtd_bsas_list_summaries
		},
		.func = FUNC_1,
		.nr_req_args = 0,
		.use = "list-summaries [[selfEmploymentId=][,[typeOfBusiness={self-employment,uk-property-non-fhl,uk-property-fhl}][,[taxYear=YYYY-YY]]]]"
	}, {
		.name = "trigger-summary",
		.api_func = {
			.func_1d = mtd_bsas_trigger_summary
		},
		.func = FUNC_1d,
		.nr_req_args = 1,
		.use = "trigger-summary <file>"
	}, {
		.name = "se-get-summary",
		.api_func = {
			.func_2 = mtd_bsas_se_get_summary
		},
		.func = FUNC_2,
		.nr_req_args = 1,
		.use = "se-get-summary bsasId [adjustedStatus={true,false}]"
	}, {
		.name = "se-list-summary-adjustments",
		.api_func = {
			.func_1 = mtd_bsas_se_list_summary_adjustments
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = "se-list-summary-adjustments bsasId"
	}, {
		.name = "se-update-summary-adjustments",
		.api_func = {
			.func_2d = mtd_bsas_se_update_summary_adjustments
		},
		.func = FUNC_2d,
		.nr_req_args = 2,
		.use = "se-update-summary-adjustments <file> bsasId"
	}, {
		.name = "pb-get-summary",
		.api_func = {
			.func_2 = mtd_bsas_pb_get_summary
		},
		.func = FUNC_2,
		.nr_req_args = 1,
		.use = "pb-get-summary bsasId [adjustedStatus={true,false}]"
	}, {
		.name = "pb-list-summary-adjustments",
		.api_func = {
			.func_1 = mtd_bsas_pb_list_summary_adjustments
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = "pb-list-summary-adjustments bsasId"
	}, {
		.name = "pb-update-summary-adjustments",
		.api_func = {
			.func_2d = mtd_bsas_pb_update_summary_adjustments
		},
		.func = FUNC_2d,
		.nr_req_args = 2,
		.use = "pb-update-summary-adjustments <file> bsasId"
	}, {
		.name = "fp-get-summary",
		.api_func = {
			.func_2 = mtd_bsas_fp_get_summary
		},
		.func = FUNC_2,
		.nr_req_args = 1,
		.use = "fp-get-summary bsasId [adjustedStatus={true,false}]"
	}, {
		.name = "fp-list-summary-adjustments",
		.api_func = {
			.func_1 = mtd_bsas_fp_list_summary_adjustments
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = "fp-list-summary-adjustments bsasId"
	}, {
		.name = "fp-update-summary-adjustments",
		.api_func = {
			.func_2d = mtd_bsas_fp_update_summary_adjustments
		},
		.func = FUNC_2d,
		.nr_req_args = 2,
		.use = "fp-update-summary-adjustments <file> bsasId"
	},

	{ }
};

const struct _endpoint ENDPOINT = {
	.endpoints = endpoints,
	.api_name = API_NAME,
	.cmds = CMDS
};
