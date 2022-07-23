#include "utils/stringutils.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

int strconcat(const char *s1, const char *s2, char **sp) {
  if (s1 == NULL || s2 == NULL || sp == NULL) {
    return STRINGUTILS_NULLINPUT;
  }

  const size_t len1 = strlen(s1);
  const size_t len2 = strlen(s2);
  *sp = malloc(len1 + len2 + 1);

  if (*sp == NULL) {
    return STRINGUTILS_NOSPACE;
  }

  memcpy(*sp, s1, len1);
  memcpy(*sp + len1, s2, len2 + 1);

  return STRINGUTILS_OK;
}

int strsplit(const char *s, char spltchar, int splttype, char **lhs,
             char **rhs) {
  if (s == NULL || lhs == NULL || rhs == NULL) {
    return STRINGUTILS_NULLINPUT;
  }

  unsigned long len = strlen(s);
  unsigned long idx = 0;
  bool found = false;

  for (unsigned long i = 0; i < len; i++) {
    if (s[i] == spltchar) {
      found = true;
      idx = i;

      if ((splttype & STRSPLIT_FIRST) == STRSPLIT_FIRST) {
        break;
      }
    }
  }

  if (!found) {
    return STRINGUTILS_NOMATCH;
  }

  // +1 for null terminated string
  *lhs = malloc(idx + 1);

  // No need to add 1, since the split char is not included
  *rhs = malloc(len - idx);

  if (*lhs == NULL || *rhs == NULL) {
    free(*lhs);
    free(*rhs);

    return STRINGUTILS_NOSPACE;
  }

  // Copy slices
  memcpy(*lhs, s, idx);
  memcpy(*rhs, s + sizeof(char) * (idx + 1), len - idx - 1);

  // Set last char to null, since they are null terminated strings
  (*lhs)[idx] = '\0';
  (*rhs)[len - idx - 1] = '\0';

  return STRINGUTILS_OK;
}
