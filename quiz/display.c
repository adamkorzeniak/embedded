/*
 * display.c
 *
 *  Created on: May 18, 2018
 *      Author: adam
 */

#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include "lcd.h"
#include "data.h"
#include "display.h"

int line;
int lines;
int linePositions[20];
char content[400];

void assignContent(char **array, int size);

void initializeQuestion(int index, int number)
{
	char *array[5];

	char question[100];
	char element1[40];
	char element2[40];
	char element3[40];
	char element4[40];

	sprintf(question, "%d. %s", number, questions[index]);
	sprintf(element1, "A) %s", answers[index][0]);
	sprintf(element2, "B) %s", answers[index][1]);
	sprintf(element3, "C) %s", answers[index][2]);
	sprintf(element4, "D) %s", answers[index][3]);
	array[0] = question;
	array[1] = element1;
	array[2] = element2;
	array[3] = element3;
	array[4] = element4;

	assignContent(array, 5);

}

void initializeResult(int index, int answer)
{
	char *array[1];

	array[0] = results[index][answer];

	assignContent(array, 1);
}

void assignContent(char **array, int size)
{
	line = 0;
	lines = 0;
	int lineIndex = 0;
	int contentIndex = 0;
	int addition = 0;

	for (int elIndex = 0; elIndex < size; elIndex++) {

		addition = contentIndex;
		int len = strlen(array[elIndex]);

		for (int i = 0; i < (len - 1) / LCD_WIDTH + 1; i++) {
			linePositions[lineIndex] = contentIndex;
			if (i < (len - 1) / LCD_WIDTH)
			{
				memcpy( content + addition + i * (LCD_WIDTH + 1), &array[elIndex][i * LCD_WIDTH], LCD_WIDTH );
				content[addition +(i+1) * (LCD_WIDTH+1) -1] = '\n';
				contentIndex += LCD_WIDTH + 1;
			}
			else
			{
				int chars = (len - 1) % LCD_WIDTH + 1;
				memcpy( content + addition + i * (LCD_WIDTH + 1), &array[elIndex][i * LCD_WIDTH], chars );
				content[addition + i * (LCD_WIDTH+1) + chars] = '\n';
				contentIndex += chars + 1;
			}
			lineIndex++;
			lines++;
		}

	}
	linePositions[lineIndex] = contentIndex;
	content[contentIndex] = '\0';
}

void display()
{
	int linePosition = linePositions[line];
	int length = linePositions[line + LCD_HEIGHT] - linePosition;
	char display[length];
	memcpy( display, &content[linePosition], length);
	display[length] = '\0';
	lcd_clrscr();
	lcd_gotoxy(0,0);
	lcd_puts(display);
	_delay_ms(100);
}

void moveDisplayDown()
{
	line++;
	if (line  > lines - LCD_HEIGHT )
	{
		line = lines - LCD_HEIGHT;
	}
}

void moveDisplayUp()
{
	line--;
	if (line < 0)
	{
		line = 0;
	}
}


void displayInt(int x)
{
	char z[10];
	sprintf( z, "%d", x);
	lcd_clrscr();
	lcd_gotoxy(0,0);
	lcd_puts(z);
	_delay_ms(20-0);
}
