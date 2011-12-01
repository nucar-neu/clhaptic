SUBDIRS =\
	libanalysis-devices \
	libprofiler \
	librules \
	libmisc \
	libtopology

lib_LIBRARIES = libhaptic.a

#libhaptic_a_LDFLAGS = -c

libhaptic_a_LIBADD = \
	$(top_builddir)/src/libanalysis-devices/*.o \
	$(top_builddir)/src/libprofiler/*.o \
	$(top_builddir)/src/libmisc/*.o \
	$(top_builddir)/src/librules/*.o \
	$(top_builddir)/src/libtopology/*.o

libhaptic_a_SOURCES = \
	$(top_builddir)/src/libanalysis-devices/*.o \
	$(top_builddir)/src/libprofiler/*.o \
	$(top_builddir)/src/libmisc/*.o \
	$(top_builddir)/src/librules/*.o \
	$(top_builddir)/src/libtopology/*.o
