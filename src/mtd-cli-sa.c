/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-sa.c - Make Tax Digital - Self-Assessment
 *
 * Copyright (C) 2020		Andrew Clayton <andrew@digital-domain.net>
 */

#include <stdio.h>

#include <libmtdac/mtd-sa.h>

#include "mtd-cli.h"
#include "utils.h"

#define MTD_CLI_CMD	MTD_CLI " sa "
#define API_NAME	"Self-Assessment"

#define ENDPOINTS \
"list-employments get-employment list-obligations list-periods create-period\n"\
"get-period update-period get-annual-summary update-annual-summary\n"\
"submit-end-of-period-statement get-end-of-period-statement"

static int print_endpoints(void)
{
	printf("Available " API_NAME " endpoints :-\n\n%s\n", ENDPOINTS);

	return -1;
}

static int get_end_of_period_statement(const char *seid,
				       const char *query_string, char **buf)
{
	char qs[64] = "\0";

	if (query_string)
		gen_query_string(query_string, qs, sizeof(qs));

	return mtd_sa_get_end_of_period_statement(seid, qs, buf);
}

static const struct endpoint endpoints[] = {
	{
		.name = "list-employments",
		.api_func = {
			.func_0 = &mtd_sa_list_employments
		},
		.func = FUNC_0,
		.nr_req_args = 0,
		.use = MTD_CLI_CMD "list-employments"
	},
	{
		.name = "get-employment",
		.api_func = {
			.func_1 = &mtd_sa_get_employment
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = MTD_CLI_CMD "get-employment selfEmploymentId"
	},
	{
		.name = "list-obligations",
		.api_func = {
			.func_1 = &mtd_sa_list_obligations
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = MTD_CLI_CMD "list-obligations selfEmploymentId"
	},
	{
		.name = "list-periods",
		.api_func = {
			.func_1 = &mtd_sa_list_periods
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = MTD_CLI_CMD "list-periods selfEmploymentId"
	},
	{
		.name = "create-period",
		.api_func = {
			.func_2 = &mtd_sa_create_period
		},
		.func = FUNC_2,
		.nr_req_args = 2,
		.use = MTD_CLI_CMD "create-period <file> selfEmploymentId"
	},
	{
		.name = "get-period",
		.api_func = {
			.func_2 = &mtd_sa_get_period
		},
		.func = FUNC_2,
		.nr_req_args = 2,
		.use = MTD_CLI_CMD "get-period selfEmploymentId periodId"
	},
	{
		.name = "update-period",
		.api_func = {
			.func_3 = &mtd_sa_update_period
		},
		.func = FUNC_3,
		.nr_req_args = 3,
		.use = MTD_CLI_CMD "update-period <file> selfEmploymentId periodId"
	},
	{
		.name = "get-annual-summary",
		.api_func = {
			.func_2 = &mtd_sa_get_annual_summary
		},
		.func = FUNC_2,
		.nr_req_args = 2,
		.use = MTD_CLI_CMD "get-annual-summary selfEmploymentId taxYear"
	},
	{
		.name = "update-annual-summary",
		.api_func = {
			.func_3 = &mtd_sa_update_annual_summary
		},
		.func = FUNC_3,
		.nr_req_args = 3,
		.use = MTD_CLI_CMD "update-annual-summary <file> selfEmploymentId taxYear"
	},
	{
		.name = "submit-end-of-period-statement",
		.api_func = {
			.func_4 = &mtd_sa_submit_end_of_period_statement
		},
		.func = FUNC_4,
		.nr_req_args = 4,
		.use = MTD_CLI_CMD "submit-end-of-period-statement <file> selfEmploymentId start end"
	},
	{
		.name = "get-end-of-period-statement",
		.api_func = {
			.func_2 = &get_end_of_period_statement
		},
		.func = FUNC_2,
		.nr_req_args = 1,
		.use = MTD_CLI_CMD "get-end-of-period-statement selfEmploymentId [[from=YYYY-MM-DD][,[to=YYYY-MM-DD]]]"
	},
	{ NULL, { NULL }, 0, 0, NULL }
};

const struct _endpoint sa_endpoint = {
	.endpoints = endpoints,
	.print_help = &print_endpoints
};
