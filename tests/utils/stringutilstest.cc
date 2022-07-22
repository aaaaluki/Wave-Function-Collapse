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

  free(s);
}

TEST(strconcat, HandlesNullPointers) {
  const char *s1 = "Hello, ";
  const char *s2 = NULL;

  char *s = strconcat(s1, s2);

  ASSERT_EQ(s == NULL, true);

  free(s);
}

TEST(strsplit, AllSpltcharPossiblities) {
  const char *s = "directory/subdirectory/file.txt";
  char *lhs, *rhs;

  // Split by last occurence
  strsplit(s, '/', STRSPLIT_LAST, &lhs, &rhs);
  EXPECT_EQ(strcmp(lhs, "directory/subdirectory"), 0);
  EXPECT_EQ(strcmp(rhs, "file.txt"), 0);

  free(lhs);
  free(rhs);

  // Split by first occurence
  strsplit(s, '/', STRSPLIT_FIRST, &lhs, &rhs);
  EXPECT_EQ(strcmp(lhs, "directory"), 0);
  EXPECT_EQ(strcmp(rhs, "subdirectory/file.txt"), 0);

  free(lhs);
  free(rhs);
}
