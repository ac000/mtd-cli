/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-sa.c - Make Tax Digital - Self-Assessment
 *
 * Copyright (C) 2020		Andrew Clayton <andrew@digital-domain.net>
 */

#include <stdio.h>

#include <libmtdac/mtd-sa.h>

#include "mtd-cli.h"

#define MTD_CLI_CMD	MTD_CLI " sa "

#define ENDPOINTS \
"list-employments get-employment list-obligations list-periods create-period\n"\
"get-period update-period get-annual-summary update-annual-summary\n"\
"submit-end-of-period-statement get-end-of-period-statement"

static int get_end_of_period_statement(const char *seid, const char *start,
				       const char *end, char **buf)
{
	const char *s;
	const char *e;

	s = *start == '-' ? NULL : start;
	e = *end == '-' ? NULL : end;

	return mtd_sa_get_end_of_period_statement(seid, s, e, buf);
}

static const struct endpoint endpoints[] = {
	{
		.name = "list-employments",
		.api_func = {
			.func_0 = &mtd_sa_list_employments
		},
		.nargs = 0,
		.use = MTD_CLI_CMD "list-employments"
	},
	{
		.name = "get-employment",
		.api_func = {
			.func_1 = &mtd_sa_get_employment
		},
		.nargs = 1,
		.use = MTD_CLI_CMD "get-employment selfEmploymentId"
	},
	{
		.name = "list-obligations",
		.api_func = {
			.func_1 = &mtd_sa_list_obligations
		},
		.nargs = 1,
		.use = MTD_CLI_CMD "list-obligations selfEmploymentId"
	},
	{
		.name = "list-periods",
		.api_func = {
			.func_1 = &mtd_sa_list_periods
		},
		.nargs = 1,
		.use = MTD_CLI_CMD "list-periods selfEmploymentId"
	},
	{
		.name = "create-period",
		.api_func = {
			.func_2 = &mtd_sa_create_period
		},
		.nargs = 2,
		.use = MTD_CLI_CMD "create-period <file> selfEmploymentId"
	},
	{
		.name = "get-period",
		.api_func = {
			.func_2 = &mtd_sa_get_period
		},
		.nargs = 2,
		.use = MTD_CLI_CMD "get-period selfEmploymentId periodId"
	},
	{
		.name = "update-period",
		.api_func = {
			.func_3 = &mtd_sa_update_period
		},
		.nargs = 3,
		.use = MTD_CLI_CMD "update-period <file> selfEmploymentId periodId"
	},
	{
		.name = "get-annual-summary",
		.api_func = {
			.func_2 = &mtd_sa_get_annual_summary
		},
		.nargs = 2,
		.use = MTD_CLI_CMD "get-annual-summary selfEmploymentId taxYear"
	},
	{
		.name = "update-annual-summary",
		.api_func = {
			.func_3 = &mtd_sa_update_annual_summary
		},
		.nargs = 3,
		.use = MTD_CLI_CMD "update-annual-summary <file> selfEmploymentId taxYear"
	},
	{
		.name = "submit-end-of-period-statement",
		.api_func = {
			.func_4 = &mtd_sa_submit_end_of_period_statement
		},
		.nargs = 4,
		.use = MTD_CLI_CMD "submit-end-of-period-statement <file> selfEmploymentId start end"
	},
	{
		.name = "get-end-of-period-statement",
		.api_func = {
			.func_3 = &get_end_of_period_statement
		},
		.nargs = 3,
		.use = MTD_CLI_CMD "get-end-of-period-statement selfEmploymentId start|- end|-"
	},
	{ NULL, { NULL }, 0, NULL }
};

static int print_endpoints(void)
{
	printf("Available self-assessment endpoints :-\n\n%s\n", ENDPOINTS);

	return -1;
}

int do_sa(int argc, char *argv[], char **buf)
{
	int err;

	err = check_args(argc, argv[0], endpoints, print_endpoints);
	if (err)
		return err;

	return do_api_func(endpoints, argv, buf);
}
