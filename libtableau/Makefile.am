AM_CPPFLAGS = \
	-I../include -I$(top_srcdir)/include \
	-I../common -I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCTHREADS_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBTABLEAU_DLL_EXPORT@

lib_LTLIBRARIES = libtableau.la

libtableau_la_SOURCES = \
	libtableau.c \
	libtableau_definitions.h \
	libtableau_error.c libtableau_error.h \
	libtableau_extern.h \
	libtableau_handle.c libtableau_handle.h \
	libtableau_io.c libtableau_io.h \
	libtableau_libcerror.h \
	libtableau_libclocale.h \
	libtableau_libcnotify.h \
	libtableau_libuna.h \
	libtableau_notify.c libtableau_notify.h \
	libtableau_query.c libtableau_query.h \
	libtableau_security_values.c libtableau_security_values.h \
	libtableau_string.c libtableau_string.h \
	libtableau_support.c libtableau_support.h \
	libtableau_types.h \
	libtableau_values.c libtableau_values.h \
	libtableau_values_table.c libtableau_values_table.h \
	libtableau_unused.h \
	tableau_header.h \
	tableau_page.h \
	tableau_query.h

libtableau_la_LIBADD = \
	@LIBCERROR_LIBADD@ \
	@LIBCTHREADS_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@PTHREAD_LIBADD@

libtableau_la_LDFLAGS = -no-undefined -version-info 1:0:0

EXTRA_DIST = \
	libtableau_definitions.h.in \
	libtableau.rc \
	libtableau.rc.in

DISTCLEANFILES = \
	libtableau_definitions.h \
	libtableau.rc \
	Makefile \
	Makefile.in

sources-local: $(BUILT_SOURCES)

splint-local:
	@echo "Running splint on libtableau ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libtableau_la_SOURCES)

