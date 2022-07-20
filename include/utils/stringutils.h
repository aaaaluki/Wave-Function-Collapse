/**
 * @file stringutils.h
 * @brief This file contains various utilites for numbers
 *
 */

#ifndef STRINGUTILS_H_
#define STRINGUTILS_H_

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

#endif // STRINGUTILS_H_