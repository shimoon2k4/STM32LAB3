/*
 * global.c
 *
 *  Created on: Oct 11, 2025
 *      Author: Lenovo
 */

#include <seven_segment.h>

int led_buffer[MAX_LED] = {1, 2, 3, 4};

char seg[10] =
{
		0x40,
		0x79,
		0x24,
		0x30,
		0x19,
		0x12,
		0x02,
		0x78,
		0x00,
		0x10
};
void clearAllState(){

}
void displayNumber(int is_horizontal,int number)
{
	if(is_horizontal == 1){
		HAL_GPIO_WritePin(GPIOB, SEG_A_HORIZONTAL_Pin, (seg[number] & 0x01) ? SET : RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_B_HORIZONTAL_Pin, (seg[number] & 0x02) ? SET : RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_C_HORIZONTAL_Pin, (seg[number] & 0x04) ? SET : RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_D_HORIZONTAL_Pin, (seg[number] & 0x08) ? SET : RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_E_HORIZONTAL_Pin, (seg[number] & 0x10) ? SET : RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_F_HORIZONTAL_Pin, (seg[number] & 0x20) ? SET : RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_G_HORIZONTAL_Pin, (seg[number] & 0x40) ? SET : RESET);
	}
	else{
		HAL_GPIO_WritePin(GPIOB, SEG_A_VERTICAL_Pin, (seg[number] & 0x01) ? SET : RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_B_VERTICAL_Pin, (seg[number] & 0x02) ? SET : RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_C_VERTICAL_Pin, (seg[number] & 0x04) ? SET : RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_D_VERTICAL_Pin, (seg[number] & 0x08) ? SET : RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_E_VERTICAL_Pin, (seg[number] & 0x10) ? SET : RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_F_VERTICAL_Pin, (seg[number] & 0x20) ? SET : RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_G_VERTICAL_Pin, (seg[number] & 0x40) ? SET : RESET);
	}
}
void updateClockBuffer(int num_vertical, int num_horizontal){
	led_buffer[0] = num_vertical/10;
	led_buffer[1] = num_vertical%10;
	led_buffer[2] = num_horizontal/10;
	led_buffer[3] = num_horizontal%10;
}

void update7SEG(int index){
	switch(index){
	case 1:
		displayNumber(0, led_buffer[0]);
		break;
	case 2:
		displayNumber(0, led_buffer[1]);
		break;
	case 3:
		displayNumber(1, led_buffer[2]);
		break;
	case 4:
		displayNumber(1, led_buffer[3]);
		break;
	default:
		break;
	}
}
void clearAllSignal(){
	HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, SET);
	HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, SET);
	HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, SET);
	HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, SET);
}
void changeSignaLedSegment(int signal){
	clearAllSignal();
switch(signal){
case 0:
	HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, RESET);
	HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, RESET);
	break;
case 1:
	HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, RESET);
	HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, RESET);
	break;
default:
	break;
}
}
void seg_show_mode_value(int mode, int value){
	if(mode == 1){
		return;
	}
	updateClockBuffer(mode, value);

}
void seg_scan_task(int timer_idx, int scan_period_ms){
    extern int  timer_flag[];
    extern void setTimer(int index, int duration);

    // Chuẩn hoá chu kỳ về bội số của TIMER_CYCLE (10 ms) để khớp timerRun()
    if (scan_period_ms < TIMER_CYCLE) scan_period_ms = TIMER_CYCLE;
    int period_norm = ((scan_period_ms + TIMER_CYCLE - 1) / TIMER_CYCLE) * TIMER_CYCLE;

    static uint8_t state = 0;  // 0: EN0&EN2 (digit 1 & 3), 1: EN1&EN3 (digit 2 & 4)

    if (timer_flag[timer_idx] == 1){
        switch (state){
            case 0:
                changeSignaLedSegment(0); // bật EN0 & EN2
                update7SEG(1);            // vertical tens
                update7SEG(3);            // horizontal tens
                break;
            case 1:
                changeSignaLedSegment(1); // bật EN1 & EN3
                update7SEG(2);            // vertical ones
                update7SEG(4);            // horizontal ones
                break;
            default:
                break;
        }

        state ^= 1;                 // đổi pha
        setTimer(timer_idx, period_norm); // nạp lại timer cho lần quét kế tiếp
    }
}

