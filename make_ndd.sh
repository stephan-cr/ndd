#!/bin/sh
# Copyright (C) 2010, 2011 Stephan Creutz
#
# This script is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 2 as
# published by the Free Software Foundation.
#
# See the COPYING and AUTHORS files for more details.

set -e

mkdir -p ndd/docs/ ndd/tests/
touch ndd/docs/Makefile.am ndd/tests/Makefile.am
cp none/Makefile.am ndd/
cp none/nl_main.c ndd/ndd_main.c

sed -i 's/nl_/ndd_/g' ndd/Makefile.am ndd/ndd_main.c
sed -i 's/Nulgrind/NDD/' ndd/ndd_main.c
sed -i -e 's/NONE/NDD/g' -e 's/none/ndd/g' ndd/Makefile.am
