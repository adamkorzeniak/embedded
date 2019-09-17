/*
 * main.c
 *
 *  Created on: May 15, 2018
 *      Author: adam
 */

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include "lcd.h"

#define F_CPU 1000000UL


int main(void)
{
  lcd_init(LCD_DISP_ON);	/* initialize display, cursor off */

    while (1)					/* loop forever */
       {
			lcd_clrscr();

			lcd_gotoxy(5,0);

			lcd_puts("XXXX");

			lcd_gotoxy(5,1);

			lcd_puts("YYYYY");

			_delay_ms(50);
        }
}
