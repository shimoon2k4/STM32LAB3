/*
 * button.h
 *
 *  Created on: Oct 11, 2025
 *      Author: Lenovo
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"

// Số nút
#define N0_OF_BUTTONS 3
// Chỉ số nút để đọc cho dễ nhớ
#define BTN1_IDX 0   // chọn/cycle mode
#define BTN2_IDX 1   // tăng giá trị
#define BTN3_IDX 2   // set/lưu

// Gọi mỗi 10 ms (trong callback TIM2)
void button_reading(void);

// Trạng thái tức thời đã khử dội (nhấn = 1)
uint8_t is_button_pressed(uint8_t index);

// Cờ “nhấn 1 lần” (rising-edge): đọc sẽ tự xóa
uint8_t get_button_pressed_flag(uint8_t index);

// Cờ “đang giữ >1s”: 1 khi giữ đủ, 0 khi thả
uint8_t is_button_pressed_1s(uint8_t index);

#endif /* INC_BUTTON_H_ */
