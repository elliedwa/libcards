/*
Copyright 2023 Elliot C. Edwards

This file is part of libcards.

libcards is free software: you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.

libcards is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
libcards. If not, see <https://www.gnu.org/licenses/>.
*/

#include "tap.h"
#include <assert.h>
#include <cards/rand.h>
#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#define NUM_SAMPLES 0x30000000
#define NUM_CARDS 52

double
chi_squared_uniform(const long dist[NUM_CARDS], long expected)
{
        assert(expected != 0);
        double chi_2 = 0.;
        double actual;
        for (unsigned long i = 0; i < NUM_CARDS; i++) {
                double diff = (double)(dist[i] - expected);
                actual = (pow(diff, 2)) / (double)expected;
                assert(actual <= 100.);
                chi_2 += actual;
        }
        return chi_2;
}

int
main(void)
{
        CARDS_srand((uint64_t)time(NULL));
        clock_t start_clock = clock();
        long dist[NUM_CARDS] = {0};
        uint64_t current;
        plan(3);
        /* plan(SKIP_ALL); */
        for (long i = 0; i < NUM_SAMPLES; i++) {
                current = CARDS_rand_range(0, NUM_CARDS - 1);
                if (current >= NUM_CARDS) {
                        fail("CARDS_rand_range(0,%d) returned %d after "
                             "%d "
                             "samples",
                             NUM_CARDS - 1, current, i);
                        break;
                }
                dist[current]++;
        }
        clock_t end_clock = clock();
        pass("CARDS_rand_range returned within the range %lld times in %d "
             "seconds!",
             NUM_SAMPLES, (end_clock - start_clock) / CLOCKS_PER_SEC);

        const double crit_val_high = 68.669;
        const double crit_val_low = 35.6;
        double chi_squared = chi_squared_uniform(dist, NUM_SAMPLES / NUM_CARDS);
        ok(isless(chi_squared, crit_val_high),
           "chi-squared result = %f is less than %f", chi_squared,
           crit_val_high);
        ok(isgreater(chi_squared, crit_val_low), "and greater than %f",
           crit_val_low);
        done_testing();
}
