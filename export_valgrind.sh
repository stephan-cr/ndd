#!/bin/sh
# Copyright (C) 2010, 2011 Stephan Creutz

set -e

url='svn://svn.valgrind.org/valgrind/tags/VALGRIND_3_6_1/'

if [ ! -e valgrind/.already_exported ] ; then
    svn export --force $url valgrind
    touch valgrind/.already_exported
fi
