#!/bin/sh
# Copyright (C) 2010, 2011 Stephan Creutz

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
