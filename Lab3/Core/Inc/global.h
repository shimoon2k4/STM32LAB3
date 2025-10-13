/*
 * global.h
 *
 *  Created on: Oct 11, 2025
 *      Author: Lenovo
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "button.h"
#include "software_timer.h"

#define MAX_LED 4
void clearAllState();
void displayNumberVertical(int number);
void displayHorizontal(int number);
void updateClockBuffer(int num_vertical, int num_horizontal);
void update7SEG(int index);
void changeSignaLedSegment(int signal);

#endif /* INC_GLOBAL_H_ */
