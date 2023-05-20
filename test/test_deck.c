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
