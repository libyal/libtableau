AM_CPPFLAGS = \
	-I../include -I$(top_srcdir)/include \
	-I../common -I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBTABLEAU_DLL_IMPORT@

AM_LDFLAGS = @STATIC_LDFLAGS@

bin_PROGRAMS = \
	tableaucontrol \
	tableauinfo

tableaucontrol_SOURCES = \
	tableaucontrol.c \
	tableautools_getopt.c tableautools_getopt.h \
	tableautools_i18n.h \
	tableautools_input.c tableautools_input.h \
	tableautools_libcerror.h \
	tableautools_libclocale.h \
	tableautools_libcnotify.h \
	tableautools_libtableau.h \
	tableautools_output.c tableautools_output.h \
	tableautools_unused.h

tableaucontrol_LDADD = \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	../libtableau/libtableau.la \
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

tableauinfo_SOURCES = \
	info_handle.c info_handle.h \
	tableauinfo.c \
	tableautools_getopt.c tableautools_getopt.h \
	tableautools_i18n.h \
	tableautools_libcerror.h \
	tableautools_libclocale.h \
	tableautools_libcnotify.h \
	tableautools_libtableau.h \
	tableautools_output.c tableautools_output.h \
	tableautools_signal.c tableautools_signal.h \
	tableautools_unused.h

tableauinfo_LDADD = \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	../libtableau/libtableau.la \
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

DISTCLEANFILES = \
	Makefile \
	Makefile.in

splint-local:
	@echo "Running splint on tableauinfo ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(tableauinfo_SOURCES)

