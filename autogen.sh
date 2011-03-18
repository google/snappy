#! /bin/sh -e
export PATH=/bin:/usr/bin  # Local hack.
rm -rf autom4te.cache
aclocal -I m4
autoheader
libtoolize --copy
automake --add-missing --copy
autoconf
