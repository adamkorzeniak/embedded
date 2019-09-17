#ifndef F_CPU
#define F_CPU 1000000UL // 8 MHz clock speed
#endif

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRD = 0x00;
	PORTD = 0xFF;
  while(1) //infinite loop
  {
	DDRD = 0x5E;
    _delay_ms(1000); //1 second delay
    DDRD = 0x5F;
    _delay_ms(1000); //1 second delay
    DDRD = 0x76;
    _delay_ms(1000); //1 second delay
    DDRD = 0x7E;
    _delay_ms(1000); //1 second delay
    DDRD = 0x5F;
    _delay_ms(1000); //1 second delay
	PORTD = 0x00;
    DDRD = 0xED;
    _delay_ms(1000); //1 second delay
	PORTD = 0xFF;
    _delay_ms(1000); //1 second delay
	PORTD = 0x00;
    _delay_ms(1000); //1 second delay
	PORTD = 0xFF;
    _delay_ms(1000); //1 second delay
	PORTD = 0x00;
    _delay_ms(1000); //1 second delay
	PORTD = 0xFF;
    _delay_ms(1000); //1 second delay
	PORTD = 0x00;
    _delay_ms(3000); //1 second delay
	PORTD = 0xFF;
  }
}
