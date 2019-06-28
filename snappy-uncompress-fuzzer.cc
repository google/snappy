// Copyright 2019 Google Inc. All Rights Reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
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
//
// libFuzzer harness for fuzzing snappy decompression routine.

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <string>

#include "snappy.h"

namespace snappy {

// Supplies random data sourced from libFuzzer to the snappy uncompressor,
// decompressing its output and running some checks in the process.
extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
  string input(reinterpret_cast<const char*>(data), size);

  size_t uncompressed_len = 0;
  bool getcomp_len_success = snappy::GetUncompressedLength(
      input.data(),
      input.size(),
      &uncompressed_len);
  // Check that GetUncompressedLength() does not return a very large
  // value (1 MB) on success.
  assert(!getcomp_len_success || uncompressed_len < (1 << 20));

  // Uncompress
  string uncompressed_out;
  bool uncompress_success = snappy::Uncompress(
      input.data(),
      input.size(),
      &uncompressed_out);

  assert(uncompress_success);
  return 0;
}

} // namespace snappy