SUBDIRS = . testing

include $(top_srcdir)/Common.am

library_includedir = $(includedir)/ccStickers/IO

library_include_HEADERS =


_SOURCES = \
           FileTreeIO.cpp \
           H5TreeIO.cpp

noinst_LTLIBRARIES = libccStickersIO.la
libccStickersIO_la_SOURCES = ${_SOURCES}



h5tutorial_1_SOURCES = h5_tutorial/h5tutorial_1.cc
h5tutorial_2_SOURCES = h5_tutorial/h5tutorial_2.cc


bin_PROGRAMS = h5tutorial_1 h5tutorial_2

h5tutorial_1: $(h5tutorial_1_SOURCES)
	h5c++ $^ -o $@

h5tutorial_2: $(h5tutorial_2_SOURCES)
	h5c++ $^ -o $@


