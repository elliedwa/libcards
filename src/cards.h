#ifndef CARDS_H_
#define CARDS_H_

#include <stdbool.h>
#include <stddef.h>

#define CARDS_standard_deck_size 52

enum CARDS_standard_suits {
        SPADES = 0,
        HEARTS = 0x10,
        DIAMONDS = 0x20,
        CLUBS = 0x30
};

enum CARDS_standard_values {
        KING,
        QUEEN,
        JACK,
        TEN,
        NINE,
        EIGHT,
        SEVEN,
        SIX,
        FIVE,
        FOUR,
        THREE,
        TWO,
        ACE
};

enum CARDS_standard {
        SK = SPADES,
        SQ,
        SJ,
        S10,
        S9,
        S8,
        S7,
        S6,
        S5,
        S4,
        S3,
        S2,
        SA,

        /* hearts */
        HK = HEARTS,
        HQ,
        HJ,
        H10,
        H9,
        H8,
        H7,
        H6,
        H5,
        H4,
        H3,
        H2,
        HA,

        /* diamonds */
        DK = DIAMONDS,
        DQ,
        DJ,
        D10,
        D9,
        D8,
        D7,
        D6,
        D5,
        D4,
        D3,
        D2,
        DA,

        /* clubs */
        CK = CLUBS,
        CQ,
        CJ,
        C10,
        C9,
        C8,
        C7,
        C6,
        C5,
        C4,
        C3,
        C2,
        CA,

};

static const enum CARDS_standard CARDS_standard_deck[CARDS_standard_deck_size] =
    {
        /* spades */
        SK,
        SQ,
        SJ,
        S10,
        S9,
        S8,
        S7,
        S6,
        S5,
        S4,
        S3,
        S2,
        SA,

        /* hearts */
        HK,
        HQ,
        HJ,
        H10,
        H9,
        H8,
        H7,
        H6,
        H5,
        H4,
        H3,
        H2,
        HA,

        /* diamonds */
        DK,
        DQ,
        DJ,
        D10,
        D9,
        D8,
        D7,
        D6,
        D5,
        D4,
        D3,
        D2,
        DA,

        /* clubs */
        CK,
        CQ,
        CJ,
        C10,
        C9,
        C8,
        C7,
        C6,
        C5,
        C4,
        C3,
        C2,
        CA,
};

/* this is a stack for now but should ultimately be a deque */
struct CARDS_deck_s {
        size_t top;
        int *array;
};

struct CARDS_deck_s *CARDS_deck_init(const void *decklist, size_t n_cards);
void CARDS_deck_destroy(struct CARDS_deck_s *D);
void CARDS_deck_push(struct CARDS_deck_s *D, int card);
int CARDS_deck_pop(struct CARDS_deck_s *D);
/* alias for CARDS_deck_pop */
int CARDS_deck_draw(struct CARDS_deck_s *D);
int CARDS_deck_peek(struct CARDS_deck_s *D);
bool CARDS_deck_isempty(struct CARDS_deck_s *D);

#endif // CARDS_H_
