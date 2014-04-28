#include "Arduino.h"

#define MAIN \
 int main(void) { init(); setup(); for (;;) loop(); return 0; }

extern "C" void __cxa_pure_virtual(void) 
{
    while(1);
}
