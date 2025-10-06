#ifndef RNG_H
#define RNG_H

#include <stdint.h>

/**
 * Linear Congruential Generator for deterministic randomness
 * Uses the same algorithm as ANSI C rand() for consistency
 */

/**
 * Seed the RNG with given value
 * @param seed - seed value
 */
void rng_seed(uint32_t seed);

/**
 * Generate next random number
 * @return next random uint32_t value
 */
uint32_t rng_next(void);

/**
 * Generate random choice from 0 to n-1
 * @param n - number of choices
 * @return random integer from 0 to n-1
 */
int rng_choice(int n);

/**
 * Generate random boolean
 * @return random boolean value
 */
bool rng_bool(void);

#endif // RNG_H
