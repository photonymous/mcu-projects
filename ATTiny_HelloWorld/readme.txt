Check if the attiny85 is plugged into programmer correctly, and
programmer is recognized by system. (note that I'm using the Sparkfun Tiny 
AVR Programmer)

   sudo avrdude -c usbtiny -p t85
   
Should output something like this:

   avrdude: AVR device initialized and ready to accept instructions

   Reading | ################################################## | 100% 0.01s

   avrdude: Device signature = 0x1e930b

   avrdude: safemode: Fuses OK

   avrdude done.  Thank you.

Then you can

   make
   make flash
   
The light should start blinking
