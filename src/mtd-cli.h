/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli.h - Make Tax Digital CLI
 *
 * Copyright (C) 2020		Andrew Clayton <andrew@digital-domain.net>
 */

#ifndef _MTD_CLI_H_
#define _MTD_CLI_H_

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MTD_CLI			"mtd-cli"

#define IS_EP(endpoint)		(strcmp(argv[0], endpoint) == 0)

struct endpoint_help {
	const char *ep;
	const char *use;
	const int nargs;
};

extern int check_args(int argc, const char *endpoint,
		      const struct endpoint_help *eh, int (*print_help)(void));

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _MTD_CLI_H_ */
