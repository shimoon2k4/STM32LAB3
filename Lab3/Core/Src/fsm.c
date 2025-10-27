/*
 * fsm.c
 *
 *  Created on: Oct 11, 2025
 *      Author: Lenovo
 */

#include "fsm.h"

enum ButtonState { BUTTON_RELEASED, BUTTON_PRESSED, BUTTON_PRESSED_MORE_THAN_1_SECOND };
enum ButtonState buttonState = BUTTON_RELEASED;

// FSM để xử lý trạng thái của nút bấm
void fsm_for_input_processing(void) {
    switch (buttonState) {
        case BUTTON_RELEASED:
            if (is_button_pressed(0)) {
                buttonState = BUTTON_PRESSED;
                // Tăng giá trị của PORTA thêm 1
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);  // Ví dụ: bật LED tại PA0
            }
            break;
        case BUTTON_PRESSED:
            if (!is_button_pressed(0)) {
                buttonState = BUTTON_RELEASED;
            } else {
                if (is_button_pressed_1s(0)) {
                    buttonState = BUTTON_PRESSED_MORE_THAN_1_SECOND;
                }
            }
            break;
        case BUTTON_PRESSED_MORE_THAN_1_SECOND:
            if (!is_button_pressed(0)) {
                buttonState = BUTTON_RELEASED;
            }
            // Tăng giá trị PORTA mỗi 500ms nếu nút vẫn được nhấn
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_0);  // Ví dụ: thay đổi trạng thái LED tại PA0
            break;
    }
}
