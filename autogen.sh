#! /bin/sh -e
rm -rf autom4te.cache
aclocal -I m4
autoheader
case `uname` in 
    Darwin*) glibtoolize --copy ;;
    *) libtoolize --copy ;;
esac
automake --add-missing --copy
autoconf
