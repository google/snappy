m4_define([snappy_major], [1])
m4_define([snappy_minor], [0])
m4_define([snappy_patchlevel], [1])

# Libtool shared library interface versions (current:revision:age)
# Update this value for every release!  (A:B:C will map to foo.so.(A-C).C.B)
# http://www.gnu.org/software/libtool/manual/html_node/Updating-version-info.html
m4_define([snappy_ltversion], [1:1:0])

AC_INIT([snappy], [snappy_major.snappy_minor.snappy_patchlevel])
AC_CONFIG_MACRO_DIR([m4])

# These are flags passed to automake (though they look like gcc flags!)
AM_INIT_AUTOMAKE([-Wall -Werror])

LT_INIT
AC_SUBST([LIBTOOL_DEPS])
AC_PROG_CXX
AC_LANG([C++])
AC_C_BIGENDIAN
AC_CHECK_HEADERS([stdint.h stddef.h sys/mman.h])

# Don't use AC_FUNC_MMAP, as it checks for mappings of already-mapped memory,
# which we don't need (and does not exist on Windows).
AC_CHECK_FUNC([mmap])

GTEST_LIB_CHECK([], [true], [true # Ignore; we can live without it.])

AC_ARG_WITH([gflags],
  [AS_HELP_STRING(
    [--with-gflags],
    [use Google Flags package to enhance the unit test @<:@default=check@:>@])],
    [],
    [with_gflags=check])

if test "x$with_gflags" != "xno"; then
  PKG_CHECK_MODULES(
    [gflags],
    [libgflags],
    [AC_DEFINE([HAVE_GFLAGS], [1], [Use the gflags package for command-line parsing.])],
    [if test "x$with_gflags" != "xcheck"; then
      AC_MSG_FAILURE([--with-gflags was given, but test for gflags failed])
    fi])
fi

# See if we have __builtin_expect.
# TODO: Use AC_CACHE.
AC_MSG_CHECKING([if the compiler supports __builtin_expect])
 
AC_TRY_COMPILE(, [
    return __builtin_expect(1, 1) ? 1 : 0
], [
    snappy_have_builtin_expect=yes
    AC_MSG_RESULT([yes])
], [
    snappy_have_builtin_expect=no
    AC_MSG_RESULT([no])
])
if test x$snappy_have_builtin_expect = xyes ; then
    AC_DEFINE([HAVE_BUILTIN_EXPECT], [1], [Define to 1 if the compiler supports __builtin_expect.])
fi

# See if we have working count-trailing-zeros intrinsics.
# TODO: Use AC_CACHE.
AC_MSG_CHECKING([if the compiler supports __builtin_ctzll])

AC_TRY_COMPILE(, [
    return (__builtin_ctzll(0x100000000LL) == 32) ? 1 : 0
], [
    snappy_have_builtin_ctz=yes
    AC_MSG_RESULT([yes])
], [
    snappy_have_builtin_ctz=no
    AC_MSG_RESULT([no])
])
if test x$snappy_have_builtin_ctz = xyes ; then
    AC_DEFINE([HAVE_BUILTIN_CTZ], [1], [Define to 1 if the compiler supports __builtin_ctz and friends.])
fi

# Other compression libraries; the unit test can use these for comparison
# if they are available. If they are not found, just ignore.
AC_CHECK_LIB([z], [zlibVersion],, [true])
AC_CHECK_LIB([lzo2], [lzo1x_1_15_compress],, [true])
AC_CHECK_LIB([lzf], [lzf_compress],, [true])
AC_CHECK_LIB([fastlz], [fastlz_compress],, [true])
AC_CHECK_LIB([quicklz], [qlz_compress],, [true])

# These are used by snappy-stubs-public.h.in.
if test "$ac_cv_header_stdint_h" = "yes"; then
    AC_SUBST([ac_cv_have_stdint_h], [1])
else
    AC_SUBST([ac_cv_have_stdint_h], [0])
fi
if test "$ac_cv_header_stddef_h" = "yes"; then
    AC_SUBST([ac_cv_have_stddef_h], [1])
else
    AC_SUBST([ac_cv_have_stddef_h], [0])
fi

# Export the version to snappy-stubs-public.h.
SNAPPY_MAJOR="snappy_major"
SNAPPY_MINOR="snappy_minor"
SNAPPY_PATCHLEVEL="snappy_patchlevel"

AC_SUBST([SNAPPY_MAJOR])
AC_SUBST([SNAPPY_MINOR])
AC_SUBST([SNAPPY_PATCHLEVEL])
AC_SUBST([SNAPPY_LTVERSION], snappy_ltversion)

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile snappy-stubs-public.h])
AC_OUTPUT
