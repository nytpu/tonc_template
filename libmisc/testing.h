// VERSION: 1.0.2
/* This is inspired by <https://text.causal.agency/005-testing-c.txt> and is
 * meant to act as a supplement to make printing messages easier for that setup
 *
 * To use, first set up your makefile as specified in the aforementioned link.
 * Add the file to be tested to the TESTS macro in the makefile to include it
 * in testing.
 *
 * Then, simply add this to the end of the file you want to test:
 *     #ifdef TEST
 *     #include "testing.h"
 *
 *     int
 *     main(void)
 *     {
 *         begin_tests("<FILENAME>");
 *         begin_group("<GROUP>");
 *         // if you just want the condition printed on assertion failure
 *         assert(...);
 *         // if you want a custom message printed on assertion failure
 *         assert_msg(..., "message");
 *         end_group();
 *         end_tests();
 *     }
 *
 *     #endif // TEST
 *
 * Add more groups as needed.
 * It's best to assert the output of a single function (writing helper
 * functions if needed).
 *
 * Note that the test binaries aren't linked with the rest of the code, so
 * you will need to stub functions from other translation units.
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

#pragma once
#ifndef TESTING_H
#define TESTING_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static const char *filename = NULL;
static const char *groupname = NULL;

// equivalent to assert() but prints out a custom message rather than the
// provided assertion
#define assert_msg(expr, msg) \
	if (!(expr)) { \
		fprintf(stderr, "%s\n", msg); \
		abort(); \
	}

// {begin,end}_tests are meant to be used at a file level, but can also be used
// to declare "supergroups" for files with lots of tests
static inline void
begin_tests(const char *fn)
{
	assert_msg(filename == NULL, "You must call end_tests before beginning new tests.");
	assert_msg(fn != NULL, "Provide a filename.");
	filename = fn;
	fprintf(stderr, "---\n%s tests begin.\n", filename);
}
static inline void
end_tests(void)
{
	assert_msg(filename != NULL, "begin_tests MUST be called before end_tests");
	fprintf(stderr, "all %s tests passed.\n", filename);
	filename = NULL;
}

// A testing group is meant to be a small unit of testing, and is the smallest
// unit that will have a success message printed
static inline void
begin_group(const char *gn)
{
	assert_msg(groupname == NULL, "You must call end_group before starting a new group.");
	assert_msg(gn != NULL, "Provide a group name.");
	groupname = gn;
}
static inline void
end_group(void)
{
	assert_msg(groupname != NULL, "begin_group MUST be called before end_group.");
	fprintf(stderr, "\tall %s tests passed.\n", groupname);
	groupname = NULL;
}

#endif // TESTING_H
