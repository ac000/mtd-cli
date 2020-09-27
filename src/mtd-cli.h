/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli.h - Make Tax Digital CLI
 *
 * Copyright (C) 2020		Andrew Clayton <andrew@digital-domain.net>
 */

#ifndef _MTD_CLI_H_
#define _MTD_CLI_H_

#include <libmtdac/mtd.h>

/*
 * Funky macro magic so we can autogenerate the endpoint structure
 * name.
 *
 * API will be defined in the mtd-cli-*.c files, e.g
 *
 *     #define API	ni
 *
 * this will then allow
 *
 *     const struct _endpoint ENDPOINT = {
 *
 * which will get turned into
 *
 *     const struct _endpoint ni_endpoint = {
 */
#define EP_DUMMY()
#define EP(name)		name ## _endpoint
#define EP_EVAL(...)		__VA_ARGS__
#define ENDPOINT		EP_EVAL(EP EP_DUMMY() (API))

enum function_selector {
	FUNC_0 = 0,
	FUNC_1,
	FUNC_1d,
	FUNC_2,
	FUNC_2d,
	FUNC_3d,
	FUNC_4d,
};

struct _endpoint {
	const struct endpoint *endpoints;
	const char *cmds;
	const char *api_name;
};

/*
 * Functions suffixed with a 'd' are ones that take a
 * struct mtd_dsrc_ctx rather than a char * as their
 * first argument.
 *
 * The number pertains to the number of the arguments the
 * function takes not including buf.
 */
struct endpoint {
	const char *name;
	const union {
		int (*func_0)(char **buf);
		int (*func_1)(const char *a1, char **buf);
		int (*func_1d)(const struct mtd_dsrc_ctx *dsctx, char **buf);
		int (*func_2)(const char *a1, const char *a2, char **buf);
		int (*func_2d)(const struct mtd_dsrc_ctx *dsctx,
			       const char *a2, char **buf);
		int (*func_3d)(const struct mtd_dsrc_ctx *dsctx,
			       const char *a2, const char *a3, char **buf);
		int (*func_4d)(const struct mtd_dsrc_ctx *dsctx,
			       const char *a2, const char *a3, const char *a4,
			       char **buf);
	} api_func;
	const enum function_selector func;
	const int nr_req_args;
	const char *use;
};

#endif /* _MTD_CLI_H_ */
