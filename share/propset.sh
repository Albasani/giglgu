#!/bin/sh
#
# $Id: propset.sh 41 2012-02-03 18:28:17Z alba $
#
export "LANG=C"
export "LC_ALL=C"
set -o nounset

find . -type f \( \
	-name '*.sh' \
\) -exec svn propset svn:executable "*" {} \+

find . -type f \( \
	-name CMakeLists.txt -o \
	-name '*.cmake' -o \
	-name '*.cmd' -o \
	-name config.h.in -o \
	-name '*.cpp' -o \
	-name '*.css' -o \
	-name '*.h' -o \
	-name '*.inl' -o \
	-name '*.sh' \
\) -exec svn propset svn:keywords "URL Revision Id" {} \+

find . -type f \( \
	-name CMakeLists.txt -o \
	-name '*.cmake' -o \
	-name '*.cmd' -o \
	-name config.h.in -o \
	-name '*.cpp' -o \
	-name '*.css' -o \
	-name '*.h' -o \
	-name '*.inl' -o \
	-name '*.sh' -o \
	-name '*.sh' \
\) -exec svn propset svn:eol-style native {} \+
