// VERSION: 1.1.2
/* Utilities to make working with plain old C strings easier.
 *
 *
 * Copyright (c) 2021 nytpu <alex [at] nytpu.com>
 * SPDX-License-Identifier: BSL-1.0
 * The orginal source for this file is available at <https://git.sr.ht/~nytpu/libmisc>.
 *
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 *
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer, must
 * be included in all copies of the Software, in whole or in part, and all
 * derivative works of the Software, unless such copies or derivative works are
 * solely in the form of machine-executable object code generated by a source
 * language processor.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include "string_util.h"

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// rip-off from <https://text.causal.agency/024-seprintf.txt>, which is itself
// a rip-off of seprint from plan 9's libc.
char *
seprintf(char *ptr, char *end, const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	int n = vsnprintf(ptr, end - ptr, fmt, ap);
	va_end(ap);
	if (n < 0) return NULL;
	if (n > end - ptr) return end;
	return ptr + n;
}

bool
string_starts_with(const char *str, const char *prefix)
{
	return !(strncmp(str, prefix, strlen(prefix)));
}

bool
string_ends_with(const char *str, const char *suffix)
{
	int str_len = strlen(str);
	int suffix_len = strlen(suffix);
	return (str_len >= suffix_len)
		&& (strcmp(str + (str_len - suffix_len), suffix) == 0);
}

#ifdef TEST
#include "testing.h"
#include <stdlib.h>

int
main(void)
{
	begin_tests("string_util.c");

	begin_group("seprintf");
	char buf[21];
	char *ptr = buf, *end = &buf[sizeof(buf)];
	for (size_t i = 0; i < sizeof(buf); ++i) {
		ptr = seprintf(ptr, end, "%1d", i % 10);
		assert(ptr == &buf[i + 1]);
	}
	assert(ptr == end);
	ptr = seprintf(ptr, end, "hello, world!");
	assert(ptr == end);
	end_group();

	begin_group("string_starts_with");
	assert(string_starts_with("ello, world!", "h") == false);
	assert(string_starts_with("hello, world!", "hello, world") == true);
	assert(string_starts_with("¡hello, world!", "hello") == false);
	assert(string_starts_with("hello, world!", "h") == true);
	assert(string_starts_with("hello, world!", "ello") == false);
	assert(string_starts_with("hello, world!", "world!") == false);
	assert(string_starts_with("/CN=test", "/CN=") == true);
	end_group();

	begin_group("string_ends_with");
	assert(string_ends_with("h", "ello, world!") == false);
	assert(string_ends_with("hello, world!", "ello, world!") == true);
	assert(string_ends_with("hello, world! 2!", "ello, world!") == false);
	assert(string_ends_with("hello, world!", "!") == true);
	assert(string_ends_with("hello, world!", "hello") == false);
	assert(string_ends_with("hello, world!", "world") == false);
	end_group();

	end_tests();
	return 0;
}

#endif // TEST