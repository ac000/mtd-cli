/* SPDX-License-Identifier: GPL-2.0 */

/*
 * utils.c - Utility functions
 *
 * Copyright (C) 2020		Andrew Clayton <andrew@digital-domain.net>
 */

#include <stddef.h>

char *gen_query_string(const char *src, char *dst, size_t len)
{
	char *ptr = dst;
	size_t i = 1;

	*(dst++) = '?';
	while (*src && i++ < len - 1) {
		if (*src == ',')
			*dst = '&';
		else
			*dst = *src;
		src++;
		dst++;
	}
	*dst = '\0';

	return ptr;
}
