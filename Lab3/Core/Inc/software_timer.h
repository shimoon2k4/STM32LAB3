/*
 * software_timer.h
 *
 *  Created on: Oct 11, 2025
 *      Author: Lenovo
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#define TIMER_CYCLE 10
#define COUNT_TIMER 3
extern int timer_flag[COUNT_TIMER];
void setTimer(int index, int duration);
void timerRun();

#endif /* INC_SOFTWARE_TIMER_H_ */
