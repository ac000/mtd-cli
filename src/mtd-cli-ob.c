/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-ob.c - Make Tax Digital - Obligations
 *
 * Copyright (C) 2021		Andrew Clayton <andrew@digital-domain.net>
 */

#include <stddef.h>

#include <libmtdac/mtd-ob.h>

#include "mtd-cli.h"

#define API	ob

#define API_NAME "Obligations"
#define CMDS \
"list-inc-and-exp-obligations list-crystallisation-obligations\n"\
"list-end-of-period-obligations"

static const struct endpoint endpoints[] = {
	{
		.name = "list-inc-and-exp-obligations",
		.func_1 = mtd_ob_list_inc_and_expend_obligations,
		.func = FUNC_1,
		.nr_req_args = 0,
		.args = "[[[typeOfBusiness={self-employment,uk-property,foreign-property}][,businessId=]][,[fromDate=YYYY-MM-DD,toDate=YYYY-MM-DD]][,[status={Open,Fulfilled}]]]"
	}, {
		.name = "list-crystallisation-obligations",
		.func_1 = mtd_ob_list_crystallisation_obligations,
		.func = FUNC_1,
		.nr_req_args = 0,
		.args = "[taxYear=YYYY-MM]"
	}, {
		.name = "list-end-of-period-obligations",
		.func_1 = mtd_ob_list_end_of_period_obligations,
		.func = FUNC_1,
		.nr_req_args = 0,
		.args = "[[[typeOfBusiness={self-employment,uk-property,foreign-property}][,businessId=]][,[fromDate=YYYY-MM-DD,toDate=YYYY-MM-DD]][,[status={Open,Fulfilled}]]]"
	},

	{ }
};

const struct _endpoint ENDPOINT = {
	.endpoints = endpoints,
	.api_name = API_NAME,
	.cmds = CMDS
};
