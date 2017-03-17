cmake_minimum_required (VERSION 3.1)
project(Snappy VERSION 1.1.3)

include(CheckIncludeFiles)
include(CheckFunctionExists)
include(CheckLibraryExists)
include(CheckCSourceCompiles)

check_include_files(byteswap.h HAVE_BYTESWAP_H)
check_include_files(dlfcn.h HAVE_DLFCN_H)
check_include_files(inttypes.h HAVE_INTTYPES_H)
check_include_files(memory.h HAVE_MEMORY_H)
check_include_files(stddef.h HAVE_STDDEF_H)
check_include_files(stdint.h HAVE_STDINT_H)
check_include_files(stdlib.h HAVE_STDLIB_H)
check_include_files(strings.h HAVE_STRINGS_H)
check_include_files(string.h HAVE_STRING_H)
check_include_files(sys/byteswap.h HAVE_SYS_BYTESWAP_H)
check_include_files(sys/endian.h HAVE_SYS_ENDIAN_H)
check_include_files(sys/mman.h HAVE_SYS_MMAN_H)
check_include_files(sys/resource.h HAVE_SYS_RESOURCE_H)
check_include_files(sys/stat.h HAVE_SYS_STAT_H)
check_include_files(sys/time.h HAVE_SYS_TIME_H)
check_include_files(sys/types.h HAVE_SYS_TYPES_H)
check_include_files(unistd.h HAVE_UNISTD_H)
check_include_files(windows.h HAVE_WINDOWS_H)
check_include_files(
  "assert.h;complex.h;ctype.h;errno.h;fenv.h;float.h;inttypes.h;iso646.h;limits.h;locale.h;math.h;setjmp.h;signal.h;stdarg.h;stdbool.h;stddef.h;stdint.h;stdio.h;stdlib.h;string.h;tgmath.h;time.h;wchar.h;wctype.h"
  STDC_HEADERS
)

check_library_exists(z zlibVersion "" HAVE_LIBZ)
check_library_exists(lzo2 lzo1x_1_15_compress "" HAVE_LIBLZO2 )
check_library_exists(lzf lzf_compress "" HAVE_LIBLZF)
check_library_exists(fastlz fastlz_compress "" HAVE_LIBFASTLZ)
check_library_exists(quicklz qlz_compress "" HAVE_LIBQUICKLZ)

check_c_source_compiles(
"int main(){ return (__builtin_ctzll(0x100000000LL) == 32) ? 1 : 0; }"
HAVE_BUILTIN_CTZ
)
check_c_source_compiles(
"int main(){ return __builtin_expect(1, 1) ? 1 : 0; }"
HAVE_BUILTIN_EXPECT
)


set(PACKAGE "${PROJECT_NAME}")
set(PACKAGE_NAME "${PACKAGE}")
set(PACKAGE_VERSION "${PROJECT_VERSION}")
set(PACKAGE_STRING "${PACKAGE} ${PACKAGE_VERSION}")
configure_file(
  "${Snappy_SOURCE_DIR}/cmake-config.h.in"
  "${Snappy_BINARY_DIR}/config.h"
)
unset(PACKAGE)
unset(PACKAGE_NAME)
unset(PACKAGE_VERSION)
unset(PACKAGE_STRING)

set(Snappy_sources
  "snappy.cc"
  "snappy-sinksource.cc"
  "snappy-stubs-internal.cc"
  "snappy-c.cc"
)
add_definitions(
  -fPIC
)
add_library(snappy STATIC
  "${Snappy_sources}"
)

if(ENABLE_SNAPPY_TESTS)
  add_definitions(
    -DHAVE_CONFIG_H
  )

  include_directories (
    "${Snappy_SOURCE_DIR}"
    "${Snappy_BINARY_DIR}"
    "${gtest_HEADER_DIRS}"
  )

  set(Snappy_unittest_sources
    "snappy_unittest.cc"
    "snappy-test.cc"
  )

  add_executable(snappy_unittest
    "${Snappy_unittest_sources}"
  )

  set(Snappy_unittest_libs snappy gtest)
  if(HAVE_LIBZ)
    set(Snappy_unittest_libs ${Snappy_unittest_libs} z)
  elseif(HAVE_LIBLZO2)
    set(Snappy_unittest_libs ${Snappy_unittest_libs} lzo2)
  elseif(HAVE_LIBLZF)
    set(Snappy_unittest_libs ${Snappy_unittest_libs} lzf)
  elseif(HAVE_LIBFASTLZ)
    set(Snappy_unittest_libs ${Snappy_unittest_libs} fastlz)
  elseif(HAVE_LIBQUICKLZ)
    set(Snappy_unittest_libs ${Snappy_unittest_libs} quicklz)
  endif()
  target_link_libraries(snappy_unittest "${Snappy_unittest_libs}")
  add_test(
    snappy_unittest
    snappy_unittest
    WORKING_DIRECTORY "${Snappy_BINARY_DIR}"
  )
  add_custom_command(
    TARGET snappy_unittest
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
      "${Snappy_SOURCE_DIR}/testdata" "${Snappy_BINARY_DIR}/testdata"
  )
endif(ENABLE_SNAPPY_TESTS)
