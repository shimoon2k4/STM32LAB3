/*
 * global.h
 *
 *  Created on: Oct 11, 2025
 *      Author: Lenovo
 */

#ifndef INC_SEVEN_SEGMENT_H_
#define INC_SEVEN_SEGMENT_H_

#include "button.h"
#include "software_timer.h"

#define MAX_LED 4
void clearAllState();
void displayNumber(int is_horizontal,int number);
void updateClockBuffer(int num_vertical, int num_horizontal);
void update7SEG(int index);
void clearAllSignal();
void changeSignaLedSegment(int signal);
void seg_scan_task(int timer_idx, int scan_period_ms);
#endif /* INC_SEVEN_SEGMENT_H_ */
