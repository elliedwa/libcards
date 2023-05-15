TEST_LOG_DRIVER = env AM_TAP_AWK='$(AWK)' $(SHELL) \
	$(top_srcdir)/build-aux/tap-driver.sh


check_LIBRARIES = libtap.a
libtap_a_SOURCES = tap.c tap.h

LDADD = $(top_builddir)/src/libcards.a libtap.a
AM_CPPFLAGS = -I$(top_srcdir)/src
check_PROGRAMS = test_deck

TESTS = $(check_PROGRAMS)
