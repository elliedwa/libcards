#ifndef TEST_H_
#define TEST_H_

#include <stdbool.h>
#include <stdlib.h>

void
assert(bool test)
{
        if (!test) {
                exit(1);
        }
}

void
ok_hard_error(bool test)
{
        if (!test) {
                exit(99);
        }
}

#endif // TEST_H_
