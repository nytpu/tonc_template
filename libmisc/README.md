# libmisc — useful C functions and files

[![license: BSL-1.0](https://img.shields.io/badge/license-BSL--1.0-informational.svg)](LICENSE)
[![builds.sr.ht status](https://builds.sr.ht/~nytpu/libmisc.svg)](https://builds.sr.ht/~nytpu/libmisc?)

This repo contains useful functions and files that I use often.  Eventually I
hope it might turn into a “standard library” of sorts that has lots of useful
stuff I can copy into my C projects when necessary.

All code in this repo is ISO C99—no POSIX extensions, no glibc extensions, no
compiler extensions.  At least, it *should* all be C99.  Email me if it isn't!


## Usage

Simply add this repo as a [subrepo](https://github.com/ingydotnet/git-subrepo)
or submodule.  Then add a rule to run `make` in this directory to build a
static `libmisc.a` library, and simply link that in with the rest of your
project.  You can then use the relevant headers.  For an example of using
libmisc as a library, see a sample makefile at
<https://git.sr.ht/~nytpu/genc/tree/dbd0c810aa7a32b4a1ea8a732819571a67e7c231/item/genc#L273-407>.

You can also copy individual files into your project as well.  You should be
sure to copy both the header and accompanying C file.  The version of a file is
included at the very top so you can easily check for updates in the future
(note that the versions are not correlated, and different pairs of files may
have different versions).

If you're worried about manually copying individual files in, updating isn't as
important here because everything should be simple, relatively unchanging, and
not security-critical, where not updating would mean you just miss out on
getting new files and functions rather than getting updates to existing ones.

Some `.c` files have an *optional* dependency on `testing.h`.  This only
affects you if you are already using `testing.h`, but `arena.c` and
`string_util.c` contain tests and could be added to your testing setup.


## File listing

The header comments of the files include more details.  All `.h` files contain
extensive documentation on the functions they contain as well.  Simply click on
the file names to see the contents.

* [`arena.h`](arena.h) and [`arena.c`](arena.c)

Version 1.3.0

Implements a simple [arena
allocator](https://en.wikipedia.org/wiki/Region-based_memory_management).  It
is particularly useful for functions with lots of temporary allocations (string
parsing and modification?) as you don't have to keep track of every little
allocation, and can instead free all memory used afterwards.

* [`err.h`](err.h) and [`err.c`](err.c)

Version 1.0.2

Contains the `err` and `warn` family of functions from *BSD.  Also includes the
{`get`,`set`}`progname` pair of functions.

* [`string_util.h`](string_util.h) and [`string_util.c`](string_util.c)

Version 1.1.2

Useful functions for working with plain C strings.

* [`testing.h`](testing.h)

Version 1.0.2

Useful functions for unit testing.


## Contributing

The upstream URL of this project is <https://git.sr.ht/~nytpu/libmisc>.
Send suggestions, bugs, and other contributions to
<~nytpu/public-inbox@lists.sr.ht>.  For help sending a patch through email, see
<https://git-send-email.io>.  You can browse the list archives at
<https://lists.sr.ht/~nytpu/public-inbox>.


## Copyright

Copyright (c) 2021 nytpu <alex [at] nytpu.com>

C Snippets is licensed under the Boost Software License, version 1.0.  You can
view a copy of the Boost Software License in [LICENSE](LICENSE) or at
<https://www.boost.org/LICENSE_1_0.txt>.
