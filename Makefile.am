SUBDIRS = src . recipes

ACLOCAL_AMFLAGS = -I m4

include Common.am


#library_includedir = $(includedir)/libMDSipTest
#library_include_HEADERS = config.h
#test_SOURCES = src/main.cpp
#bin_PROGRAMS = test
#test_LDADD = libMDSipTest.la


##PACKAGE_MAJOR=@PACKAGE_MAJOR@
##PACKAGE_MINOR=@PACKAGE_MINOR@

# fix !
LIBRARY_VERSION = 1:0:0

CONLIBS = \
          src/libccStickers.la \
          src/Core/libccStickersCore.la \
          src/Math/libccStickersMath.la \
          src/Graphic2D/libccStickersGraphic2D.la


lib_LTLIBRARIES = libccStickers.la
libccStickers_la_SOURCES = ${_uLib_SOURCES}
libccStickers_la_LDFLAGS = -version-info $(LIBRARY_VERSION)
# -release $(PACKAGE_VERSION)
libccStickers_la_LIBADD  = $(AM_LIBS_ALL) ${CONLIBS}


# pkgconfigdir   = $(libdir)/pkgconfig
# pkgconfig_DATA = libmutom-${PACKAGE_VERSION}.pc

