/*
 * main.c
 *
 *  Created on: May 16, 2018
 *      Author: adam
 */

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "pinDefines.h"
#include "lcd.h"

//Functions//
static inline void initADC0(void)
{
	ADMUX |= (1 << REFS0);					//reference voltage on AVCC
	ADCSRA |= (1 << ADPS1) | (1 << ADPS0);	//ADC clock prescaler /8
	ADCSRA |= (1 << ADEN);					//enable ADC
}

static inline void display(int value1, int value2)
{
	lcd_clrscr();
	lcd_gotoxy(0,0);

	char buffer[12];
    sprintf(buffer, "%d", value1);
	lcd_puts(buffer);

	lcd_gotoxy(0,1);

    sprintf(buffer, "%d", value2);
	lcd_puts(buffer);
	_delay_ms(500);

}

int main(void)
{
	  lcd_init(LCD_DISP_ON);	/* initialize display, cursor off */

	//Inits//
	uint8_t ledValue;
	uint16_t adcValue;
	uint8_t i;
	initADC0();
	LED_DDR = 0xff;

	//Event  loop
	while(1)
	{
		ADCSRA |= (1 << ADSC);				//start ADC conversion
		loop_until_bit_is_clear(ADCSRA, ADSC);	//wait until done
		adcValue = ADC;						//read ADC in
		//Have 10 bits, want 3 bits (eight leds)
		ledValue = (adcValue >> 7);

		LED_PORT = 0;
		for (i=0; i <= ledValue; i++)
		{
			LED_PORT |= (1 << i);
		}
		display(adcValue, 0);

		_delay_ms(50);

	}
}
