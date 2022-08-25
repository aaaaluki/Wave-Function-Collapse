#include "utils/printutils.h"

#include "utils/colorutils.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define ERR_OUT stderr

void errmsg(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);

  fprintf(ERR_OUT, COLOR_RED_BOLD_BRIGHT "[ERROR]" COLOR_RESET " ");
  vfprintf(ERR_OUT, fmt, args);
  fprintf(ERR_OUT, "\n");

  va_end(args);
}
