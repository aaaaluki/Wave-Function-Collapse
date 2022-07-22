/**
 * @file stringutils.h
 * @brief This file contains various utilites for "strings"
 *
 */

#ifndef STRINGUTILS_H_
#define STRINGUTILS_H_

/* Bits to set on the flags argument */
#define STRSPLIT_FIRST (1 << 0) /* Split on first match */
#define STRSPLIT_LAST  (1 << 1) /* Split on last match*/

/* Error returns from 'strsplit'. */
#define STRSPLIT_OK        0 /* No errors */
#define STRSPLIT_NULLINPUT 1 /* Some input is null */
#define STRSPLIT_NOSPACE   2 /* Ran out of memory */
#define STRSPLIT_NOMATCH   3 /* No matches found */

// TODO: do the same as strsplit(), result as input and return error code
/**
 * @brief Returns a pointer to the concatenation of s1 and s2
 *
 * Sauce: https://stackoverflow.com/a/8465083/13313449
 *
 * @param s1 pointer to string 1
 * @param s2 pointer to string 2
 * @return char *
 */
char *strconcat(const char *s1, const char *s2);

/**
 * @brief Splits the given string into two copies
 *
 * @param s String to split
 * @param spltchar Split character
 * @param splttype How to split (first or last char ocurrence)
 * @param lhs Left hand side of spliting (Should be NULL)
 * @param rhs Right hand side of spliting (Should be NULL)
 * @return int Error code of the defined macros
 */
int strsplit(const char *s, char spltchar, int splttype, char **lhs,
             char **rhs);

#endif // STRINGUTILS_H_
