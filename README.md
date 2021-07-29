# tonc-template

**THIS IS A MIRROR OF <https://git.sr.ht/~nytpu/tonc-template>!**  I *will not*
respond to pull requests or issues here.  See [Contributing](#contributing) for
details on how to contribute, and <https://git.sr.ht/~nytpu/tonc-template> for
the canonical source.

This template is designed to be used to create gba homebrew using the Tonc
Library.  The template is written from scratch and is designed to be
self-contained (other than devkitPro) and easy to understand and modify.

If you want to make homebrew the [tonc
tutorial](http://www.coranac.com/tonc/text/toc.htm) is the best place to learn
to do so, even if you intend to use libgba afterwards.


## Features

- Easy to understand and modify build system
- Very portable, all that's required to build is a POSIX-compatible sh(1),
  POSIX-compatible make(1), and a devkitARM installation.
- Includes bundled libgbfs for easily including binary files such as art and
  music
- Automatically determines all tool and compiler paths, all you have to do is
  set the $`DEVKITPRO` environment variable.


## Usage
### Requirements

- POSIX or POSIX-compatible `sh`.
- POSIX `make`.  Most `make`s (including GNU Make and BSD Make) support the
  POSIX standard.
- A full devkitARM (`gba-dev`) installation.  See [the
  devkitPro wiki](https://devkitpro.org/wiki/Getting_Started) for help on
  installation.


### Building

Set $`DEVKITPRO` to point to your devkitPro installation (this should be
automatically done most of the time).  You can also set $`CFLAGS`, $`ASFLAGS`,
and $`LDFLAGS` to add additional flags to the C compiler, assembler, and
linker, respectively.

Then run:

    ./configure
    make

and the ROM will be output as `tonc-template.gba` (or `PROGNAME.gba` if you
changed $`PROGNAME` in the `Makefile`)


### Modifying

Change the $`PROGNAME` macro in the `Makefile` to match your game's name.  Then
simply add your code to `main.c` like you normally would.  To add more C source
files, add them to the $`OBJS` macro in the `Makefile`.

In your source code, you can include `<tonc.h>` to get libtonc functions and
`"gbfs.h"` to get GBFS functions.  Also included is a modified version of my
own [libmisc](https://git.sr.ht/~nytpu/libmisc) that provides some useful
functions; notably an arena allocator (`arena.h`) and string utilities
(`string_util.h`).

To use GBFS, first go [the `$(PROGNAME).gba` rule in the
Makefile](Makefile#L95-102) and follow the instructions in the comment to
enable GBFS.  To add files to be bundled with the ROM with GBFS, add the
filename to the $`GBFSFILES` macro in the `Makefile`; if you want to include
images instead of already binary files, then add the files to the $`PNGFILES`
array instead.


## Contributing

The upstream URL of this project is <https://git.sr.ht/~nytpu/tonc-template>.
Send suggestions, bugs, and other contributions to
<~nytpu/public-inbox@lists.sr.ht>.  For help sending a patch through email, see
<https://git-send-email.io>.  You can browse the list archives at
<https://lists.sr.ht/~nytpu/public-inbox>.


## Copyright

Copyright (c) 2021 nytpu <alex [at] nytpu.com>

Licensed under the Boost Software License, version 1.0.  You can view a copy of
the Boost Software License in [`LICENSE`](LICENSE) or at
<https://www.boost.org/LICENSE_1_0.txt>.

This repository contains [libmisc](https://git.sr.ht/~nytpu/libmisc), which is
also Copyright (c) 2021 nytpu and is licensed under the terms of the Boost
Software License, version 1.0.

This repository contains [GBFS](https://pineight.com/gba/#gbfs).  GBFS is
Copyright 2002 Damian Yerrick and is licensed under the terms of the MIT
license.  See the [header of `gbfs.h`](gbfs.h#L4-24) for a full copy of the MIT
license.

All credit for [tonc](https://www.coranac.com/projects/tonc/) goes to cearn.
