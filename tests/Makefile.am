AM_CPPFLAGS = \
	-I../include -I$(top_srcdir)/include \
	-I../common -I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCTHREADS_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBTABLEAU_DLL_IMPORT@

BUILT_SOURCES = package.m4

check_AUTOTESTS = \
	test_library \
	test_manpages

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

AUTOM4TE = autom4te
AUTOTEST = $(AUTOM4TE) --language=autotest

SUFFIXES = .at

.at:
	$(AM_V_GEN)rm -f $@ $@.tmp; \
	$(AUTOTEST) -I '$(srcdir)' -o $@.tmp $< && \
	mv $@.tmp $@

atconfig: $(top_builddir)/config.status
	cd $(top_builddir) && $(SHELL) ./config.status tests/$@

check-build: $(check_PROGRAMS)

check-local: $(check_AUTOTESTS)
	@fail=0; \
	for test_suite in $(check_AUTOTESTS); do \
		$(AM_TESTS_ENVIRONMENT) $(SHELL) "./$$test_suite" $(TESTSUITEFLAGS) || fail=1; \
		echo ""; \
	done; \
	exit $$fail

clean-local:
	for test_suite in $(check_AUTOTESTS); do \
		test ! -f "$$test_suite" || $(SHELL) "./$$test_suite" --clean; \
	done

package.m4: $(top_srcdir)/configure.ac
	$(AM_V_GEN):; \
	{ \
	  echo 'm4_define([AT_PACKAGE_NAME], [$(PACKAGE_NAME)])' ; \
	  echo 'm4_define([AT_PACKAGE_TARNAME], [$(PACKAGE_TARNAME)])' ; \
	  echo 'm4_define([AT_PACKAGE_VERSION], [$(PACKAGE_VERSION)])' ; \
	  echo 'm4_define([AT_PACKAGE_STRING], [$(PACKAGE_STRING)])' ; \
	  echo 'm4_define([AT_PACKAGE_BUGREPORT], [$(PACKAGE_BUGREPORT)])' ; \
	} > $@

test_library: \
	package.m4 \
	test_library.at \
	test_macros.at

test_manpages: \
	package.m4 \
	test_manpages.at

EXTRA_DIST = \
	$(check_AUTOTESTS:=.at) \
	package.m4 \
	test_macros.at

CLEANFILES = \
	$(check_AUTOTESTS) \
	*.exe \
	*.tmp \
	notify_stream.log

DISTCLEANFILES = \
	*.log \
	atconfig \
	Makefile \
	Makefile.in

