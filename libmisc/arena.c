// VERSION: 1.3.0
/* This file provides an implementation of an arena allocator that allows for
 * many allocations, which are then freed all at once.  It is particularly
 * useful for functions with lots of temporary allocations (string parsing and
 * modification?) as you don't have to keep track of every little allocation,
 * and can instead free all memory used afterwards.
 *
 * This implementation is very loosely based off of Zig's arena allocator:
 * https://github.com/ziglang/zig/blob/master/lib/std/heap/arena_allocator.zig
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

#include "arena.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

// An arena "page" is just a buffer of size cap with sz amount of data
// contained in it
struct page {
	size_t sz; // size of the buf's contained data, not the full buf size
	size_t cap;
	uint8_t *buf;
};

// An arena is just a set of buffer pages (len pages long).  The arenas are
// usually of size sys_pgsz, but may be larger.
struct arena_s {
	size_t sys_pgsz;
	size_t len;
	struct page *pg; // array of pages
};


// I usually avoid using these system detect macros and for this case it's
// probably not worth it, but I'm gonna do it anyways
// TODO: figure out how to get page size on more systems
#if defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE >= 200112L
#include <unistd.h>
static size_t
get_page_size(void)
{
	return sysconf(_SC_PAGESIZE);
}
#elif defined(_BSD_SOURCE)
#include <unistd.h>
static size_t
get_page_size(void)
{
	return getpagesize();
}
#elif defined(_WIN32)
#include <windows.h>
static size_t
get_page_size(void)
{
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	return si.dwPageSize;
}
#else
static size_t
get_page_size(void)
{
	return ARENA_DEFAULT_PAGE_SIZE;
}
#endif

// Add a new, empty page of size to an arena.  Returns 0 if successful, -1 on
// failure
static int
arena_new_page(arena *a, size_t size)
{
	// do this runaround to prevent nullifying the valid a->pg on
	// allocation failure
	struct page *p = realloc(a->pg, (a->len + 1) * sizeof(*a->pg));
	if (!p) return -1;
	a->pg = p;

	a->pg[a->len].sz = 0;
	a->pg[a->len].cap = size;
	a->pg[a->len].buf = calloc(size, sizeof(*a->pg[a->len].buf));
	if (!a->pg[a->len].buf) return -1;

	a->len++;
	return 0;
}

arena *
arena_init(void)
{
	arena *a = calloc(1, sizeof(*a));
	if (!a) return NULL;
	a->sys_pgsz = get_page_size();
	a->len = 0;
	a->pg = NULL;
	int rc = arena_new_page(a, a->sys_pgsz);
	if (rc == -1) {
		arena_deinit(a);
		return NULL;
	}
	return a;
}

void
arena_deinit(arena *a)
{
	for (size_t i = 0; i < a->len; ++i) free(a->pg[i].buf);
	free(a->pg);
	free(a);
}

void *
arena_alloc(arena *a, size_t size)
{
	for (size_t i = 0; i < a->len; ++i) {
		if ((a->pg[i].cap - a->pg[i].sz) >= size) {
			a->pg[i].sz += size;
			return a->pg[i].buf + (a->pg[i].sz - size);
		}
	}

	size_t newsz = (size > a->sys_pgsz) ? size : a->sys_pgsz;
	int rc = arena_new_page(a, newsz);
	if (rc == -1) return NULL;
	a->pg[a->len - 1].sz += newsz;
	return a->pg[a->len - 1].buf;
}


#ifdef TEST
#include "testing.h"

int
main(void)
{
	begin_tests("arena.c");

	begin_group("arena_init");
	arena *a = arena_init();
	assert(a != NULL);
	printf("\tDetected page size: %ld\n", a->sys_pgsz);
	// checking for sensible defaults, not really necessary
	assert(a->len == 1);
	assert(a->pg != NULL);
	assert(a->pg[0].sz == 0);
	assert(a->pg[0].cap == a->sys_pgsz);
	assert(a->pg[0].buf != NULL);
	end_group();

	begin_group("arena_alloc");
	void *dummy = arena_alloc(a, 10);
	assert(dummy == a->pg[0].buf);
	assert(a->pg[0].sz == 10);

	dummy = arena_alloc(a, a->sys_pgsz + 1);
	assert(a->len == 2);
	assert(a->pg[1].sz == a->sys_pgsz + 1);
	assert(a->pg[1].cap == a->sys_pgsz + 1);
	assert(dummy == a->pg[1].buf);

	dummy = arena_alloc(a, 20);
	assert(dummy == (a->pg[0].buf + 10));
	assert(a->pg[0].sz == 30);
	end_group();

	arena_deinit(a);
	end_tests();
	return 0;
}

#endif // TEST
