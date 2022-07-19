#include <gtest/gtest.h>

extern "C" {
#include "utils/numutils.h"
}

TEST(numutils, positive_ints) {
  ASSERT_EQ(next_pow2(3), 4);
  ASSERT_EQ(next_pow2(15), 16);
  ASSERT_EQ(next_pow2(17), 32);
  ASSERT_EQ(next_pow2(0), 0);
}

TEST(numutils, negative_ints) {
  ASSERT_EQ(next_pow2(-3), 0);
  ASSERT_EQ(next_pow2(-165), 0);
  ASSERT_EQ(next_pow2(-1235), 0);
}
