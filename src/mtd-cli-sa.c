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
"Self-Employment\n\n"\
"se-list-employments se-get-employment se-list-obligations se-list-periods\n"\
"se-create-period se-get-period se-update-period se-get-annual-summary\n"\
"se-update-annual-summary se-submit-end-of-period-statement\n"\
"se-get-end-of-period-statement"

static int print_endpoints(void)
{
	printf("Available " API_NAME " endpoints :-\n\n%s\n", ENDPOINTS);

	return -1;
}

static int se_get_end_of_period_statement(const char *seid,
					  const char *query_string, char **buf)
{
	char qs[64] = "\0";

	if (query_string)
		gen_query_string(query_string, qs, sizeof(qs));

	return mtd_sa_se_get_end_of_period_statement(seid, qs, buf);
}

static const struct endpoint endpoints[] = {
	/* Self-Employment */
	{
		.name = "se-list-employments",
		.api_func = {
			.func_0 = &mtd_sa_se_list_employments
		},
		.func = FUNC_0,
		.nr_req_args = 0,
		.use = MTD_CLI_CMD "se-list-employments"
	},
	{
		.name = "se-get-employment",
		.api_func = {
			.func_1 = &mtd_sa_se_get_employment
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = MTD_CLI_CMD "se-get-employment selfEmploymentId"
	},
	{
		.name = "se-list-obligations",
		.api_func = {
			.func_1 = &mtd_sa_se_list_obligations
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = MTD_CLI_CMD "se-list-obligations selfEmploymentId"
	},
	{
		.name = "se-list-periods",
		.api_func = {
			.func_1 = &mtd_sa_se_list_periods
		},
		.func = FUNC_1,
		.nr_req_args = 1,
		.use = MTD_CLI_CMD "se-list-periods selfEmploymentId"
	},
	{
		.name = "se-create-period",
		.api_func = {
			.func_2 = &mtd_sa_se_create_period
		},
		.func = FUNC_2,
		.nr_req_args = 2,
		.use = MTD_CLI_CMD "se-create-period <file> selfEmploymentId"
	},
	{
		.name = "se-get-period",
		.api_func = {
			.func_2 = &mtd_sa_se_get_period
		},
		.func = FUNC_2,
		.nr_req_args = 2,
		.use = MTD_CLI_CMD "se-get-period selfEmploymentId periodId"
	},
	{
		.name = "se-update-period",
		.api_func = {
			.func_3 = &mtd_sa_se_update_period
		},
		.func = FUNC_3,
		.nr_req_args = 3,
		.use = MTD_CLI_CMD "se-update-period <file> selfEmploymentId periodId"
	},
	{
		.name = "se-get-annual-summary",
		.api_func = {
			.func_2 = &mtd_sa_se_get_annual_summary
		},
		.func = FUNC_2,
		.nr_req_args = 2,
		.use = MTD_CLI_CMD "se-get-annual-summary selfEmploymentId taxYear"
	},
	{
		.name = "se-update-annual-summary",
		.api_func = {
			.func_3 = &mtd_sa_se_update_annual_summary
		},
		.func = FUNC_3,
		.nr_req_args = 3,
		.use = MTD_CLI_CMD "se-update-annual-summary <file> selfEmploymentId taxYear"
	},
	{
		.name = "se-submit-end-of-period-statement",
		.api_func = {
			.func_4 = &mtd_sa_se_submit_end_of_period_statement
		},
		.func = FUNC_4,
		.nr_req_args = 4,
		.use = MTD_CLI_CMD "se-submit-end-of-period-statement <file> selfEmploymentId start end"
	},
	{
		.name = "se-get-end-of-period-statement",
		.api_func = {
			.func_2 = &se_get_end_of_period_statement
		},
		.func = FUNC_2,
		.nr_req_args = 1,
		.use = MTD_CLI_CMD "se-get-end-of-period-statement selfEmploymentId [[from=YYYY-MM-DD][,[to=YYYY-MM-DD]]]"
	},
	{ NULL, { NULL }, 0, 0, NULL }
};

const struct _endpoint sa_endpoint = {
	.endpoints = endpoints,
	.print_help = &print_endpoints
};
