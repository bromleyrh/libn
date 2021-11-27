#
# Makefile
#

mach = $(shell uname -m)

ifeq ($(mach), i686)
wordsize := 32
else
wordsize := 64
endif

cppflags = -D__WORDSIZE=$(wordsize)

all: overflow_test

overflow_test: overflow_test.o add.o sub.o mul.o
	gcc -o $@ $^

overflow_test.o: overflow_test.c
	gcc -c -o $@ -Wall -Wextra $^

add.o: add.S
	gcc $(cppflags) -c -o $@ $^

mul.o: mul.S
	gcc $(cppflags) -c -o $@ $^

sub.o: sub.S
	gcc $(cppflags) -c -o $@ $^

.PHONY: clean

clean:
	rm -f *.o overflow_test

# vi: set noexpandtab sw=4 ts=4:
