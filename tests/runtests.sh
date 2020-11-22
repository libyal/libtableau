#!/bin/sh
# Script to run tests
#
# Version: 20201121

if test -f ${PWD}/libtableau/.libs/libtableau.1.dylib && test -f ./pytableau/.libs/pytableau.so;
then
	install_name_tool -change /usr/local/lib/libtableau.1.dylib ${PWD}/libtableau/.libs/libtableau.1.dylib ./pytableau/.libs/pytableau.so;
fi

make check CHECK_WITH_STDERR=1;
RESULT=$?;

if test ${RESULT} -ne 0 && test -f tests/test-suite.log;
then
	cat tests/test-suite.log;
fi
exit ${RESULT};

