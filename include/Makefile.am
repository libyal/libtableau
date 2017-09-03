include_HEADERS = \
	libtableau.h

pkginclude_HEADERS = \
	libtableau/definitions.h \
	libtableau/error.h \
	libtableau/extern.h \
	libtableau/features.h \
	libtableau/types.h

EXTRA_DIST = \
	libtableau.h.in \
	libtableau/definitions.h.in \
	libtableau/features.h.in \
	libtableau/types.h.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f libtableau.h
	/bin/rm -f libtableau/definitions.h
	/bin/rm -f libtableau/features.h
	/bin/rm -f libtableau/types.h
	/bin/rm -f Makefile

