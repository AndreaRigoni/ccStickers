include $(top_srcdir)/Common.am

#AM_DEFAULT_SOURCE_EXT = .cpp

# if HAVE_CHECK
TESTS = \
        CoreTest \
        OptionsTest


# UuidTest

# else
# TEST =
# endif

LDADD = ../libccStickersCore.la

check_PROGRAMS = $(TESTS)


all: $(TESTS)

