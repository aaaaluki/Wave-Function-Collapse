#include <gtest/gtest.h>

extern "C" {
#include "utils/numutils.h"
}

TEST(next_pow2, HandlesPositiveInput) {
  EXPECT_EQ(next_pow2(3), 4);
  EXPECT_EQ(next_pow2(15), 16);
  EXPECT_EQ(next_pow2(17), 32);
}

TEST(next_pow2, HandlesNegativeInput) {
  EXPECT_EQ(next_pow2(-3), 0);
  EXPECT_EQ(next_pow2(-165), 0);
  EXPECT_EQ(next_pow2(-1235), 0);
}

TEST(next_pow2, HandlesZeroInput) {
  EXPECT_EQ(next_pow2(0), 0);
}
