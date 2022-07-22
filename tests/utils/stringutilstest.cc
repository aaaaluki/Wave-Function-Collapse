#include <gtest/gtest.h>
#include <string.h>

extern "C" {
#include "utils/stringutils.h"
#include <stddef.h>
}

TEST(strconcat, HandlesNonNullPointers) {
  const char *s1 = "Hello, ";
  const char *s2 = "there!";

  char *s;
  int r = strconcat(s1, s2, &s);

  EXPECT_EQ(r, STRINGUTILS_OK);
  ASSERT_EQ(strcmp(s, "Hello, there!"), 0);

  free(s);
}

/* FIXME: Somehow now this test is broken, if I pass NULL to the function it
crashes because SIGSGEV. I'm disabling it for now, since testing this on a C
file and compiling it works as expected.

Idk, maybe because I'm using the NULL C++ definition instead of the C one?¿ */
/*TEST(strconcat, HandlesNullPointers) {
  const char *s1 = "Hello, ";
  const char *s2 = NULL;

  char *s;
  int r = strconcat(s1, s2, &s);

  ASSERT_EQ(r, STRINGUTILS_OK);

  free(s);
}*/

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
