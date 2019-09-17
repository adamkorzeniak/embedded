/*
 * main.c
 *
 *  Created on: May 21, 2018
 *      Author: adam
 */

#include <avr/io.h>
#include <stdio.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"

#define F_CPU 1000000UL


static volatile unsigned long int time = 0UL;
static volatile unsigned long int ticks = 0UL;

static volatile long int tickTime[5] = {0, 0, 0, 0, 0};
static volatile long int tickTimer[5] = {0, 0, 0, 0, 0};

const int cir = 220UL;

int main(void)
{
	lcd_init(LCD_DISP_ON);	/* initialize display, cursor off */
	lcd_clrscr();

	char displayTime[40];
	char displayTicks[40];

	OCR1A = 62500;
	TCCR1B |= (1 << WGM12);
	TIMSK1 |= (1 << OCIE1A);
	TCCR1B |= (1 << CS11);

    DDRD &= ~(1 << DDD2);     // Clear the PD2 pin
    // PD2 (PCINT0 pin) is now an input

    PORTD |= (1 << PORTD2);    // turn On the Pull-up
    // PD2 is now an input with pull-up enabled

    EICRA |= (1 << ISC01);    // falling edge
    EIMSK |= (1 << INT0);     // Turns on INT0

	sei();
	ticks = 0;

	while (1)					/* loop forever */
	   {

			if (ticks > 4) {

			long int timeDifference = (tickTime[4] - tickTime[0]) * 100;
			timeDifference += (tickTimer[4] - tickTimer[0]) / 125;

			long int speed = 4UL * 3600UL * cir / timeDifference;

			}

			lcd_clrscr();

			lcd_gotoxy(0,0);
			lcd_puts(displayTicks);

			lcd_gotoxy(0,1);
			lcd_puts(displayTime);

			_delay_ms(1000);

		}
}

ISR (TIMER1_COMPA_vect)
{
    time += 5;
}

ISR (INT0_vect)
{
	if (bit_is_clear(PIND, 2))
	{
		_delay_ms(10);
		if (bit_is_clear(PIND, 2))
		{
			if (ticks < 5) {
				tickTime[ticks] = time;
				tickTimer[ticks] = TCNT1;
			} else {

				tickTime[0] = tickTime[1];
				tickTimer[0] = tickTimer[1];
				tickTime[1] = tickTime[2];
				tickTimer[1] = tickTimer[2];
				tickTime[2] = tickTime[3];
				tickTimer[2] = tickTimer[3];
				tickTime[3] = tickTime[4];
				tickTimer[3] = tickTimer[4];
				tickTime[4] = time;
				tickTimer[4] = TCNT1;
			}
			ticks++;
			_delay_ms(10);
		}


	}
}
