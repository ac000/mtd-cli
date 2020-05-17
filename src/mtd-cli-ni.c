/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli-ni.c - make Tax Digital - National Insurance
 *
 * Copyright (C) 2020		Andrew Clayton <andrew@digital-domain.net>
 */

#include <stdio.h>

#include <libmtdac/mtd-ni.h>

#include "mtd-cli.h"

#define MTD_CLI_CMD	MTD_CLI " ni "

#define ENDPOINTS	"get-annual-summary"

static const struct endpoint_help ep_help[] = {
	{ "get-annual-summary", MTD_CLI_CMD "get-annual-summary utr taxYear",
	 2 },
	{ NULL, NULL, 0 }
};

static int print_endpoints(void)
{
	printf("Available national insurance endpoints :-\n\n%s\n", ENDPOINTS);

	return -1;
}

int do_ni(int argc, char *argv[], char **buf)
{
	int err;

	err = check_args(argc, argv[0], ep_help, print_endpoints);
	if (err)
		return err;

	if (IS_EP("get-annual-summary"))
		return mtd_ni_get_annual_summary(argv[1], argv[2], buf);

	return -1;
}
