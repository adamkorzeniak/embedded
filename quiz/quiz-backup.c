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
char content[200];

void initializeQuestion(int index)
{

	line = 0;
	lines = 0;
	int lineIndex = 0;
	int contentIndex = 0;
	int addition = 0;

	char *array[5] = { questions[index], answers[index][0], answers[index][1], answers[index][2], answers[index][3]};

	for (int elIndex = 0; elIndex < 5; elIndex++) {

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

void initializeResult(int index, int answer)
{
	line = 0;
	lines = 0;
	int lineIndex = 0;
	int contentIndex = 0;

	char *displayValue = results[index][answer];

	int len = strlen(displayValue);

	for (int i = 0; i < (len - 1) / LCD_WIDTH + 1; i++) {
		linePositions[lineIndex] = contentIndex;
		if (i < (len - 1) / LCD_WIDTH)
		{
			memcpy( content + i * (LCD_WIDTH + 1), &displayValue[i * LCD_WIDTH], LCD_WIDTH );
			content[(i+1) * (LCD_WIDTH+1) -1] = '\n';
			contentIndex += LCD_WIDTH + 1;
		}
		else
		{
			int chars = (len - 1) % LCD_WIDTH + 1;
			memcpy( content + i * (LCD_WIDTH + 1), &displayValue[i * LCD_WIDTH], chars );
			content[i * (LCD_WIDTH+1) + chars] = '\n';
			contentIndex += chars + 1;
		}
		lineIndex++;
		lines++;
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
	_delay_ms(100);
}

