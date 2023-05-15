#include "test.h"
#include <cards.h>
#include <stdbool.h>
#include <stdlib.h>

int
main(void)
{
        struct CARDS_deck_s *D =
            CARDS_deck_init(CARDS_standard_deck, CARDS_standard_deck_size);
        ok_hard_error(D);

        CARDS_deck_destroy(D);
        return 0;
}
