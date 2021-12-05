#
# Makefile
#

mach = $(shell uname -m)

ifeq ($(mach), i686)
cppflags := -DI386
else
cppflags := -DX86_64
endif

debugflags = -ggdb3 -O0

asmflags = $(debugflags)
cflags = $(debugflags) -Iinclude -Wall -Wextra

all: arithmetic_test overflow_test

arithmetic_test: arithmetic_test.o arithmetic.o add.o sub.o mul.o
	gcc -o $@ $^

arithmetic_test.o: arithmetic_test.c
	gcc -c $(cflags) -o $@ $^

overflow_test: overflow_test.o arithmetic.o add.o sub.o mul.o
	gcc -o $@ $^

overflow_test.o: overflow_test.c
	gcc -c $(cflags) -o $@ $^

arithmetic.o: arithmetic.c
	gcc $(cppflags) -c $(cflags) -o $@ $^

add.o: add.S
	gcc $(cppflags) -c $(asmflags) -o $@ $^

mul.o: mul.S
	gcc $(cppflags) -c $(asmflags) -o $@ $^

sub.o: sub.S
	gcc $(cppflags) -c $(asmflags) -o $@ $^

.PHONY: clean

clean:
	rm -f *.o arithmetic_test overflow_test

# vi: set noexpandtab sw=4 ts=4:
