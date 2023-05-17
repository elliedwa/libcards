#include "../src/deck.h"
#include "tap.h"
#include "test_deck_data.h"

int
main(void)
{
        plan(NO_PLAN);
        struct CARDS_deck_s *D =
            CARDS_deck_init(CARDS_test_deck, CARDS_test_deck_size);
        if (!D) {
                BAIL_OUT("Failed to create deck");
        }
        cmp_ok(CARDS_test_deck_size, "==", D->top,
               "new deck's top == deck size");
        cmp_ok(FOURTH, "==", CARDS_deck_peek(D),
               "top card of unshuffled test deck is FOURTH");
        cmp_ok(FOURTH, "==", CARDS_deck_pop(D), "pop FOURTH");
        cmp_ok(THIRD, "==", CARDS_deck_pop(D), "pop THIRD");
        cmp_ok(SECOND, "==", CARDS_deck_pop(D), "pop SECOND");
        cmp_ok(FIRST, "==", CARDS_deck_pop(D), "pop FIRST");
        cmp_ok(CARDS_DECK_EMPTY, "==", CARDS_deck_pop(D),
               "pop, but deck is empty");
        cmp_ok(CARDS_DECK_EMPTY, "==", CARDS_deck_peek(D),
               "peek, but deck is empty");
        done_testing();
}
