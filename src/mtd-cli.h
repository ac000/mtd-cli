/* SPDX-License-Identifier: GPL-2.0 */

/*
 * mtd-cli.h - Make Tax Digital CLI
 *
 * Copyright (C) 2020 - 2025	Andrew Clayton <ac@sigsegv.uk>
 */

#ifndef _MTD_CLI_H_
#define _MTD_CLI_H_

#include <stdbool.h>
#include <fcntl.h>

#include <libmtdac/mtd.h>

#if defined(__FreeBSD__) && !defined(O_PATH)
#define O_PATH  0
#endif

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
	FUNC_3,
	FUNC_3d,
	FUNC_4d,
};

struct _endpoint {
	const struct endpoint *endpoints;
	const char *cmds;
	const char *api_name;
};

struct endpoint {
	const char *name;
	const enum mtd_api_endpoint api_ep;
	const int nr_req_args;
	const bool file_data;
	const char *args;
};

#endif /* _MTD_CLI_H_ */
