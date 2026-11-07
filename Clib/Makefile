# POSIX build of the object simple_system.ecf expects on macOS and Linux.
# Usage: make -C Clib
CC ?= cc
CFLAGS ?= -O2 -fPIC

simple_system.o: simple_system.c simple_system.h
	$(CC) $(CFLAGS) -c simple_system.c -o simple_system.o

clean:
	rm -f simple_system.o

.PHONY: clean
