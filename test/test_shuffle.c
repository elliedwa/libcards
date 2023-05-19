#include "../src/deck.h"
#include "../src/decks/standard.h"
#include "fff.h"
#include "tap.h"
#include <stdint.h>
DEFINE_FFF_GLOBALS
FAKE_VALUE_FUNC(uint64_t, CARDS_rand);
FAKE_VOID_FUNC(CARDS_srand, uint64_t);
FAKE_VALUE_FUNC(uint64_t, CARDS_rand_range, uint64_t, uint64_t);

#define CARDS_TEST_NUM_VALUES 4
#define CARDS_TEST_NUM_SUITS NO_SUITS
#define CARDS_TEST_DECK_SIZE                                                   \
        (CARDS_TEST_NUM_SUITS == NO_SUITS                                      \
             ? CARDS_TEST_NUM_VALUES                                           \
             : CARDS_TEST_NUM_VALUES * CARDS_TEST_NUM_SUITS)
enum CARDS_test { FIRST, SECOND, THIRD, FOURTH };

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
        struct CARDS_deck_s *D_std = CARDS_deck_init(CARDS_STANDARD_NUM_SUITS,
                                                     CARDS_STANDARD_NUM_VALUES);
        CARDS_deck_shuffle(D_std);
        cmp_ok(D_std->top, "==", CARDS_STANDARD_DECK_SIZE,
               "shuffle doesn't change the deck size (standard_deck)");
        cmp_ok(D_std->top - 1, "==", CARDS_rand_range_fake.call_count,
               "shuffle asks for random value the correct number of times "
               "(standard_deck)");
        CARDS_deck_destroy(D_std);

        reset_fakes();
        struct CARDS_deck_s *D =
            CARDS_deck_init(CARDS_TEST_NUM_SUITS, CARDS_TEST_NUM_VALUES);

        uint64_t return_vals_threes[3] = {3, 3, 3};

        SET_RETURN_SEQ(CARDS_rand_range, return_vals_threes, 3);
        CARDS_deck_shuffle(D);
        cmp_ok(D->top, "==", CARDS_TEST_DECK_SIZE,
               "shuffle doesn't change the deck size (test_deck)");
        cmp_ok(D->top - 1, "==", CARDS_rand_range_fake.call_count,
               "shuffle asks for random value the correct number of times "
               "(test_deck)");
        int D_expected[4] = {FIRST, THIRD, FOURTH, SECOND};
        cmp_mem(D->array, D_expected, sizeof(D->array[0]) * 4);
        CARDS_deck_destroy(D);

        reset_fakes();
        struct CARDS_deck_s *L =
            CARDS_deck_init(CARDS_TEST_NUM_SUITS, CARDS_TEST_NUM_VALUES);
        uint64_t return_vals_flip[3] = {0, 1, 1};
        SET_RETURN_SEQ(CARDS_rand_range, return_vals_flip, 3);
        CARDS_deck_shuffle(L);
        int L_expected[4] = {FOURTH, THIRD, SECOND, FIRST};
        cmp_mem(L->array, L_expected, sizeof(L->array[0]) * 4);
        CARDS_deck_destroy(L);
        done_testing();
}
