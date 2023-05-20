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
#include "deck.h"
#include <cards/cards.h>
#include <cards/rand.h>
/* #define NDEBUG */
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static struct CARDS_deck_s *
CARDS_deck_init_no_suits(int num_values)
{
        const int n_cards = num_values;
        const int suit_width = 0;
        int *array = malloc(sizeof(int) * n_cards * 2);
        int top = 0;
        for (int value = 0; value < num_values; value++) {
                assert(top <= n_cards);
                array[top++] = value;
        }
        struct CARDS_deck_s deck = {suit_width, top, array};
        struct CARDS_deck_s *deckptr = malloc(sizeof deck);
        if (!deckptr) {
                return NULL;
        }
        memcpy(deckptr, &deck, sizeof deck);
        return deckptr;
}

struct CARDS_deck_s *
CARDS_deck_init(const int num_suits, const int num_values)
{
        CARDS_srand((uint64_t)time(NULL));

        if (num_suits == NO_SUITS) {
                return CARDS_deck_init_no_suits(num_values);
        }
        const int suit_width = num_values > 0x10 ? 0x20 : 0x10;

        const unsigned int n_cards = num_suits * num_values;
        int *array = malloc(sizeof(int) * n_cards * 2);
        if (!array) {
                return NULL;
        }
        size_t top = 0;
        for (int suit = 0; suit < num_suits; suit++) {
                for (int value = 0; value < num_values; value++) {
                        assert(top <= n_cards);
                        array[top++] = suit * suit_width + value;
                }
        }
        struct CARDS_deck_s deck = {suit_width, top, array};
        struct CARDS_deck_s *deckptr = malloc(sizeof deck);
        if (!deckptr) {
                return NULL;
        }
        memcpy(deckptr, &deck, sizeof deck);
        return deckptr;
}

void
CARDS_deck_push(struct CARDS_deck_s *deck, int card)
{
        deck->array[deck->top++] = card;
}

int
CARDS_deck_pop(struct CARDS_deck_s *deck)
{
        if (CARDS_deck_isempty(deck)) {
                return CARDS_DECK_EMPTY;
        }
        int popped = deck->array[--deck->top];
        return popped;
}

int
CARDS_deck_draw(struct CARDS_deck_s *deck)
{
        return CARDS_deck_pop(deck);
}

int
CARDS_deck_peek(struct CARDS_deck_s *deck)
{
        if (CARDS_deck_isempty(deck)) {
                return CARDS_DECK_EMPTY;
        }
        return deck->array[deck->top - 1];
}

bool
CARDS_deck_isempty(struct CARDS_deck_s *deck)
{
        return deck->top == 0;
}

void
CARDS_deck_shuffle(struct CARDS_deck_s *deck)
{

        for (size_t i = deck->top - 1; i >= 1; i--) {
                size_t j = CARDS_rand_range(0, i);
                /* using the top index as tmp storage */
                deck->array[deck->top] = deck->array[j];
                deck->array[j] = deck->array[i];
                deck->array[i] = deck->array[deck->top];
        }
}

void
CARDS_deck_destroy(struct CARDS_deck_s *deck)
{
        free(deck->array);
        free(deck);
}
