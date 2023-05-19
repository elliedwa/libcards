#include "tap.h"
#include <assert.h>
#include <cards/rand.h>
#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#define NUM_SAMPLES 0x1000000
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
