# Introduction #

Installing the required libraries.

**You will need a working OpenCL implementation**

# Details #

#Haptic Installation steps

aclocal

autoheader

autoconf


# This may be necessary to generate Install.sh
automake --add-missing
./configure
make

You shouldnt need to do make install in this case since all that is delivered by the project is a library