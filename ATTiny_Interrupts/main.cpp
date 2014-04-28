#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t slowdown, thresh;

ISR(TIM0_OVF_vect)
{
   slowdown++;
   if(slowdown >= thresh)
   {
      PORTB ^= 1<<PB0; // Toggle Port B bit/pin 0
      slowdown  = 0;
      
      thresh++;
      if(thresh > 80)
         thresh = 1;
   }   
}


int main(int argc, char** argv)
{
   // CLI: Clear Interrupts
   cli(); // Disable global interrupts
   
   // DDRB: Data Direction Register for port B
	DDRB |= 1<<PB0; // set pin 0 as an output
   
   // TCCR0B: Timer Counter Control Register B
   // CS0X Bits control timer prescaling (slows the counter by the specified fraction):
   // 2 1 0
   // -----
   // 0 0 1  no prescaling
   // 0 1 0  1/8th
   // 0 1 1  1/64th
   // 1 0 0  1/256th
   // 1 0 1  1/1024th
   TCCR0B |= (1<<CS01);// | (1<<CS00);// | (1<<CS02)
   
   // TIMSK: Timer/Counter Interrupt Mask Register
   // TOIE0: Timer Overflow Interrupt Enable 0 (there's also a '1')
   TIMSK  |= 1<<TOIE0; 
   
   // TCNT0: Timer Count 0 
   TCNT0   = 0;  // Initialize the count to 0. Timer counts up.
   
   slowdown = 0;
   thresh   = 1;
   
   // Set Enable Interrupts
   sei(); // Enable global interrupts
   
   while(1)
   {}
}






