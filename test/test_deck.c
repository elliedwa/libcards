#include "tap.h"
#include <cards/cards.h>
#include <cards/decks/standard.h>

#define CARDS_TEST_NUM_VALUES 4
#define CARDS_TEST_NUM_SUITS NO_SUITS
enum CARDS_test { FIRST, SECOND, THIRD, FOURTH };

int
main(void)
{
        plan(NO_PLAN);
        struct CARDS_deck_s *D_std = CARDS_deck_init(CARDS_STANDARD_NUM_SUITS,
                                                     CARDS_STANDARD_NUM_VALUES);
        if (!D_std) {
                BAIL_OUT("Failed to create deck");
        }
        cmp_ok(D_std->top,
               "==", CARDS_STANDARD_NUM_SUITS * CARDS_STANDARD_NUM_VALUES,
               "new deck's top == deck size");
        cmp_ok(CARDS_deck_peek(D_std), "==", 0x3c);

        struct CARDS_deck_s *D_test =
            CARDS_deck_init(CARDS_TEST_NUM_SUITS, CARDS_TEST_NUM_VALUES);

        cmp_ok(FOURTH, "==", CARDS_deck_peek(D_test),
               "top card of unshuffled test deck is FOURTH");
        cmp_ok(FOURTH, "==", CARDS_deck_pop(D_test), "pop FOURTH");
        cmp_ok(THIRD, "==", CARDS_deck_pop(D_test), "pop THIRD");
        cmp_ok(SECOND, "==", CARDS_deck_pop(D_test), "pop SECOND");
        cmp_ok(FIRST, "==", CARDS_deck_pop(D_test), "pop FIRST");
        cmp_ok(CARDS_DECK_EMPTY, "==", CARDS_deck_pop(D_test),
               "pop, but deck is empty");
        cmp_ok(CARDS_DECK_EMPTY, "==", CARDS_deck_peek(D_test),
               "peek, but deck is empty");
        done_testing();
}
