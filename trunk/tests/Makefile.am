##
## Makefile.am
##

check_PROGRAMS += tests/arithmetic_test tests/overflow_test

TESTS += tests/arithmetic_test tests/overflow_test

if APPLE
test_ldflags = -rpath @abs_top_builddir@/.libs
else
test_ldflags = -no-install -rpath @abs_top_builddir@/.libs
endif

tests_arithmetic_test_SOURCES = tests/arithmetic_test.c
tests_arithmetic_test_CPPFLAGS = $(AM_CPPFLAGS) -Iinclude
tests_arithmetic_test_CFLAGS = $(AM_CFLAGS)
tests_arithmetic_test_LDADD = $(arithmetic_link)
tests_arithmetic_test_LDFLAGS = $(test_ldflags)
tests_arithmetic_test_DEPENDENCIES = libn.la

tests_overflow_test_SOURCES = tests/overflow_test.c
tests_overflow_test_CPPFLAGS = $(AM_CPPFLAGS) -Iinclude
tests_overflow_test_CFLAGS = $(AM_CFLAGS) -Wno-dangling-else
tests_overflow_test_LDADD = $(arithmetic_link)
tests_overflow_test_LDFLAGS = $(test_ldflags)
tests_overflow_test_DEPENDENCIES = libn.la

## vi: set noexpandtab sw=4 ts=4:
