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
 ProxyInterfaceExample


# else
# TEST =
# endif

LDADD  = ${top_builddir}/src/Core/libccStickersCore.la
LDADD += ${top_builddir}/src/Math/libccStickersMath.la
LDADD += ${top_builddir}/src/Graphic2D/libccStickersGraphic2D.la
LDADD += ${top_builddir}/src/libccStickers.la


check_PROGRAMS = $(TESTS)


all: $(TESTS)

