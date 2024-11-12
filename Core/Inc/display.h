/*
 * display.h
 *
 *  Created on: Nov 1, 2022
 *      Author: dell
 */

#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

#include "main.h"
#include "global.h"

extern int index_led;
extern int counterL, counterP;

void display7SEG(int counter);
void update7SEG(int index);

void updateClockBufferMode1();
void updateClockBufferMode2();
void updateClockBufferMode3();
void updateClockBufferMode4();

#endif /* INC_DISPLAY_H_ */
