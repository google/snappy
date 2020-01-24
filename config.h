// Copyright 2020 Google Inc. All Rights Reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
//       copyright notice, this list of conditions and the following disclaimer
//       in the documentation and/or other materials provided with the
//       distribution.
//     * Neither the name of Google Inc. nor the names of its
//       contributors may be used to endorse or promote products derived from
//       this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef THIRD_PARTY_SNAPPY_OPENSOURCE_CONFIG_H_
#define THIRD_PARTY_SNAPPY_OPENSOURCE_CONFIG_H_

#if !defined(SNAPPY_BAZEL_BUILD)
#include "cmake-config.h"
#else  // defined(SNAPPY_BAZEL_BUILD)

// SNAPPY_HAVE_INCLUDE()
//
// Checks whether the compiler supports an include checking macro, and if so,
// checks whether an include file exists before doing a possibly failing
// `#include` directive.
//
// C++ 17 feature, supported by Clang, GCC, and MSVC.
// https://clang.llvm.org/docs/LanguageExtensions.html#include-file-checking-macros
// https://gcc.gnu.org/onlinedocs/cpp/_005f_005fhas_005finclude.html
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2015/p0061r1.html
#if defined(__has_include)
#define SNAPPY_HAVE_INCLUDE(x) __has_include(x)
#else
#define SNAPPY_HAVE_INCLUDE(x) 0
#endif

// SNAPPY_HAVE_IDENTIFIER()
//
// https://clang.llvm.org/docs/LanguageExtensions.html#is-identifier
#if defined(__is_identifier)
#define SNAPPY_HAVE_IDENTIFIER(x) __is_identifier(x)
#else
#define SNAPPY_HAVE_IDENTIFIER(x) 0
#endif

// The following macros are derived from Abseil, licenced under Apache 2.0.
//
// Do not use this configuration for CMake just yet, some of the
// language/compilers are not supported in all compilers that previously worked
// (e.g. GCC only added support for __has_builtin in GCC 10).
//
// TODO(yannic): How about consuming them directly from Abseil?

// SNAPPY_HAVE_BUILTIN()
// https://github.com/abseil/abseil-cpp/blob/159bf2bf6d1cc8087e02468d071e94d1177d1bae/absl/base/config.h#L136
//
// Checks whether the compiler supports a Clang Feature Checking Macro, and if
// so, checks whether it supports the provided builtin function "x" where x
// is one of the functions noted in
// https://clang.llvm.org/docs/LanguageExtensions.html
//
// Note: Use this macro to avoid an extra level of #ifdef __has_builtin check.
// http://releases.llvm.org/3.3/tools/clang/docs/LanguageExtensions.html
//
// Also supported by some versions of GCC (>= 10?).
// https://gcc.gnu.org/onlinedocs/cpp/_005f_005fhas_005fbuiltin.html#g_t_005f_005fhas_005fbuiltin
#if defined(__has_builtin)
#define SNAPPY_HAVE_BUILTIN(x) __has_builtin(x)
#else
#define SNAPPY_HAVE_BUILTIN(x) 0
#endif

// SNAPPY_IS_LITTLE_ENDIAN
// SNAPPY_IS_BIG_ENDIAN
// https://github.com/abseil/abseil-cpp/blob/159bf2bf6d1cc8087e02468d071e94d1177d1bae/absl/base/config.h#L433
//
// Checks the endianness of the platform.
//
// Notes: uses the built in endian macros provided by GCC (since 4.6) and
// Clang (since 3.2); see
// https://gcc.gnu.org/onlinedocs/cpp/Common-Predefined-Macros.html.
// Otherwise, if _WIN32, assume little endian. Otherwise, bail with an error.
#if defined(SNAPPY_IS_BIG_ENDIAN)
#error "SNAPPY_IS_BIG_ENDIAN cannot be directly set."
#endif
#if defined(SNAPPY_IS_LITTLE_ENDIAN)
#error "SNAPPY_IS_LITTLE_ENDIAN cannot be directly set."
#endif

#if (defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__) && \
     __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
#define SNAPPY_IS_LITTLE_ENDIAN 1
#elif defined(__BYTE_ORDER__) && defined(__ORDER_BIG_ENDIAN__) && \
    __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define SNAPPY_IS_BIG_ENDIAN 1
