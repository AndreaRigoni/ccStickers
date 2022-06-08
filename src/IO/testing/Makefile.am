include $(top_srcdir)/Common.am

#AM_DEFAULT_SOURCE_EXT = .cpp

# if HAVE_CHECK
TESTS = \
        FileTreeIOTest \
        H5TreeIOTest 



LDADD = ../libccStickersIO.la


## NEEDED FOR H5 ##
AM_CPPFLAGS = 	-D_FORTIFY_SOURCE=2 -DOLD_HEADER_FILENAME -DHDF_NO_NAMESPACE -DNO_STATIC_CAST \
				-O2 -pipe -fno-plt

AM_LDFLAGS += -L/usr/lib -lhdf5_hl_cpp -lhdf5_cpp -lhdf5_hl -lhdf5 \
          -Wl,-O1,--sort-common,--as-needed,-z,relro,-z,now \
		  -lsz -lz -ldl -lm -Wl,-rpath -Wl,/usr/lib		

check_PROGRAMS = $(TESTS)


all: $(TESTS)

