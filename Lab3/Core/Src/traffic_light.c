/*
 * traffic_light.c
 *
 *  Created on: Oct 11, 2025
 *      Author: Lenovo
 */

#include "traffic_light.h"

const TLGroup VERTICAL = { {LED_RED_VERTICAL_GPIO_Port, LED_GREEN_VERTICAL_GPIO_Port, LED_YELLOW_VERTICAL_GPIO_Port},
                         {LED_RED_VERTICAL_Pin, LED_GREEN_VERTICAL_Pin, LED_YELLOW_VERTICAL_Pin} };
const TLGroup HORIZONTAL = { {LED_RED_HORIZONTAL_GPIO_Port, LED_GREEN_HORIZONTAL_GPIO_Port, LED_YELLOW_HORIZONTAL_GPIO_Port},
                          {LED_RED_HORIZONTAL_Pin, LED_GREEN_HORIZONTAL_Pin, LED_YELLOW_HORIZONTAL_Pin} };

uint8_t DURATION[3] = {5, 3, 2};

//int state_vertical = 0;
//int state_horizontal = 0;

Axis AX_H = { .state = RED,   .counter = 5 };
Axis AX_V = { .state = GREEN, .counter = 3 };

int state = 0;

void tl_set_color(const TLGroup* g, int color) {
    for (int c = 0; c < 3; ++c) {
        HAL_GPIO_WritePin(g->port[c], g->pin[c], (c == color) ? RESET : SET);
    }
}

void apply_axis_lights(int is_horizontal, int state) {
    const TLGroup *g1;

    if (is_horizontal) {
        g1 = &HORIZONTAL;
    } else {
        g1 = &VERTICAL;
    }

    switch (state) {
        case RED:    tl_set_color(g1, RED);    break;
        case GREEN:  tl_set_color(g1, GREEN);  break;
        case YELLOW:  tl_set_color(g1, YELLOW); break;
        default:      break;
    }
}

void axis_tick(Axis* ax, int is_horizontal) {
    apply_axis_lights(is_horizontal, ax->state);

    if (--ax->counter <= 0) {
        ax->state   = (ax->state + 1) % 3;
        ax->counter = DURATION[ax->state];
    }
}

void init_traffic_light(void) {
	HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, SET);
	HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, SET);
	HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, SET);
	HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, SET);
}
void update_led_time(int color, int value) {
    if (DURATION[color] < MAX_TIME_DURATION) {
    	DURATION[color] = value;
    }
}
//void traffic_light_run(void) {
//
//}
void test_process_run(){
	if(timer_flag[0] == 1){
		updateClockBuffer(AX_V.counter, AX_H.counter);
		axis_tick(&AX_H, 1);
		axis_tick(&AX_V, 0);
	    setTimer(0, 1000);
	}
}
