#include <gtest/gtest.h>

extern "C" {
#include "argparse/argparse.h"
}

TEST(ArgParse, SimpleTest) {
  int argc = 5;
  const char **argv = (const char **)malloc(argc);
  argv[0] = (char *)"argparsetest";
  argv[1] = (char *)"-abcde";
  argv[2] = (char *)"-f";
  argv[3] = (char *)"spacearg";
  argv[4] = (char *)"-fnospacearg";

  const char *ostr = (char *)"abcdef:";

  AParse ap;
  argparse_init(&ap, argc, argv, ostr);

  EXPECT_EQ(argparse_next(&ap), 'a');
  EXPECT_EQ(argparse_next(&ap), 'b');
  EXPECT_EQ(argparse_next(&ap), 'c');
  EXPECT_EQ(argparse_next(&ap), 'd');
  EXPECT_EQ(argparse_next(&ap), 'e');
  EXPECT_EQ(argparse_next(&ap), 'f');
  EXPECT_EQ(ap.arg, "spacearg");
  EXPECT_EQ(argparse_next(&ap), 'f');
  EXPECT_EQ(ap.arg, "nospacearg");
  EXPECT_EQ(argparse_next(&ap), -1);

  free(argv);
}

TEST(ArgParse, NoArgTest) {
  int argc = 1;
  const char **argv = (const char **)malloc(argc);
  argv[0] = (char *)"argparsetest";
  const char *ostr = (char *)"abcdef:";

  AParse ap;
  argparse_init(&ap, argc, argv, ostr);

  free(argv);
}

TEST(ArgParse, ErrorDoubleDashTest) {
  int argc = 2;
  const char **argv = (const char **)malloc(argc);
  argv[0] = (char *)"argparsetest";
  argv[1] = (char *)"--abcde";
  const char *ostr = (char *)"abcdef:";

  AParse ap;
  argparse_init(&ap, argc, argv, ostr);
  ASSERT_EQ(argparse_next(&ap), -1);

  free(argv);
}

TEST(ArgParse, ErrorNoArgumentGivenTest) {
  int argc = 2;
  const char **argv = (const char **)malloc(argc);
  argv[0] = (char *)"argparsetest";
  argv[1] = (char *)"-f";
  const char *ostr = (char *)"abcdef:";

  AParse ap;
  argparse_init(&ap, argc, argv, ostr);
  ASSERT_EQ(argparse_next(&ap), -1);

  free(argv);
}

TEST(ArgParse, ErrorNotInOptionStringTest) {
  int argc = 2;
  const char **argv = (const char **)malloc(argc);
  argv[0] = (char *)"argparsetest";
  argv[1] = (char *)"-xyz";
  const char *ostr = (char *)"abc";

  AParse ap;
  argparse_init(&ap, argc, argv, ostr);
  ASSERT_EQ(argparse_next(&ap), -1);

  free(argv);
}
