/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-id.c - Make Tax Digital - Individuals Disclosures
 *
 * Copyright (C) 2021 - 2022	Andrew Clayton <andrew@digital-domain.net>
 */

#include <libmtdac/mtd-id.h>

#include "mtd-cli.h"

#define API	id

#define API_NAME "Individuals Disclosures"
#define CMDS \
"get set delete\n\n"\
"Marriage Allowance\n\n"\
"ma-create"

static const struct endpoint endpoints[] = {
	{
		.name = "get",
		.func_1 = mtd_id_get,
		.func = FUNC_1,
		.nr_req_args = 1,
		.args = "taxYear"
	}, {
		.name = "set",
		.func_2d = mtd_id_set,
		.func = FUNC_2d,
		.nr_req_args = 2,
		.args = "<file> teaxYear"
	}, {
		.name = "delete",
		.func_1 = mtd_id_delete,
		.func = FUNC_1,
		.nr_req_args = 1,
		.args = "taxYear"
	},
	/* Marriage Allowance */
	{
		.name = "ma-create",
		.func_1d = mtd_id_ma_create,
		.func = FUNC_1d,
		.nr_req_args = 1,
		.args = "<file>"
	},

	{ }
};

const struct _endpoint ENDPOINT = {
	.endpoints = endpoints,
	.api_name = API_NAME,
	.cmds = CMDS
};
