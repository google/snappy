// Copyright 2011 Google Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
//      Unless required by applicable law or agreed to in writing, software
//      distributed under the License is distributed on an "AS IS" BASIS,
//      WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//      See the License for the specific language governing permissions and
//      limitations under the License.

#include <algorithm>
#include <string>

#include "snappy-stubs-internal.h"

namespace snappy {

void Varint::Append32(string* s, uint32 value) {
  char buf[Varint::kMax32];
  const char* p = Varint::Encode32(buf, value);
  s->append(buf, p - buf);
}

}  // namespace snappy
