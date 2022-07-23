/**
 * @file stringutils.h
 * @brief This file contains various utilites for "strings"
 *
 */

#ifndef UTILS_STRINGUTILS_H
#define UTILS_STRINGUTILS_H

/* Error returns from 'strsplit'. */
#define STRINGUTILS_OK        0 /* No errors */
#define STRINGUTILS_NULLINPUT 1 /* Some input is null */
#define STRINGUTILS_NOSPACE   2 /* Ran out of memory */
#define STRINGUTILS_NOMATCH   3 /* No matches found */

/* Bits to set on the flags argument for strsplit() */
#define STRSPLIT_FIRST (1 << 0) /* Split on first match */
#define STRSPLIT_LAST  (1 << 1) /* Split on last match*/

/**
 * @brief Returns a pointer to the concatenation of s1 and s2
 *
 * Sauce: https://stackoverflow.com/a/8465083/13313449
 *
 * @param s1 string 1
 * @param s2 string 2
 * @param sp pointer to concatenated string
 * @return int Error code of the defined macros
 */
int strconcat(const char *s1, const char *s2, char **sp);

/**
 * @brief Splits the given string into two copies
 *
 * @param s String to split
 * @param spltchar Split character
 * @param splttype How to split (first or last char ocurrence)
 * @param lhs Left hand side of spliting result
 * @param rhs Right hand side of spliting result
 * @return int Error code of the defined macros
 */
int strsplit(const char *s, char spltchar, int splttype, char **lhs,
             char **rhs);

#endif // UTILS_STRINGUTILS_H
