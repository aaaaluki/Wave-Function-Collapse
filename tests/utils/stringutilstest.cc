#include <gtest/gtest.h>
#include <string.h>

extern "C" {
#include "utils/stringutils.h"
}

TEST(strconcat, HandlesNonNullPointers) {
  const char *s1 = "Hello, ";
  const char *s2 = "there!";

  char *s = strconcat(s1, s2);

  ASSERT_EQ(strcmp(s, "Hello, there!"), 0);
}
