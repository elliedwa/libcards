ACLOCAL_AMFLAGS = -I m4
AM_CPPFLAGS = -I$(top_srcdir)/include

noinst_LIBRARIES = lib/libcards.a
lib_libcards_a_SOURCES = src/deck.c src/deck.h src/rand.c src/rand.h
nobase_include_HEADERS = include/cards/cards.h include/cards/decks/standard.h

TEST_LOG_DRIVER = env AM_TAP_AWK='$(AWK)' $(SHELL) \
	$(top_srcdir)/build-aux/tap-driver.sh


TEST_COMMON = test/tap.h test/tap.c test/fff.h
CARDS = src/deck.c src/deck.h
RAND = src/rand.c src/rand.h


check_PROGRAMS = test/cards.test test/rand.test test/shuffle.test
test_cards_test_SOURCES = test/test_deck.c $(CARDS) $(RAND) $(TEST_COMMON)
test_rand_test_SOURCES = test/test_rand.c $(CARDS) $(RAND) $(TEST_COMMON)

# rand is fake in test_shuffle
test_shuffle_test_SOURCES = test/test_shuffle.c $(CARDS) $(TEST_COMMON)


TESTS = $(check_PROGRAMS)

dist_doc_DATA = README
