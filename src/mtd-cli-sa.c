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

static const struct endpoint_help ep_help[] = {
	{ "list-employments", MTD_CLI_CMD "list-employments", 0 },
	{ "get-employment", MTD_CLI_CMD "get-employment selfEmploymentId", 1 },
	{ "list-obligations", MTD_CLI_CMD "list-obligations selfEmploymentId",
	  1 },
	{ "list-periods", MTD_CLI_CMD "list-periods selfEmploymentId", 1 },
	{ "create-period", MTD_CLI_CMD "create-period <file> selfEmploymentId",
	  2 },
	{ "get-period", MTD_CLI_CMD "get-period selfEmploymentId periodId",
	 2 },
	{ "update-period",
	  MTD_CLI_CMD "update-period <file> selfEmploymentId periodId", 3 },
	{ "get-annual-summary",
	  MTD_CLI_CMD "get-annual-summary selfEmploymentId taxYear", 2 },
	{ "update-annual-summary",
	  MTD_CLI_CMD "update-annual-summary <file> selfEmploymentId taxYear",
	  3 },
	{ "submit-end-of-period-statement",
	  MTD_CLI_CMD
	   "submit-end-of-period-statement <file> selfEmploymentId start end",
	  3 },
	{ "get-end-of-period-statement",
	  MTD_CLI_CMD
	   "get-end-of-period-statement selfEmploymentId start|- end|-",
	  3 },
	{ NULL, NULL, 0 }
};

static int print_endpoints(void)
{
	printf("Available self-assessment endpoints :-\n\n%s\n", ENDPOINTS);

	return -1;
}

static int get_end_of_period_statement(char *argv[], char **buf)
{
	const char *start;
	const char *end;

	start = *argv[2] == '-' ? NULL : argv[2];
	end = *argv[3] == '-' ? NULL : argv[3];

	return mtd_sa_get_end_of_period_statement(argv[1], start, end, buf);
}

int do_sa(int argc, char *argv[], char **buf)
{
	int err;

	err = check_args(argc, argv[0], ep_help, print_endpoints);
	if (err)
		return err;

	if (IS_EP("list-employments"))
		return mtd_sa_list_employments(buf);
	else if (IS_EP("get-employment"))
		return mtd_sa_get_employment(argv[1], buf);
	else if (IS_EP("list-obligations"))
		return mtd_sa_list_obligations(argv[1], buf);
	else if (IS_EP("list-periods"))
		return mtd_sa_list_periods(argv[1], buf);
	else if (IS_EP("create-period"))
		return mtd_sa_create_period(argv[1], argv[2], buf);
	else if (IS_EP("get-period"))
		return mtd_sa_get_period(argv[1], argv[2], buf);
	else if (IS_EP("update-period"))
		return mtd_sa_update_period(argv[1], argv[2], argv[3], buf);
	else if (IS_EP("get-annual-summary"))
		return mtd_sa_get_annual_summary(argv[1], argv[2], buf);
	else if (IS_EP("update-annual-summary"))
		return mtd_sa_update_annual_summary(argv[1], argv[2], argv[3],
						    buf);
	else if (IS_EP("submit-end-of-period-statement"))
		return mtd_sa_submit_end_of_period_statement(argv[1], argv[2],
							     argv[3], argv[4],
							     buf);
	else if (IS_EP("get-end-of-period-statement"))
		return get_end_of_period_statement(argv, buf);

	return -1;
}
