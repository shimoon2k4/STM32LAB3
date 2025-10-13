/*
 * global.c
 *
 *  Created on: Oct 11, 2025
 *      Author: Lenovo
 */

#include "global.h"

const int MAX_LED = 4;
int led_buffer[MAX_LED] = {0};

void clearAllState(){

}
void displayNumberStraight(int number)
{
	HAL_GPIO_WritePin(GPIOB, SEG_A_STRAIGHT_Pin, (seg[number] & 0x01) ? SET : RESET);
	HAL_GPIO_WritePin(GPIOB, SEG_B_STRAIGHT_Pin, (seg[number] & 0x02) ? SET : RESET);
	HAL_GPIO_WritePin(GPIOB, SEG_C_STRAIGHT_Pin, (seg[number] & 0x04) ? SET : RESET);
	HAL_GPIO_WritePin(GPIOB, SEG_D_STRAIGHT_Pin, (seg[number] & 0x08) ? SET : RESET);
	HAL_GPIO_WritePin(GPIOB, SEG_E_STRAIGHT_Pin, (seg[number] & 0x10) ? SET : RESET);
	HAL_GPIO_WritePin(GPIOB, SEG_F_STRAIGHT_Pin, (seg[number] & 0x20) ? SET : RESET);
	HAL_GPIO_WritePin(GPIOB, SEG_G_STRAIGHT_Pin, (seg[number] & 0x40) ? SET : RESET);
}
void displayHorizontal(int number)
{
	HAL_GPIO_WritePin(GPIOB, SEG_A_HORIZONTAL_Pin, (seg[number] & 0x01) ? SET : RESET);
	HAL_GPIO_WritePin(GPIOB, SEG_B_HORIZONTAL_Pin, (seg[number] & 0x02) ? SET : RESET);
	HAL_GPIO_WritePin(GPIOB, SEG_C_HORIZONTAL_Pin, (seg[number] & 0x04) ? SET : RESET);
	HAL_GPIO_WritePin(GPIOB, SEG_D_HORIZONTAL_Pin, (seg[number] & 0x08) ? SET : RESET);
	HAL_GPIO_WritePin(GPIOB, SEG_E_HORIZONTAL_Pin, (seg[number] & 0x10) ? SET : RESET);
	HAL_GPIO_WritePin(GPIOB, SEG_F_HORIZONTAL_Pin, (seg[number] & 0x20) ? SET : RESET);
	HAL_GPIO_WritePin(GPIOB, SEG_G_HORIZONTAL_Pin, (seg[number] & 0x40) ? SET : RESET);
}

void updateClockBuffer(int num_straight, int num_horizontal){
	led_buffer[0] = num_straight/10;
	led_buffer[1] = num_straight%10;
	led_buffer[2] = num_horizontal/10;
	led_buffer[3] = num_horizontal%10;
}

void update7SEG(int index){
	switch(index){
	case 1:
		displayNumberStraight(led_buffer[0]);
		break;
	case 2:
		displayNumberStraight(led_buffer[1]);
		break;
	case 3:
		displayHorizontal(led_buffer[2]);
		break;
	case 4:
		displayHorizontal(led_buffer[3]);
		break;
	default:
		break;
	}
}

void changeSignaLedSegment(int signal){
switch(signal){
case 0:
	HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, RESET);
	HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, SET);
	HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, SET);
	HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, SET);
	break;
case 1:
	HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, SET);
	HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, RESET);
	HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, SET);
	HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, SET);
	break;
case 2:
	HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, SET);
	HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, SET);
	HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, RESET);
	HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, SET);
	break;
case 3:
	HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, SET);
	HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, SET);
	HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, SET);
	HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, RESET);
	break;
default:
	return;
	break;
}
}

