/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-tesst-cu.c - Make Tax Digital - Create Test User
 *
 * Copyright (C) 2020 - 2021	Andrew Clayton <andrew@digital-domain.net>
 */

#include <stddef.h>

#include <libmtdac/mtd-test-cu.h>

#include "mtd-cli.h"

#define API	test_cu
#define API_CMD	"test-cu"

#define API_NAME "Create Test User"
#define CMDS "create-individual create-organisation create-agent list-services"

static const struct endpoint endpoints[] = {
	{
		.name = "create-individual",
		.api_func = {
			.func_1d = mtd_test_cu_create_individual
		},
		.func = FUNC_1d,
		.nr_req_args = 1,
		.use = "create-individual <file>"
	},
	{
		.name = "create-organisation",
		.api_func = {
			.func_1d = mtd_test_cu_create_organisation
		},
		.func = FUNC_1d,
		.nr_req_args = 1,
		.use = "create-organisation <file>"
	},
	{
		.name = "create-agent",
		.api_func = {
			.func_1d = mtd_test_cu_create_agent
		},
		.func = FUNC_1d,
		.nr_req_args = 1,
		.use = "create-agent <file>"
	},
	{
		.name = "list-services",
		.api_func = {
			.func_0 = mtd_test_cu_list_services
		},
		.func = FUNC_0,
		.nr_req_args = 0,
		.use = "list-services"
	},

	{ }
};

const struct _endpoint ENDPOINT = {
	.endpoints = endpoints,
	.api_name = API_NAME,
	.cmds = CMDS
};
