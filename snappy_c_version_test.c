/* Compile this helper as C so C++ headers cannot supply the version macros. */
#include "snappy-c.h"

void snappy_test_c_version(int version[4]) {
  version[0] = SNAPPY_MAJOR;
  version[1] = SNAPPY_MINOR;
  version[2] = SNAPPY_PATCHLEVEL;
  version[3] = SNAPPY_VERSION;
}
