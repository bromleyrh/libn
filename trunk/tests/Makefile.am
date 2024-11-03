##
## Makefile.am
##

check_PROGRAMS += tests/arithmetic_test tests/overflow_test

LOG_DRIVER = tests/test_wrapper.sh

TESTS += tests/arithmetic_test tests/overflow_test

TESTS_ENVIRONMENT = BUILDDIR=@abs_top_builddir@; export BUILDDIR;

if APPLE
test_ldflags = -headerpad_max_install_names -rpath @abs_top_builddir@/.libs
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

.PHONY: check-exec check-noexec

check-exec:
	TESTS_SKIP=0 $(MAKE) check

check-noexec:
	TESTS_SKIP=1 $(MAKE) check

## vi: set noexpandtab sw=4 ts=4:
