/**
 * @file printutils.h
 * @brief Utilies for printing text
 *
 */

#ifndef UTILS_PRINTUTILS_H
#define UTILS_PRINTUTILS_H

/**
 * @brief Prints the message as an error and exits with exitcode
 *
 * @param exitcode Exit code value
 * @param fmt Message describing the error
 * @param ... varadic args for fmt format
 */
void errmsg(int exitcode, const char *fmt, ...);

#endif // UTILS_PRINTUTILS_H
