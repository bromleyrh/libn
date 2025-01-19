##
## Makefile.am
##

## Process this file with automake to produce Makefile.in

ACLOCAL_AMFLAGS = -I m4

SUBDIRS = include

EXTRA_DIST = bootstrap build-aux libn.map libn.pc.in .version

build_date = "$(shell date)"
build_vers = "$(shell git rev-parse HEAD)"

if I386
defines := -DI386
else
defines := -DX86_64
endif

debug_cppflags_debug =
debug_cflags_debug = -ggdb3 -O0

std_cppflags = -D_XOPEN_SOURCE=700
std_cflags = @std_flags@

AM_CPPFLAGS = $(defines) $(std_cppflags)
AM_CFLAGS = $(std_cflags) -pipe -Wall -Wextra

if DEBUG
AM_CPPFLAGS += $(debug_cppflags_debug)
AM_CFLAGS += $(debug_cflags_debug)
else
AM_CPPFLAGS += $(debug_cppflags_ndebug)
AM_CFLAGS += $(debug_cflags_ndebug)
endif

if APPLE
sosuf = dylib
else
sosuf = so
endif

pkgconfigdir = @pkgconfigdir@

pkgconfig_DATA = libn.pc

$(pkgconfig_DATA): config.status

noinst_HEADERS = arithmetic.S common.h common.S

if ! GENERIC
arch_sources = add.S mul.S sub.S
endif

BUILT_SOURCES = version.c

CLEANFILES = version.c

build_date_str = "build_date=$(build_date)"
build_vers_str = "build_git_commit_id=$(build_vers)"

version.c:
	echo "const char build_date[] = \"$(build_date_str)\";" >|$@
	echo "const char build_git_commit_id[] = \"$(build_vers_str)\";" >>$@

lib_LTLIBRARIES = libn.la

arithmetic_link = $(abs_builddir)/.libs/libn.$(sosuf)

if LD_VERSION_SCRIPT
version_script = -Wl,--version-script=libn.map
endif

libn_la_SOURCES = $(arch_sources) arithmetic.c version.c
libn_la_CPPFLAGS = $(AM_CPPFLAGS) -Iinclude
libn_la_CFLAGS = $(AM_CFLAGS)
libn_la_LDFLAGS = -version-info @ln_cur@:@ln_rev@:@ln_age@ $(version_script)

include generic/Makefile.am

check_PROGRAMS =
TESTS =

include scripts/Makefile.am
include tests/Makefile.am

install-exec-hook:
	@if ldc=`which ldconfig 2>/dev/null` && test -x "${ldc}"; then \
		echo "Regenerating runtime linker cache" >&2; \
		ldconfig || true; \
	fi
	@echo
	@echo "Note: The path \"$(pkgconfigdir)\" must be added to"
	@echo "PKG_CONFIG_PATH in order to build dependent modules"
	@echo

## vi: set noexpandtab sw=4 ts=4:
