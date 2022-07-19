/**
 * @file printutils.h
 * @brief Utilies for printing text
 * 
 */

#ifndef PRINTUTILS_H_
#define PRINTUTILS_H_

  /**
   * @brief Prints the message as an error and exits with exitcode
   * 
   * @param msg Message describing the error
   * @param exitcode Exit code value
   */
  void errmsg(const char* msg, int exitcode);

#endif // PRINTUTILS_H_
