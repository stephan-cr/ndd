#!/bin/sh
# Copyright (C) 2010, 2011 Stephan Creutz
#
# This script is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 2 as
# published by the Free Software Foundation.
#
# See the COPYING and AUTHORS files for more details.

set -e

cd valgrind
patch -N -p1 <patches/adapt_build_scripts || true
./autogen.sh
./configure --prefix=`pwd`/usr
procs=1
if [ $(which nproc) ] ; then
    procs=$(nproc)
else
    procs=$(grep processor /proc/cpuinfo | wc -l)
fi
make -j$procs
make install
