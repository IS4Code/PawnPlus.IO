PawnPlus.IO
==========

_PawnPlus.IO_ is an addon for _[PawnPlus](//github.com/IllidanS4/PawnPlus/)_ allowing manipulation of various I/O streams, files, and network sockets, both synchronously and asynchronously.

## Documentation
See the [wiki](//github.com/IllidanS4/PawnPlus.IO/wiki) for documentation.

## Installation
Download the latest [release](//github.com/IllidanS4/PawnPlus.IO/releases/latest) for your platform to the "plugins" directory and add "PawnPlus.IO" (or "PawnPlus.IO.so" on Linux) to the `plugins` line in server.cfg.

Include [PawnPlus.IO.inc](pawno/include/PawnPlus.IO.inc) in your Pawn program and you are done.

_[PawnPlus](//github.com/IllidanS4/PawnPlus/)_ has to be active in order for this plugin to work.

## Building
Use Visual Studio to build the project on Windows, or `make` or `make static` on Linux. Requires GCC >= 4.9.
