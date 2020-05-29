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

enum nr_func_args {
	FUNC_0 = 0,
	FUNC_1,
	FUNC_2,
	FUNC_3,
	FUNC_4,
};

struct _endpoint {
	const struct endpoint *endpoints;
	const char *cmds;
	const char *api_name;
};

struct endpoint {
	const char *name;
	const union {
		int (*func_0)(char **buf);
		int (*func_1)(const char *a1, char **buf);
		int (*func_2)(const char *a1, const char *a2, char **buf);
		int (*func_3)(const char *a1, const char *a2, const char *a3,
			      char **buf);
		int (*func_4)(const char *a1, const char *a2, const char *a3,
			      const char *a4, char **buf);
	} api_func;
	const enum nr_func_args func;
	const int nr_req_args;
	const char *use;
};

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _MTD_CLI_H_ */
