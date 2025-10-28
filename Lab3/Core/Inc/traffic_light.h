/*
 * traffic_light.h
 *
 *  Created on: Oct 11, 2025
 *      Author: Lenovo
 */

#ifndef INC_TRAFFIC_LIGHT_H_
#define INC_TRAFFIC_LIGHT_H_
#include <seven_segment.h>

#define RED    0
#define GREEN  1
#define YELLOW 2
#define MAX_TIME_DURATION 99
//extern int state_vertical;
//extern int state_horizontal;

extern uint8_t DURATION[3];

typedef struct {
    GPIO_TypeDef* port[3];
    uint16_t pin[3];
} TLGroup;

extern const TLGroup VERTICAL;
extern const TLGroup HORIZONTAL;

typedef struct {
    int state;
    int counter;
} Axis;

extern Axis AX_H;
extern Axis AX_V;

extern uint8_t DURATION[3];

void init_traffic_light(void);
void traffic_light_run(void);
void test_process_run();

void tl_set_color(const TLGroup* g, int color);
void apply_axis_lights(int is_horizontal, int state);
void axis_tick(Axis* ax, int is_horizontal);
#endif /* INC_TRAFFIC_LIGHT_H_ */
