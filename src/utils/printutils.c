#include "utils/printutils.h"

#include "utils/colorutils.h"

#include <stdio.h>
#include <stdlib.h>

void errmsg(const char *msg, int exitcode) {
  fprintf(stderr, COLOR_RED_BOLD_BRIGHT "[ERROR]" COLOR_RESET " %s\n", msg);
  exit(exitcode);
}