#elif defined(_WIN32)
#define SNAPPY_IS_LITTLE_ENDIAN 1
#else
#error "snappy endian detection needs to be set up for your compiler"
#endif

// Define to 1 if the compiler supports __builtin_ctz and friends.
#if SNAPPY_HAVE_BUILTIN(__builtin_ctz)
#define HAVE_BUILTIN_CTZ 1
#endif

// Define to 1 if the compiler supports __builtin_expect.
#if SNAPPY_HAVE_BUILTIN(__builtin_expect)
#define HAVE_BUILTIN_EXPECT 1
#endif

// Define to 1 if you have the <byteswap.h> header file.
#if SNAPPY_HAVE_INCLUDE(<byteswap.h>)
#define HAVE_BYTESWAP_H 1
#endif

// Define to 1 if you have a definition for mmap() in <sys/mman.h>.
#if SNAPPY_HAVE_INCLUDE(<sys/mman.h>)
#define HAVE_FUNC_MMAP 1
#endif

// Define to 1 if you have a definition for sysconf() in <unistd.h>.
#if SNAPPY_HAVE_INCLUDE(<unistd.h>)
#define HAVE_FUNC_SYSCONF 1
#endif

// Define to 1 if you have the <gflags/gflags.h> header file.
#if SNAPPY_HAVE_INCLUDE(<gflags/gflags.h>)
#define HAVE_GFLAGS 1
#endif

// Define to 1 if you have the <gtest/gtest.h> header file for Google Test.
#if SNAPPY_HAVE_INCLUDE(<gtest/gtest.h>)
#define HAVE_GTEST 1
#endif

// Define to 1 if you have the "lzo/lzo1x.h" header file
// for the `lzo2' library (-llzo2).
#if SNAPPY_HAVE_INCLUDE("lzo/lzo1x.h")
#define HAVE_LIBLZO2 1
#endif

// Define to 1 if you have the "zlib.h" header file for the `z' library (-lz).
#if SNAPPY_HAVE_INCLUDE("zlib.h")
#define HAVE_LIBZ 1
#endif

// Define to 1 if you have the <sys/endian.h> header file.
#if SNAPPY_HAVE_INCLUDE(<sys/endian.h>)
#define HAVE_SYS_ENDIAN_H 1
#endif

// Define to 1 if you have the <sys/mman.h> header file.
#if SNAPPY_HAVE_INCLUDE(<sys/mman.h>)
#define HAVE_SYS_MMAN_H 1
#endif

// Define to 1 if you have the <sys/resource.h> header file.
#if SNAPPY_HAVE_INCLUDE(<sys/resource.h>)
#define HAVE_SYS_RESOURCE_H 1
#endif

// Define to 1 if you have the <sys/time.h> header file.
#if SNAPPY_HAVE_INCLUDE(<sys/time.h>)
#define HAVE_SYS_TIME_H 1
#endif

// Define to 1 if you have the <sys/uio.h> header file.
#if SNAPPY_HAVE_INCLUDE(<sys/uio.h>)
#define HAVE_SYS_UIO_H 1
#endif

// Define to 1 if you have the <unistd.h> header file.
#if SNAPPY_HAVE_INCLUDE(<unistd.h>)
#define HAVE_UNISTD_H 1
#endif

// Define to 1 if you have the <windows.h> header file.
#if SNAPPY_HAVE_INCLUDE(<windows.h>)
#define HAVE_WINDOWS_H 1
#endif

// Define to 1 if you target processors with SSSE3+ and have <tmmintrin.h>.
#if SNAPPY_HAVE_INCLUDE(<tmmintrin.h>) && defined(__SSSE3__)
#define SNAPPY_HAVE_SSSE3 1
#endif

// Define to 1 if you target processors with BMI2+ and have <bmi2intrin.h>.
#if SNAPPY_HAVE_INCLUDE(<bmi2intrin.h>) && defined(__BMI2__)
#define SNAPPY_HAVE_BMI2 1
#endif

#endif  // !defined(SNAPPY_BAZEL_BUILD)

#endif  // THIRD_PARTY_SNAPPY_OPENSOURCE_CONFIG_H_
