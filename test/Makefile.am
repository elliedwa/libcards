TEST_LOG_DRIVER = env AM_TAP_AWK='$(AWK)' $(SHELL) \
	$(top_srcdir)/build-aux/tap-driver.sh


check_LIBRARIES = libtap.a
libtap_a_SOURCES = tap.c tap.h

CARDS = $(top_srcdir)/src/deck.c $(top_srcdir)/src/deck.h
RAND = $(top_srcdir)/src/rand.c $(top_srcdir)/src/rand.h


LDADD = libtap.a
AM_CPPFLAGS = -I$(top_srcdir)/src
check_PROGRAMS = cards.test rand.test shuffle.test
cards_test_SOURCES = test_deck.c $(CARDS) $(RAND)
rand_test_SOURCES = test_rand.c $(CARDS) $(RAND)
# rand is fake in test_shuffle
shuffle_test_SOURCES = test_shuffle.c $(CARDS)


TESTS = $(check_PROGRAMS)
