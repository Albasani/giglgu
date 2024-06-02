#!/bin/sh -x
#
# $Id: build.sh 238 2012-02-20 10:34:56Z alba $
#
export "LANG=C"
export "LC_ALL=C"
set -o nounset
set -o errexit

prefix_dir="${HOME}/opt/giglgu"
[ -d "${prefix_dir}" ] || mkdir -p "${prefix_dir}" 
build_dir=build
[ -n "${GIGLGU_LOGFILE:-}" ] || export "GIGLGU_LOGFILE=%P-%T.log"

[ -d "${build_dir}" ] || mkdir "${build_dir}"
cd "${build_dir}"
cmake -Wdev \
	"-DCMAKE_INSTALL_PREFIX=${prefix_dir}" \
	"-DBUILD_SHARED_LIBS=ON" \
	"-DWITH_TESTING=ON" \
	"-DWITH_SEPARATE_LIBS=ON" \
	..
make depend
make doc
make all
# make install
make test
