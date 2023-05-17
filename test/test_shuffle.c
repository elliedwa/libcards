#include "../src/cards.h"
#include "fff.h"
#include "tap.h"
#include "test_deck_data.h"
#include <stdint.h>
DEFINE_FFF_GLOBALS
FAKE_VALUE_FUNC(uint64_t, CARDS_rand);
FAKE_VOID_FUNC(CARDS_srand, uint64_t);
FAKE_VALUE_FUNC(uint64_t, CARDS_rand_range, uint64_t, uint64_t);

void
reset_fakes(void)
{
        RESET_FAKE(CARDS_rand);
        RESET_FAKE(CARDS_rand_range);
        RESET_FAKE(CARDS_srand);
}

int
main(void)
{
        reset_fakes();
        plan(NO_PLAN);
        struct CARDS_deck_s *F =
            CARDS_deck_init(CARDS_standard_deck, CARDS_standard_deck_size);
        CARDS_deck_shuffle(F);
        cmp_ok(F->top, "==", CARDS_standard_deck_size,
               "shuffle doesn't change the deck size (standard_deck)");
        cmp_ok(F->top - 1, "==", CARDS_rand_range_fake.call_count,
               "shuffle asks for random value the correct number of times "
               "(standard_deck)");
        CARDS_deck_destroy(F);

        reset_fakes();
        struct CARDS_deck_s *D =
            CARDS_deck_init(CARDS_test_deck, CARDS_test_deck_size);
        uint64_t return_vals_threes[3] = {3, 3, 3};

        SET_RETURN_SEQ(CARDS_rand_range, return_vals_threes, 3);
        CARDS_deck_shuffle(D);
        cmp_ok(D->top, "==", CARDS_test_deck_size,
               "shuffle doesn't change the deck size (test_deck)");
        cmp_ok(D->top - 1, "==", CARDS_rand_range_fake.call_count,
               "shuffle asks for random value the correct number of times "
               "(test_deck)");
        int D_expected[4] = {FIRST, THIRD, FOURTH, SECOND};
        cmp_mem(D->array, D_expected, sizeof(D->array[0]) * 4);
        CARDS_deck_destroy(D);

        reset_fakes();
        struct CARDS_deck_s *L =
            CARDS_deck_init(CARDS_test_deck, CARDS_test_deck_size);
        uint64_t return_vals_flip[3] = {0, 1, 1};
        SET_RETURN_SEQ(CARDS_rand_range, return_vals_flip, 3);
        CARDS_deck_shuffle(L);
        int L_expected[4] = {FOURTH, THIRD, SECOND, FIRST};
        cmp_mem(L->array, L_expected, sizeof(L->array[0]) * 4);
        CARDS_deck_destroy(L);
        done_testing();
}
