/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-bd.c - Make Tax Digital - Business Details
 *
 * Copyright (C) 2021 - 2022	Andrew Clayton <andrew@digital-domain.net>
 */

#include <stddef.h>

#include <libmtdac/mtd-bd.h>

#include "mtd-cli.h"

#define API	bd

#define API_NAME "Business Details"
#define CMDS "list get"

static const struct endpoint endpoints[] = {
	{
		.name = "list",
		.func_0 = mtd_bd_list,
		.func = FUNC_0,
		.nr_req_args = 0,
		.args = ""
	}, {
		.name = "get",
		.func_1 = mtd_bd_get,
		.func = FUNC_1,
		.nr_req_args = 1,
		.args = "businessId"
	},

	{ }
};

const struct _endpoint ENDPOINT = {
	.endpoints = endpoints,
	.api_name = API_NAME,
	.cmds = CMDS
};
