/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-bd.c - Make Tax Digital - Business Details
 *
 * Copyright (C) 2021		Andrew Clayton <andrew@digital-domain.net>
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
		.api_func = {
			.func_0 = mtd_bd_list
		},
		.func = FUNC_0,
		.nr_req_args = 0,
		.use = "list"
	},
	{
		.name = "get",
		.api_func = {
			.func_1 = mtd_bd_get
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = "get businessId"
	},

	{ }
};

const struct _endpoint ENDPOINT = {
	.endpoints = endpoints,
	.api_name = API_NAME,
	.cmds = CMDS
};
