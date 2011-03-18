// Copyright 2011 Google Inc. All Rights Reserved.

#include <string.h>

#include "snappy-sinksource.h"

namespace snappy {

Source::~Source() { }

Sink::~Sink() { }

char* Sink::GetAppendBuffer(size_t length, char* scratch) {
  return scratch;
}

ByteArraySource::~ByteArraySource() { }

size_t ByteArraySource::Available() const { return left_; }

const char* ByteArraySource::Peek(size_t* len) {
  *len = left_;
  return ptr_;
}

void ByteArraySource::Skip(size_t n) {
  left_ -= n;
  ptr_ += n;
}

UncheckedByteArraySink::~UncheckedByteArraySink() { }

void UncheckedByteArraySink::Append(const char* data, size_t n) {
  // Do no copying if the caller filled in the result of GetAppendBuffer()
  if (data != dest_) {
    memcpy(dest_, data, n);
  }
  dest_ += n;
}

char* UncheckedByteArraySink::GetAppendBuffer(size_t len, char* scratch) {
  return dest_;
}


}
