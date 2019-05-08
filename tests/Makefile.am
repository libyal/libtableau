AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCTHREADS_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBTABLEAU_DLL_IMPORT@

TESTS = \
	test_library.sh

check_SCRIPTS = \
	test_library.sh \
	test_manpage.sh \
	test_runner.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	tableau_test_error \
	tableau_test_handle \
	tableau_test_notify \
	tableau_test_security_values \
	tableau_test_support \
	tableau_test_values_table

tableau_test_error_SOURCES = \
	tableau_test_error.c \
	tableau_test_libtableau.h \
	tableau_test_macros.h \
	tableau_test_unused.h

tableau_test_error_LDADD = \
	../libtableau/libtableau.la

tableau_test_handle_SOURCES = \
	tableau_test_functions.c tableau_test_functions.h \
	tableau_test_getopt.c tableau_test_getopt.h \
	tableau_test_handle.c \
	tableau_test_libcerror.h \
	tableau_test_libclocale.h \
	tableau_test_libcnotify.h \
	tableau_test_libtableau.h \
	tableau_test_libuna.h \
	tableau_test_macros.h \
	tableau_test_memory.c tableau_test_memory.h \
	tableau_test_unused.h

tableau_test_handle_LDADD = \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	../libtableau/libtableau.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@PTHREAD_LIBADD@

tableau_test_notify_SOURCES = \
	tableau_test_libcerror.h \
	tableau_test_libtableau.h \
	tableau_test_macros.h \
	tableau_test_notify.c \
	tableau_test_unused.h

tableau_test_notify_LDADD = \
	../libtableau/libtableau.la \
	@LIBCERROR_LIBADD@

tableau_test_security_values_SOURCES = \
	tableau_test_libcerror.h \
	tableau_test_libtableau.h \
	tableau_test_macros.h \
	tableau_test_memory.c tableau_test_memory.h \
	tableau_test_security_values.c \
	tableau_test_unused.h

tableau_test_security_values_LDADD = \
	../libtableau/libtableau.la \
	@LIBCERROR_LIBADD@

tableau_test_support_SOURCES = \
	tableau_test_libtableau.h \
	tableau_test_macros.h \
	tableau_test_support.c \
	tableau_test_unused.h

tableau_test_support_LDADD = \
	../libtableau/libtableau.la

tableau_test_values_table_SOURCES = \
	tableau_test_libcerror.h \
	tableau_test_libtableau.h \
	tableau_test_macros.h \
	tableau_test_memory.c tableau_test_memory.h \
	tableau_test_unused.h \
	tableau_test_values_table.c

tableau_test_values_table_LDADD = \
	../libtableau/libtableau.la \
	@LIBCERROR_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

