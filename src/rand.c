#include "rand.h"
#include <limits.h>
#include <stdint.h>

#define CARDS_RAND_MAX UINT64_MAX

/* xoshiro256** by David Blackman and Sebastiano Vigna */

static inline uint64_t
rotl(const uint64_t x, int k)
{
        return (x << k) | (x >> (64 - k));
}

static uint64_t xoshiro_state[4];

uint64_t
xoshiro_next(void)
{
        const uint64_t result = rotl(xoshiro_state[1] * 5, 7) * 9;
        const uint64_t t = xoshiro_state[1] << 17;
        xoshiro_state[2] ^= xoshiro_state[0];
        xoshiro_state[3] ^= xoshiro_state[1];
        xoshiro_state[1] ^= xoshiro_state[2];
        xoshiro_state[0] ^= xoshiro_state[3];

        xoshiro_state[2] ^= t;

        xoshiro_state[3] = rotl(xoshiro_state[3], 45);

        return result;
}

/* SplitMix64 by Sebastiano Vigna */

static uint64_t splitmix_state;

uint64_t
splitmix_next(void)
{
        uint64_t z = (splitmix_state += 0x9e3779b97f4a7c15);
        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
        z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
        return z ^ (z >> 31);
}

uint64_t
CARDS_rand(void)
{
        return xoshiro_next();
}

uint64_t
CARDS_rand_range(uint64_t low, uint64_t high)
{
        return low + CARDS_rand() / (CARDS_RAND_MAX / (high - low + 1) + 1);
}

void
CARDS_srand(uint64_t seed)
{
        splitmix_state = seed;
        for (int i = 0; i < 4; i++) {
                xoshiro_state[i] = splitmix_next();
        }
}
