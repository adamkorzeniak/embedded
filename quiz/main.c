/*
 * main.c
 *
 *  Created on: May 11, 2018
 *      Author: adam
 */

#ifndef F_CPU
#define F_CPU 1000000UL // 8 MHz clock speed
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include "lcd.h"
#include "data.h"
#include "display.h"

#define CONTROL_PORT PORTB
#define CONTROL_PIN PINB
#define SCROLL_UP PB6
#define SCROLL_DOWN PB7
#define LED_LIGHT PB0
#define BUTTON_A PB1
#define BUTTON_B PB2
#define BUTTON_C PB3
#define BUTTON_D PB4

void setupGame();
int getPressedButton();
int isButtonPressed(int buttonIndex);
int receiveAction();
void shuffle(size_t n);

const int REQUIRED_CONFIDENCE = 15; //ms
const int quizSize = 10;
const int dataSize = 10;
int buttons[6] = {BUTTON_A, BUTTON_B, BUTTON_C, BUTTON_D, SCROLL_UP, SCROLL_DOWN};
int buttonPressed = -1;
int *array;

int main(void)
{
	setupGame();
	displayInt(100);
	_delay_ms(100000);

	for (int i = 0; i < quizSize; i ++) {

		initializeQuestion(i, i+1);
		display();
		int button = receiveAction();
		initializeResult(i, button);
		display();
		receiveAction();
	}
}


int receiveAction()
{
	int button = -1;
	while (button > 3 || button < 0)
	{
		button = getPressedButton();
		if (button == 4)
		{
			moveDisplayDown();
			display();
		}
		else if (button == 5)
		{
			moveDisplayUp();
			display();
		}
	}
	return button;
}

void setupGame() {

	lcd_init(LCD_DISP_ON);	/* initialize display, cursor off */

	DDRD = 0b11111111;
	DDRB = 0b11111111;

	PORTB = 0x00;
	PORTD = 0x00;
	PORTB |= (1 << BUTTON_A) | (1 << BUTTON_B) | (1 << BUTTON_C) | (1 << BUTTON_D) | (1 << SCROLL_UP) | (1 << SCROLL_DOWN);

}

int getPressedButton()
{
	for (int i = 0; i < 6; i++ ) {

		if (isButtonPressed(i)) {
			if (buttonPressed != i)
			{
				buttonPressed = i;
				return i;
			}
		}
		else if (i == buttonPressed)
		{
			buttonPressed = -1;
		}
	}
	return -1;
}

int isButtonPressed(int buttonIndex)
{
	if (bit_is_clear(CONTROL_PIN, buttons[buttonIndex])) {

		_delay_ms(REQUIRED_CONFIDENCE);

		if (bit_is_clear(CONTROL_PIN, buttons[buttonIndex]))
		{
			return 1;
		}
	}
	return 0;
}

void shuffle(size_t n)
{
	for (int a = 0; a < n; a++)
	{
		array[a] = a;
	}

    if (n > 1)
    {
        size_t i;
        for (i = 0; i < n - 1; i++)
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}
