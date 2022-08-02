#include "argparse/argparse.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void argparse_init(AParse *ap, int argc, const char **argv, const char *ostr) {
  ap = memset(ap, 0, sizeof(AParse));

  ap->idx = 1;
  ap->opt = 0;
  ap->arg = NULL;
  ap->argc = argc;
  ap->argv = argv;
  ap->ostr = ostr;
}

int argparse_next(AParse *ap) {
  static const char *argptr = "";
  char *ostrptr;

  if (!*argptr) {
    if (ap->idx >= ap->argc) {
      /* consumed all arguments */
      return -1;
    }

    if (*(argptr = ap->argv[ap->idx]) != '-') {
      /* option does not start with - */
      return -1;
    }

    if (argptr[1] && *++argptr == '-') {
      /* -- given */
      ap->idx++;
      argptr = "";
      return -1;
    }
  }

  if (!(ostrptr = strchr(ap->ostr, *argptr))) { /* option not in ostr */
    fprintf(stderr, "%s -- does not have option -%c\n", ap->argv[0], *argptr);
    return -1;
  }

  ap->opt = *argptr++;
  if (*++ostrptr == ':') { /* opt needs an argument */
    if (*argptr) {         /* arg follows option without space */
      ap->arg = argptr;

    } else if (++ap->idx >= ap->argc) { /* no arg given */
      fprintf(stderr, "%s -- option -%c needs an argument\n", ap->argv[0],
              ap->opt);
      return -1;

    } else { /* arg follows option with space */
      ap->arg = ap->argv[ap->idx];
    }

    argptr = "";
    ap->idx++;
  } else { /* no arg needed */
    ap->arg = NULL;
    if (!*argptr) {
      ap->idx++;
    }
  }

  return ap->opt;
}
