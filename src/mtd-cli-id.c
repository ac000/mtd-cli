/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-id.c - Make Tax Digital - Individuals Disclosures
 *
 * Copyright (C) 2021		Andrew Clayton <andrew@digital-domain.net>
 */

#include <stddef.h>

#include <libmtdac/mtd-id.h>

#include "mtd-cli.h"

#define API	id

#define API_NAME "Individuals Disclosures"
#define CMDS "get set delete"

static const struct endpoint endpoints[] = {
	{
		.name = "get",
		.api_func = {
			.func_1 = mtd_id_get
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.args = "taxYear"
	}, {
		.name = "set",
		.api_func = {
			.func_2d = mtd_id_set
		},
		.func = FUNC_2d,
		.nr_req_args = 2,
		.args = "<file> teaxYear"
	}, {
		.name = "delete",
		.api_func = {
			.func_1 = mtd_id_delete
		},
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
