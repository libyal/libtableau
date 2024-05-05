ACLOCAL_AMFLAGS = -I m4

SUBDIRS = \
	include \
	common \
	libcerror \
	libcthreads \
	libclocale \
	libcnotify \
	libuna \
	libtableau \
	tableautools \
	po \
	manuals \
	tests \
	msvscpp

DPKG_FILES = \
	dpkg/changelog \
	dpkg/changelog.in \
	dpkg/compat \
	dpkg/control \
	dpkg/copyright \
	dpkg/rules \
	dpkg/libtableau-dev.install \
	dpkg/libtableau.install \
	dpkg/source/format

GETTEXT_FILES = \
	config.rpath \
	po/Makevars.in

PKGCONFIG_FILES = \
	libtableau.pc.in

SPEC_FILES = \
	libtableau.spec \
	libtableau.spec.in

EXTRA_DIST = \
	$(DPKG_FILES) \
	$(GETTEXT_FILES) \
	$(PKGCONFIG_FILES) \
	$(SPEC_FILES)

DISTCLEANFILES = \
	config.status \
	config.cache \
	config.log \
	libtableau.pc \
	libtableau.spec \
	Makefile \
	Makefile.in \
	po/Makevars

pkgconfigdir = $(libdir)/pkgconfig

pkgconfig_DATA = \
	libtableau.pc

libtool: @LIBTOOL_DEPS@
	cd $(srcdir) && $(SHELL) ./config.status --recheck

lib: library

library:
	cd $(srcdir)/common && $(MAKE) $(AM_MAKEFLAGS)
	cd $(srcdir)/libcerror && $(MAKE) $(AM_MAKEFLAGS)
	cd $(srcdir)/libctrheads && $(MAKE) $(AM_MAKEFLAGS)
	cd $(srcdir)/libclocale && $(MAKE) $(AM_MAKEFLAGS)
	cd $(srcdir)/libcnotify && $(MAKE) $(AM_MAKEFLAGS)
	cd $(srcdir)/libuna && $(MAKE) $(AM_MAKEFLAGS)
	cd $(srcdir)/libtableau && $(MAKE) $(AM_MAKEFLAGS)
	cd $(srcdir)/po && $(MAKE) $(AM_MAKEFLAGS)

