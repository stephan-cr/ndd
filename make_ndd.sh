#!/bin/sh
# Copyright (C) 2010, 2011 Stephan Creutz

set -e

mkdir -p ndd/docs/ ndd/tests/
touch ndd/docs/Makefile.am ndd/tests/Makefile.am
cp none/Makefile.am ndd/
cp none/nl_main.c ndd/ndd_main.c

sed -i 's/nl_/ndd_/g' ndd/Makefile.am ndd/ndd_main.c
sed -i 's/Nulgrind/NDD/' ndd/ndd_main.c
sed -i -e 's/NONE/NDD/g' -e 's/none/ndd/g' ndd/Makefile.am
