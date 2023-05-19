#ifndef STANDARD_H_
#define STANDARD_H_

#include <stdio.h>
#define CARDS_STANDARD_NUM_SUITS 4U
#define CARDS_STANDARD_NUM_VALUES 13U
#define CARDS_STANDARD_NUM_FACE_CARDS 3U
#ifndef CARDS_STANDARD_ACE_LOW
#define CARDS_STANDARD_ACE_HIGH
#endif
#define CARDS_STANDARD_SUIT_WIDTH                                              \
        (CARDS_STANDARD_NUM_VALUES > 0x10u ? 0x20 : 0x10)

#define CARDS_STANDARD_DECK_SIZE                                               \
        (CARDS_STANDARD_NUM_SUITS == NO_SUITS                                  \
             ? CARDS_STANDARD_NUM_VALUES                                       \
             : CARDS_STANDARD_NUM_VALUES * CARDS_STANDARD_NUM_SUITS)

static const char *CARDS_STANDARD_SUIT_NAMES[CARDS_STANDARD_NUM_SUITS] = {
    "Clubs", "Diamonds", "Hearts", "Spades"};

static const char *CARDS_STANDARD_COURT_NAMES[CARDS_STANDARD_NUM_FACE_CARDS] = {
    "Jack", "Queen", "King"};

struct CARDS_STANDARD_card_s {
        int suit;
        int value;
};

struct CARDS_STANDARD_card_s
CARDS_STANDARD_card_struct(int card)
{
        struct CARDS_STANDARD_card_s card_s = {
            card / CARDS_STANDARD_SUIT_WIDTH, card % CARDS_STANDARD_SUIT_WIDTH};
        return card_s;
};

int
CARDS_STANDARD_struct_to_int(struct CARDS_STANDARD_card_s card)
{
        return card.suit * CARDS_STANDARD_SUIT_WIDTH + card.value;
}

#endif // STANDARD_H_
