/*
 * fsm.h
 *
 *  Created on: Oct 11, 2025
 *      Author: Lenovo
 */

#ifndef INC_FSM_H_
#define INC_FSM_H_

#include "traffic_light.h"

#define N0_OF_BUTTONS 3

// Các chỉ số nút bấm để dễ sử dụng
#define BTN1_IDX 0  // Chuyển chế độ
#define BTN2_IDX 1  // Tăng giá trị
#define BTN3_IDX 2  // Xác nhận giá trị

// Chế độ của hệ thống (bình thường và chỉnh sửa các LED)
typedef enum { MODE_NORMAL = 1, MODE_MOD_RED, MODE_MOD_AMB, MODE_MOD_GRN } Mode_t;

// Khai báo các hàm xử lý
void ui_tick_10ms(void);  // Hàm tạo nhịp 2 Hz, gọi mỗi 10ms/lần
void fsm_for_input_processing(void);  // Hàm xử lý các sự kiện từ nút bấm và chế độ

// Các hàm liên quan đến các nút bấm
uint8_t get_button_pressed_flag(uint8_t index); // Kiểm tra nút có được nhấn không
uint8_t is_button_pressed_1s(uint8_t index);    // Kiểm tra nút có bị giữ hơn 1 giây không

// Các hàm cập nhật và hiển thị trên 7-segment
void seg_show_mode_value(uint8_t mode, uint8_t value); // Hiển thị giá trị và chế độ trên 7-segment

#endif /* INC_FSM_H_ */
