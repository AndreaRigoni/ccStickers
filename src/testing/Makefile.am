include $(top_srcdir)/Common.am

#AM_DEFAULT_SOURCE_EXT = .cpp

# if HAVE_CHECK
TESTS = \
 BuildTest \
 SerializeToBinTest \
 SerializeToShmTest \
 ContentProducerTest \
 ClassUtilsTest \
 DataUtilsTest \
 StatisticsUtilsTest \
 OptionsTest


# UuidTest

# else
# TEST =
# endif

LDADD = ../libccStickers.la

check_PROGRAMS = $(TESTS)


all: $(TESTS)

