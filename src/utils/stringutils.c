#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "utils/printutils.h"
#include "utils/stringutils.h"

char *strconcat(const char *s1, const char *s2) {
  if (s1 == NULL || s2 == NULL) {
    return NULL;
  }

  const size_t len1 = strlen(s1);
  const size_t len2 = strlen(s2);
  char *result = malloc(len1 + len2 + 1);

  if (result == NULL) {
    return NULL;
  }

  memcpy(result, s1, len1);
  memcpy(result + len1, s2, len2 + 1);

  return result;
}