/*
 * button.c
 *
 *  Created on: Oct 11, 2025
 *      Author: Lenovo
 */
#include "button.h"
uint16_t BUTTON[COUNT_BUTTON] =
{
	GPIO_PIN_11,
	GPIO_PIN_12,
	GPIO_PIN_13

};
int KeyReg0[COUNT_BUTTON] = {NORMAL_STATE};
int KeyReg1[COUNT_BUTTON] = {NORMAL_STATE};
int KeyReg2[COUNT_BUTTON] = {NORMAL_STATE};
int KeyReg3[COUNT_BUTTON] = {NORMAL_STATE};
int TimerForKeyPress = 300;
int button_flag[COUNT_BUTTON] = {0};
void FlagKeyProcess(int index){
	button_flag[index] = 1;
}
void getKeyInput() {
	for(int i= 0; i<COUNT_BUTTON; i++){
		KeyReg0[i] = KeyReg1[i];
		KeyReg1[i] = KeyReg2[i];
		KeyReg2[i] = HAL_GPIO_ReadPin(GPIOA, BUTTON[i]);
		if((KeyReg0[i] == KeyReg1[i]) && (KeyReg1[i] == KeyReg2[i])){
			if(KeyReg3[i] != KeyReg2[i]){
				KeyReg2[i] = KeyReg3[i];
				if(KeyReg2[i] == PRESSED_STATE){
					FlagKeyProcess(i);
					TimerForKeyPress = 300;
				}
			}
			else{
				TimerForKeyPress--;
				if(TimerForKeyPress == 0){
					KeyReg3[i] = NORMAL_STATE;
				}
			}
		}
	}
}

