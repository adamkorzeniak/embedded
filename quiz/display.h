/*
 * display.h
 *
 *  Created on: Jun 17, 2018
 *      Author: adam
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#endif /* DISPLAY_H_ */

#define LCD_WIDTH 16
#define LCD_HEIGHT 2

void initializeQuestion(int index, int number);
void display();
void moveDisplayUp();
void moveDisplayDown();
void initializeResult(int index, int answer);
void displayInt(int x);

