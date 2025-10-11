/*
 * software_timer.c
 *
 *  Created on: Oct 11, 2025
 *      Author: Lenovo
 */
#include "software_timer.h"
int timer_flag[COUNT_TIMER] = {0};
int timer_counter[COUNT_TIMER] = {0};
void setTimer(int index, int duration){
	if(index>3) return;
	timer_counter[index] = duration/TIMER_CYCLE;
	timer_flag[index] = 0;
}
void timerRun(){
	int index = 0;
	while(index<COUNT_TIMER){
	if(timer_counter[index]>0){
		timer_counter[index]--;
		if(timer_counter[index] <= 0){
			timer_flag[index] = 1;
		}
	}
	index++;
	}
}

