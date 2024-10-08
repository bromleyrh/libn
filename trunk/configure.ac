#
# configure.ac
#

AC_INIT([libn], m4_esyscmd_s([cat .version]))
AC_PREREQ([2.69])

env_cflags=$CFLAGS

AC_CONFIG_SRCDIR([add.S])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])

AC_CANONICAL_TARGET

dnl ensure installed files are accessible by non-root users when parent
dnl directories are created
dnl FIXME: Honor file mode creation mask for non-installation directories
MKDIR_P="build-aux/mkpath -m 0755"

AM_INIT_AUTOMAKE([foreign no-define subdir-objects])
AM_SILENT_RULES([yes])
LT_INIT([disable-static])

AS_CASE(
    [$target_cpu],
        [i386|i486|i586|i686],
            [arch=i386],
        [x86_64],
            [arch=x86_64],
        [arch=generic]
)
AM_CONDITIONAL([I386], [test $arch = "i386"])
AM_CONDITIONAL([X86_64], [test $arch = "x86_64"])
AM_CONDITIONAL([GENERIC], [test $arch = "generic"])

AS_CASE(
    [$target_os],
        [*darwin*],
            [platform=darwin],
        [*freebsd*],
            [platform=freebsd],
        [*linux*],
            [platform=linux],
        [AC_MSG_ERROR([unsupported platform], [1])]
)
AM_CONDITIONAL([APPLE], [test $platform = "darwin"])
AM_CONDITIONAL([FREEBSD], [test $platform = "freebsd"])
AM_CONDITIONAL([LINUX], [test $platform = "linux"])

AM_PROG_AS
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_RANLIB

AC_CHECK_PROGS([pkgcfg], [pkg-config pkgconf])

AX_LD_VERSION_SCRIPT

AC_ARG_ENABLE([debugging],
              [  --enable-debugging      enable debugging],
              [AS_CASE(
                  [$enableval],
                      [yes],
                          [debug=true],
                      [no],
                          [debug=false],
                      [AC_MSG_ERROR([invalid "--enable-debugging" argument])]
               )
              ],
              [debug=false])
AM_CONDITIONAL([DEBUG], [test $debug = true])

AC_ARG_WITH([pkgconfigdir],
            [  --with-pkgconfigdir=DIR install pkg-config data in DIR],
            [pkgconfigdir=$withval],
            [pkgconfigdir="$libdir/pkgconfig"])
AC_SUBST([pkgconfigdir])

AC_SUBST([ln_cur], [0])
AC_SUBST([ln_age], [0])
AC_SUBST([ln_rev], [0])

dnl FIXME: Later, only prevent Autoconf from adding "-g -O2" to CFLAGS
CFLAGS=$env_cflags

AC_CONFIG_FILES([Makefile include/Makefile libn.pc])
AC_CONFIG_HEADERS([config.h])
AC_OUTPUT

dnl Pass sed output to cat in the following to write output in larger blocks,
dnl reducing the needed time to run the commands
dnl FIXME: Replace with wrapper script or utility
postlink_cmds=:
AS_IF(
    [test $platform = "darwin"],
    [libpath="$(pwd | sed "s/'/'\\\\\\\\\\\\\\\\\\\''/g")"
     libpath="$(printf "$libpath" | sed -e 's/\//\\\//g')"
     libpath="${libpath}\/.libs\/libn.dylib"
     postlink_cmds="${postlink_cmds}; scripts\/fix_up_linking_os_x.sh"
     postlink_cmds="$postlink_cmds @OUTPUT@ '$libpath'"]
)
lt=libtool
sed_edit_expr="s/postlink_cmds=\"\"/postlink_cmds=\"$postlink_cmds\"/"
sed -e "$sed_edit_expr" $lt | cat >${lt}.new \
    && mv -f ${lt}.new $lt \
    && chmod +x $lt

cat <<-EOF

$PACKAGE_NAME configuration

    Target architecture: $target_cpu

               Compiler: $CC

              Debugging: $debug

    Installation prefix: $prefix

EOF

dnl vi: set expandtab sw=4 ts=4:
