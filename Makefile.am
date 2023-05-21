# Copyright 2023 Elliot C. Edwards

# This file is part of libcards.

# libcards is free software: you can redistribute it and/or modify it under the
# terms of the GNU General Public License as published by the Free Software
# Foundation, either version 3 of the License, or (at your option) any later
# version.

# libcards is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE. See the GNU General Public License for more details.

# You should have received a copy of the GNU General Public License along with
# libcards. If not, see <https://www.gnu.org/licenses/>.


ACLOCAL_AMFLAGS = -I m4
AM_CPPFLAGS = -I$(top_srcdir)/include
AM_CFLAGS = -Wall -Wextra -Wpedantic -std=c99

lib_LTLIBRARIES = lib/libcards.la
lib_libcards_la_SOURCES = src/deck.c src/deck.h src/rand.c src/rand_p.h
nobase_include_HEADERS = include/cards/cards.h include/cards/decks/standard.h \
	include/cards/rand.h

TEST_LOG_DRIVER = env AM_TAP_AWK='$(AWK)' $(SHELL) \
	$(top_srcdir)/build-aux/tap-driver.sh


TEST_COMMON = test/tap.h test/tap.c test/fff.h
DECK = src/deck.c src/deck.h
RAND = src/rand.c


check_PROGRAMS = test/cards.test test/rand.test test/shuffle.test
test_cards_test_SOURCES = test/test_deck.c $(DECK) $(RAND) $(TEST_COMMON)
# unit tests can't link against the library, but automake won't let us use object files with
# the same basename as the ones compiled by libtool. the automake manual suggests this
# workaround.
test_cards_test_CFLAGS = $(AM_CFLAGS)
test_rand_test_SOURCES = test/test_rand.c $(DECK) $(RAND) $(TEST_COMMON)
test_rand_test_CFLAGS = $(AM_CFLAGS)

# rand is fake in test_shuffle
test_shuffle_test_SOURCES = test/test_shuffle.c $(DECK) $(TEST_COMMON)
test_shuffle_test_CFLAGS = $(AM_CFLAGS)


TESTS = $(check_PROGRAMS)

dist_doc_DATA = README
