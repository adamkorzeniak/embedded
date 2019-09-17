/*
 * main.c
 *
 *  Created on: May 13, 2018
 *      Author: adam
 */
#ifndef F_CPU
#define F_CPU 1000000UL // 8 MHz clock speed
#endif

#include <avr/io.h>
#include <util/delay.h>

#define SPEAKER PIN1

#define NOTE_C 7710
#define NOTE_D 6850
#define NOTE_E 6090
#define NOTE_F 5764
#define NOTE_G 5128
#define NOTE_A 4566
#define NOTE_H 4068
#define NOTE_C1 3836

//#define NOTE_C 7644
//#define NOTE_D 6810
//#define NOTE_E 6068
//#define NOTE_F 5726
//#define NOTE_G 5102
//#define NOTE_A 4546
//#define NOTE_H 4050
//#define NOTE_C1 3822

#define PIN_NOTE_C PIN3
#define PIN_NOTE_D PIN0
#define PIN_NOTE_E PIN1
#define PIN_NOTE_F PIN7
#define PIN_NOTE_G PIN5
#define PIN_NOTE_A PIN2
#define PIN_NOTE_H PIN6
#define PIN_NOTE_C1 PIN4

int main(void)
{
	DDRB = 0x00;
	PORTB = 0xFF;
	DDRC |= 1 << SPEAKER;

	while(1)
	{
		if (~PINB & 1 << PIN_NOTE_C)
		{
			PORTC |= 1 << SPEAKER;
			_delay_us(NOTE_C / 2);
			PORTC &= ~(1 << SPEAKER);
			_delay_us(NOTE_C / 2);
		}
		else if (~PINB & 1 << PIN_NOTE_D)
		{
			PORTC |= 1 << SPEAKER;
			_delay_us(NOTE_D / 2);
			PORTC &= ~(1 << SPEAKER);
			_delay_us(NOTE_D / 2);
		}
		else if (~PINB & 1 << PIN_NOTE_E)
		{
			PORTC |= 1 << SPEAKER;
			_delay_us(NOTE_E / 2);
			PORTC &= ~(1 << SPEAKER);
			_delay_us(NOTE_E / 2);
		}
		else if (~PINB & 1 << PIN_NOTE_F)
		{
			PORTC |= 1 << SPEAKER;
			_delay_us(NOTE_F / 2);
			PORTC &= ~(1 << SPEAKER);
			_delay_us(NOTE_F / 2);
		}
		else if (~PINB & 1 << PIN_NOTE_G)
		{
			PORTC |= 1 << SPEAKER;
			_delay_us(NOTE_G / 2);
			PORTC &= ~(1 << SPEAKER);
			_delay_us(NOTE_G / 2);
		}
		else if (~PINB & 1 << PIN_NOTE_A)
		{
			PORTC |= 1 << SPEAKER;
			_delay_us(NOTE_A / 2);
			PORTC &= ~(1 << SPEAKER);
			_delay_us(NOTE_A / 2);
		}
		else if (~PINB & 1 << PIN_NOTE_H)
		{
			PORTC |= 1 << SPEAKER;
			_delay_us(NOTE_H / 2);
			PORTC &= ~(1 << SPEAKER);
			_delay_us(NOTE_H /2);
		}
		else if (~PINB & 1 << PIN_NOTE_C1)
		{
			PORTC |= 1 << SPEAKER;
			_delay_us(NOTE_C1 / 2);
			PORTC &= ~(1 << SPEAKER);
			_delay_us(NOTE_C1 /2);
		}
	}
}
