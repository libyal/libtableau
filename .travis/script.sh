#!/bin/sh
# Script to run script step on Travis-CI
#
# Version: 20190808

# Exit on error.
set -e;

if test ${TRAVIS_OS_NAME} = "linux" || test ${TRAVIS_OS_NAME} = "linux-ppc64le";
then
	export PATH=$(echo $PATH | tr ":" "\n" | sed '/\/opt\/python/d' | tr "\n" ":" | sed "s/::/:/g");
fi

if test ${TARGET} = "docker";
then
	docker run -t -v "${PWD}:/libtableau" ${DOCKERHUB_REPO}:${DOCKERHUB_TAG} sh -c "cd libtableau && .travis/script_docker.sh";

elif test ${TARGET} != "coverity";
then
	.travis/runtests.sh;

	if test ${TARGET} = "macos-gcc-pkgbuild";
	then
		export VERSION=`sed '5!d; s/^ \[//;s/\],$//' configure.ac`;

		make install DESTDIR=${PWD}/osx-pkg;
		mkdir -p ${PWD}/osx-pkg/usr/share/doc/libtableau;
		cp AUTHORS COPYING NEWS README ${PWD}/osx-pkg/usr/share/doc/libtableau;

		pkgbuild --root osx-pkg --identifier com.github.libyal.libtableau --version ${VERSION} --ownership recommended ../libtableau-${VERSION}.pkg;
	fi
fi
