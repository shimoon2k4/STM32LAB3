/*
 * global.c
 *
 *  Created on: Oct 11, 2025
 *      Author: Lenovo
 */

#include "global.h"

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

void changeSignaLedSegment(){

}
