/*
 * main.c
 *
 *  Created on: May 11, 2018
 *      Author: adam
 */

#ifndef F_CPU
#define F_CPU 1000000UL // 1 MHz clock speed
#endif

#include <avr/io.h>
#include <util/delay.h>

void checkButton(int player);
void displayResult();
void isFinished();
void setupGame();


int REQUIRED_CONFIDENCE = 15; //ms
int BUTTON[2] = {PB3, PB4};

int confidence[2];
int buttonState[2];
int ledNumber[2];
int oldScore;
int score;

int LEDS[2][6] = {
		{PD4, PD3, PD2, PD1, PD0, PD7},
		{PC0, PC1, PC2, PC3, PC4, PC5}
};

int main(void)
{
	setupGame();
	while (1)
	{

		checkButton(0);
		checkButton(1);

		displayResult();
		isFinished();

		_delay_ms(1);
	}

}

void setupGame() {

	DDRD = 0b11111111;
	DDRC = 0b11111111;

	PORTC = 0x00;
	PORTD = 0x00;
	PORTB |= 1 << BUTTON[0];
	PORTB |= 1 << BUTTON[1];

	for (int i = 0; i < 2; i++) {
		confidence[i] = buttonState[i] = ledNumber[i] = 0;
	}
	score = oldScore = 0;

}

void checkButton(int player)
{
	if (bit_is_clear(PINB, BUTTON[player]) != buttonState[player]) {

		confidence[player]++;

		if (confidence[player] > REQUIRED_CONFIDENCE)
		{
			buttonState[player] = !buttonState[player];
			confidence[player] = 0;
			if (buttonState[player] == 1)
			{
				score += player * 2 - 1;
			}
		}
	}
	else
	{
		confidence[player] = 0;
	}
}

void displayResult()
{
	if (score > oldScore) {
		if (score > 0) {
			PORTC |= 1 << LEDS[1][ledNumber[1]];
			ledNumber[1]++;
		} else {
			ledNumber[0]--;
			PORTD &= ~(1 << LEDS[0][ledNumber[0]]);
		}
	} else if (score < oldScore) {
		if (score < 0) {
			PORTD |= 1 << LEDS[0][ledNumber[0]];
			ledNumber[0]++;
		} else {
			ledNumber[1]--;
			PORTC &= ~(1 << LEDS[1][ledNumber[1]]);
		}
	}
	oldScore = score;
}

void isFinished() {
	if (score > 5) {

		_delay_ms(500);

		for (int i = 0; i < 6; i++) {
			PORTC ^= 0xFF;
			_delay_ms(500);
		}

		setupGame();
	} else if (score < -5) {

		_delay_ms(500);

		for (int i = 0; i < 6; i++) {
			PORTD ^= 0xFF;
			_delay_ms(500);
		}
		setupGame();
	}
}
