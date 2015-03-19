SUBDIRS = Core Math Graphic2D . testing

include $(top_srcdir)/Common.am

library_includedir = $(includedir)/ccStickers

library_include_HEADERS = \
 ClassUtils.h \
 SerializeUtils.h \
 DataUtils.h \
 FileUtils.h \
 ProducerConsumer.h \
 StatisticsUtils.h \
 Threads.h


_SOURCES = \
ClassUtils.cpp \
SerializeUtils.cpp \
DataUtils.cpp \
FileUtils.cpp \
ProducerConsumer.cpp \
StatisticsUtils.cpp

noinst_LTLIBRARIES = libccStickers.la
libccStickers_la_SOURCES = ${_SOURCES}

