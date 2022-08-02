/**
 * @file argparse.h
 * @brief This argparser is going to be inspired in the one used in radare2
 *
 */

#ifndef ARGPARSE_ARGPARSE_H
#define ARGPARSE_ARGPARSE_H

typedef struct argparse_t {
  int idx;           /* current argv index */
  int opt;           /* current option */
  const char *arg;   /* current argument */
  int argc;          /* arg count */
  const char **argv; /* arg values */
  const char *ostr;  /* option string */
} AParse;

/**
 * @brief Initialize the arg parser
 *
 * @param ap pointer to parser
 * @param argc argc from main
 * @param argv argv from main
 * @param ostr option string
 */
void argparse_init(AParse *ap, int argc, const char **argv, const char *ostr);

/**
 * @brief
 *
 * @param ap pointer to parser
 * @return int parsed option
 */
int argparse_next(AParse *ap);

#endif // ARGPARSE_ARGPARSE_H
