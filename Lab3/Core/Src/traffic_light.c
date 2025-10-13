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

const uint8_t DURATION[3] = {5, 3, 2};

Axis AX_H = { .state = RED,   .counter = 5 };
Axis AX_V = { .state = GREEN, .counter = 3 };

void tl_set_color(const TLGroup* g, int color) {
    for (int c = 0; c < 3; ++c) {
        HAL_GPIO_WritePin(g->port[c], g->pin[c], (c == color) ? GPIO_PIN_RESET : GPIO_PIN_SET);
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
}

void traffic_light_run(void) {
    axis_tick(&AX_H, 1);
    axis_tick(&AX_V, 0);
}
