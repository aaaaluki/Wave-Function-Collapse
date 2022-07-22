#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

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

int strsplit(const char *s, char spltchar, int splttype, char **lhs,
             char **rhs) {
  if (s == NULL || lhs == NULL || rhs == NULL) {
    return STRSPLIT_NULLINPUT;
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
    return STRSPLIT_NOMATCH;
  }

  // +1 for null terminated string
  *lhs = calloc(idx + 1, sizeof(char));

  // No need to add 1, since the split char is not included
  *rhs = calloc(len - idx, sizeof(char));

  if (*lhs == NULL || *rhs == NULL) {
    free(*lhs);
    free(*rhs);

    return STRSPLIT_NOSPACE;
  }

  memcpy(*lhs, s, idx);
  memcpy(*rhs, s + sizeof(char) * (idx + 1), len - idx - 1);

  return STRSPLIT_OK;
}
