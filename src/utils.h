/* SPDX-License-Identifier: GPL-2.0 */

/*
 * utils.h - Utiity functions
 *
 * Copyright (C) 2020		Andrew Clayton <andrew@digital-domain.net>
 */

#ifndef _UTILS_H_
#define _UTILS_H_

#ifdef __cplusplus
extern "C" {
#endif

extern char *gen_query_string(const char *src, char *dst, size_t len);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _UTILS_H_ */