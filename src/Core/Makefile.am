SUBDIRS = . testing

include $(top_srcdir)/Common.am

library_includedir = $(includedir)/ccStickers/Core

library_include_HEADERS = \
           Options.h



_SOURCES = \
           Options.cpp \
           SerializeToBin.cpp \
           FileUtils.cpp


noinst_LTLIBRARIES = libccStickersCore.la
libccStickersCore_la_SOURCES = ${_SOURCES}

