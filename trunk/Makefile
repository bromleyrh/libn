#
# Makefile
#

all: overflow

overflow: add64.s overflow.c
	gcc -o $@ $^

.PHONY: clean

clean:
	rm -f *.o overflow

# vi: set noexpandtab sw=4 ts=4:
