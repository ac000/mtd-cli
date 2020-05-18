/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli.h - Make Tax Digital CLI
 *
 * Copyright (C) 2020		Andrew Clayton <andrew@digital-domain.net>
 */

#ifndef _MTD_CLI_H_
#define _MTD_CLI_H_

#ifdef __cplusplus
extern "C" {
#endif

#define MTD_CLI			"mtd-cli"

struct _endpoint {
	const struct endpoint *endpoints;
	int (*print_help)(void);
};

struct endpoint {
	const char *name;
	union {
		int (*func_0)(char **buf);
		int (*func_1)(const char *a1, char **buf);
		int (*func_2)(const char *a1, const char *a2, char **buf);
		int (*func_3)(const char *a1, const char *a2, const char *a3,
			      char **buf);
		int (*func_4)(const char *a1, const char *a2, const char *a3,
			      const char *a4, char **buf);
	} api_func;
	const int nargs;
	const char *use;
};

extern int do_api_func(const struct endpoint *ep, char *argv[], char **buf);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _MTD_CLI_H_ */
