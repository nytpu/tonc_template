#!/usr/bin/make -f
# Pure POSIX makefile for libmisc
#
#
# Copyright (c) 2021 nytpu <alex [at] nytpu.com>
# SPDX-License-Identifier: BSL-1.0
# The orginal source for this file is available at <https://git.sr.ht/~nytpu/genc>.
#
# Permission is hereby granted, free of charge, to any person or organization
# obtaining a copy of the software and accompanying documentation covered by
# this license (the "Software") to use, reproduce, display, distribute,
# execute, and transmit the Software, and to prepare derivative works of the
# Software, and to permit third-parties to whom the Software is furnished to
# do so, all subject to the following:
#
# The copyright notices in the Software and this entire statement, including
# the above license grant, this restriction and the following disclaimer, must
# be included in all copies of the Software, in whole or in part, and all
# derivative works of the Software, unless such copies or derivative works are
# solely in the form of machine-executable object code generated by a source
# language processor.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
# SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
# FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
# ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
# DEALINGS IN THE SOFTWARE.
.POSIX:
.SILENT:
.SUFFIXES:

## program info
PROGNAME = libmisc

## default programs
CC = cc
AR = ar

CFLAGS =

## files & dependencies
LIBS = $(PROGNAME).a
OBJS = arena.o string_util.o

include config.mk


## default target
all: $(LIBS)


## dependencies
arena.o: arena.h
string_util.o: string_util.h
$(OBJS): config.mk Makefile


## rules
.SUFFIXES: .o .c
.c.o:
	printf 'Compiling\t$<\n'
	$(CC) $(CFLAGS) -c -o $@ $<

$(PROGNAME).a: $(OBJS)
	printf 'Archiving\t$?\n'
	ar -cr $@ $?


## phonies
# technically .PHONY isn't POSIX, but targets with a leading period aren't
# reserved so it's still valid, it'd just be useless to actually execute
.PHONY: all clean
clean:
	rm -rf $(OBJS) $(LIBS) $(TESTS)
