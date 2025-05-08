#PREFIX_CON=/home/mkrosby0/Documents/CS1B/Serendipity
PREFIX_CON=$(realpath ..)
./configure --prefix=${PREFIX_CON} --disable-leaks --disable-overwrite --disable-relink --enable-sigwinch --with-install-prefix=${PREFIX_CON} --without-cxx --disable-echo
