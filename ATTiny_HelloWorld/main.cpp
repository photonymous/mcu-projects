#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

// delay.h requires this defined before it is included
#define F_CPU 1000000 // Core clock is 8MHz, but we're dividing it by 8 (see fuses)

#include <util/delay.h>

int main(int argc, char** argv)
{

	// "Tiny Programmer" on-board LED is on digital pin 0
	DDRB |= _BV(PB0); // set pin 0 as an output
	
	while(1)
	{

		PORTB |= _BV(PB0);
		_delay_ms(50);
		PORTB &= ~_BV(PB0);
		_delay_ms(50);

	}
}



