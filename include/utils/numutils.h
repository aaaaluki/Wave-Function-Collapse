/**
 * @file numutils.h
 * @brief This file contains various utilites for numbers
 *
 */

#ifndef UTILS_NUMUTILS_H
#define UTILS_NUMUTILS_H

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

#endif // UTILS_NUMUTILS_H
