#include "deck.h"
#include "rand.h"
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

static struct CARDS_deck_s *
_CARDS_deck_init_no_suits(int num_values)
{
        const int n_cards = num_values;
        int *array = malloc(sizeof(int) * n_cards * 2);
        int top = 0;
        for (int value = 0; value < num_values; value++) {
                assert(top <= n_cards);
                array[top++] = value;
        }
        struct CARDS_deck_s *deck = malloc(sizeof(*array) + sizeof(top));
        if (!deck) {
                return NULL;
        }
        deck->top = top;
        deck->array = array;
        return deck;
}

struct CARDS_deck_s *
CARDS_deck_init(const int num_suits, const int num_values)
{
        CARDS_srand((uint64_t)time(NULL));

        if (num_suits == NO_SUITS) {
                return _CARDS_deck_init_no_suits(num_values);
        }
        const int n_cards = num_suits * num_values;
        int *array = malloc(sizeof(int) * n_cards * 2);
        if (!array) {
                return NULL;
        }
        int top = 0;
        for (int suit = 0; suit < num_suits; suit++) {
                for (int value = 0; value < num_values; value++) {
                        assert(top <= n_cards);
                        array[top++] = suit * 0x10 + value;
                }
        }
        struct CARDS_deck_s *deck = malloc(sizeof(*array) + sizeof(top));
        if (!deck) {
                return NULL;
        }
        deck->top = top;
        deck->array = array;
        return deck;
}

void
CARDS_deck_push(struct CARDS_deck_s *D, int card)
{
        D->array[D->top++] = card;
}

int
CARDS_deck_pop(struct CARDS_deck_s *D)
{
        if (CARDS_deck_isempty(D)) {
                return CARDS_DECK_EMPTY;
        }
        int popped = D->array[--D->top];
        return popped;
}

int
CARDS_deck_draw(struct CARDS_deck_s *D)
{
        return CARDS_deck_pop(D);
}

int
CARDS_deck_peek(struct CARDS_deck_s *D)
{
        if (CARDS_deck_isempty(D)) {
                return CARDS_DECK_EMPTY;
        }
        return D->array[D->top - 1];
}

bool
CARDS_deck_isempty(struct CARDS_deck_s *D)
{
        return D->top == 0;
}

void
CARDS_deck_shuffle(struct CARDS_deck_s *D)
{

        for (size_t i = D->top - 1; i >= 1; i--) {
                size_t j = CARDS_rand_range(0, i);
                /* using the top index as tmp storage */
                D->array[D->top] = D->array[j];
                D->array[j] = D->array[i];
                D->array[i] = D->array[D->top];
        }
}

void
CARDS_deck_destroy(struct CARDS_deck_s *D)
{
        free(D->array);
        free(D);
}
