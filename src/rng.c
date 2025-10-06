#include "rng.h"
#include <stdbool.h>
#include <stdint.h>

// Global RNG state
static uint32_t rng_state = 1;

void rng_seed(uint32_t seed) {
    rng_state = seed;
}

uint32_t rng_next(void) {
    // Linear Congruential Generator: X(n+1) = (a * X(n) + c) mod m
    // Using ANSI C standard values: a=1103515245, c=12345, m=2^31
    rng_state = (1103515245UL * rng_state + 12345UL) & 0x7FFFFFFF;
    return rng_state;
}

int rng_choice(int n) {
    if (n <= 0) return 0;
    return (int)(rng_next() % (uint32_t)n);
}

bool rng_bool(void) {
    return (rng_next() & 1) != 0;
}
