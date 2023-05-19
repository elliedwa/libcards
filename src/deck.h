#ifndef CARDS_H_
#define CARDS_H_

#include <stdbool.h>
#include <stddef.h>

#define CARDS_DECK_EMPTY (-1)
#define NO_SUITS (-1)

/* this is a stack for now but should ultimately be a deque */
struct CARDS_deck_s {
        const int suit_width;
        size_t top;
        int *array;
};

struct CARDS_deck_s *CARDS_deck_init(int num_suits, int num_values);
void CARDS_deck_destroy(struct CARDS_deck_s *D);
void CARDS_deck_push(struct CARDS_deck_s *D, int card);
int CARDS_deck_pop(struct CARDS_deck_s *D);
/* alias for CARDS_deck_pop */
int CARDS_deck_draw(struct CARDS_deck_s *D);
int CARDS_deck_peek(struct CARDS_deck_s *D);
bool CARDS_deck_isempty(struct CARDS_deck_s *D);

/* shuffles deck in place */
void CARDS_deck_shuffle(struct CARDS_deck_s *D);

#endif // CARDS_H_
