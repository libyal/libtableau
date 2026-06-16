#!/bin/sh
# Script to run tests
#
# Version: 20260609

if test -f ${PWD}/libtableau/.libs/libtableau.1.dylib && test -f ./pytableau/.libs/pytableau.so
then
	install_name_tool -change /usr/local/lib/libtableau.1.dylib ${PWD}/libtableau/.libs/libtableau.1.dylib ./pytableau/.libs/pytableau.so
fi

make check-build > /dev/null

make check $@
RESULT=$?

if test ${RESULT} -ne 0
then
	find . -name \*.log -path \*.dir/\*/\*.log -print -exec cat {} \;
fi
exit ${RESULT}

