#ifndef RAND_H_
#define RAND_H_

#include <stdint.h>

uint64_t CARDS_rand(void);

// inclusive
uint64_t CARDS_rand_range(uint64_t low, uint64_t high);

void CARDS_srand(uint64_t seed);

#endif // RAND_H_
