#!/bin/sh
# Copyright (C) 2010, 2011 Stephan Creutz
#
# This script is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 2 as
# published by the Free Software Foundation.
#
# See the COPYING and AUTHORS files for more details.

set -e

url='svn://svn.valgrind.org/valgrind/tags/VALGRIND_3_6_1/'

if [ ! -e valgrind/.already_exported ] ; then
    svn export --force $url valgrind
    touch valgrind/.already_exported
fi
