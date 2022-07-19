/**
 * @file numutils.h
 * @brief This file contains various utilites for numbers
 * 
 */

#ifndef NUMUTILS_H_
#define NUMUTILS_H_

#include <stdint.h>
      
  /**
   * @brief Returns the next power of 2
   * 
   * Sauce: http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2
   * 
   * @param v 
   * @return uint32_t 
   */
  uint32_t next_pow2(uint32_t v);

#endif // NUMUTILS_H_