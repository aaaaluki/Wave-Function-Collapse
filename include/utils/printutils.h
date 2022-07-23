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
 * @param msg Message describing the error
 * @param exitcode Exit code value
 */
void errmsg(const char *msg, int exitcode);

#endif // UTILS_PRINTUTILS_H
