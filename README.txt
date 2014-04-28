Things to install:
==================

arduino-mk
arduino-core
arduino
binutils-avr
gcc-avr (exe = avr-gcc and avr-g++)
avr-libc
simulavr
avrdude (maybe gets installed with arduino)
flex
bison
byacc
libusb-dev


Add yourself to some groups:
============================

sudo usermod -a -G tty username
sudo usermod -a -G dialout username

Finally:
========

Log out and back in
Should be ready to go!
...go into one of the examples and type "make" followed by "make flash" or "make upload"

