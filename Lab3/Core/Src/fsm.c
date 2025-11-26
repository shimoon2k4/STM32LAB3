/*
 * fsm.c
 *
 *  Created on: Oct 11, 2025
 *      Author: Lenovo
 */

#include "fsm.h"

uint8_t redDur = 5, ambDur = 2, grnDur = 3;
uint8_t tem_redDur = 5, tem_ambDur = 2, tem_grnDur = 3;

// Chế độ hiển thị
static Mode_t mode = MODE_NORMAL;

// Biến điều khiển nhấp nháy LED (2 Hz)
#define TICK_MS 10
#define BLINK_TOGGLE_TICKS (250 / TICK_MS)
//static uint16_t blinkTick;
//static uint8_t blinkOn;

// Hàm chuyển đổi chế độ (Mode)
void clear_all_leds(void) {
    HAL_GPIO_WritePin(LED_RED_VERTICAL_GPIO_Port, LED_RED_VERTICAL_Pin, SET);
    HAL_GPIO_WritePin(LED_GREEN_VERTICAL_GPIO_Port, LED_GREEN_VERTICAL_Pin, SET);
    HAL_GPIO_WritePin(LED_YELLOW_VERTICAL_GPIO_Port, LED_YELLOW_VERTICAL_Pin, SET);
    HAL_GPIO_WritePin(LED_RED_HORIZONTAL_GPIO_Port, LED_RED_HORIZONTAL_Pin, SET);
    HAL_GPIO_WritePin(LED_GREEN_HORIZONTAL_GPIO_Port, LED_GREEN_HORIZONTAL_Pin, SET);
    HAL_GPIO_WritePin(LED_YELLOW_HORIZONTAL_GPIO_Port, LED_YELLOW_HORIZONTAL_Pin, SET);
}
static void cycle_mode(void) {
    mode = (mode == MODE_MOD_GRN) ? MODE_NORMAL : (Mode_t)(mode + 1);
    clear_all_leds();
    setTimer(2, 500);
}

// Hàm tăng giá trị (quay lại 1 nếu quá 99)
static void inc_wrap(uint8_t *v) {
    if (*v < 99) (*v)++;
    else *v = 1;
}

// Hàm hiển thị chế độ và giá trị trên LED 7 đoạn
static void render_mode2to4() {
    int val = 0;
    switch (mode) {
        case MODE_MOD_RED: val = tem_redDur; break;
        case MODE_MOD_AMB: val = tem_ambDur; break;
        case MODE_MOD_GRN: val = tem_grnDur; break;
        default: break;
    }
    // Hiển thị giá trị và chế độ
    seg_show_mode_value((int)mode, val);
}

// Hàm xử lý các sự kiện từ nút bấm và các chế độ
void fsm_for_input_processing(void) {
    // BTN1: chuyển chế độ
    if (get_button_pressed_flag(BTN1_IDX)) {
        cycle_mode();
//        if (mode == MODE_NORMAL) init_traffic_light();
    }
    if(mode == MODE_NORMAL){
    	test_process_run();
    	tem_redDur = redDur;
    	tem_ambDur = ambDur;
    	tem_grnDur = grnDur;
    }
//    if (mode == MODE_NORMAL) {
//        // Hiển thị thời gian còn lại cho cả 2 hướng (A và B) trên LED 7 đoạn
////    	traffic_light_run();
//        return;
//    }
    else {
            // Các Mode điều chỉnh (2, 3, 4): Xử lý nhấp nháy LED
            // Sử dụng Timer 1 (được định nghĩa trong main) cho việc nhấp nháy
            if (timer_flag[2] == 1) {
                // Reset timer: 25 ticks * 10ms = 250ms (Tần số 2Hz -> Đảo mỗi 250ms)
                setTimer(2, 500);

                switch (mode) {
                    case MODE_MOD_RED:
                        HAL_GPIO_TogglePin(LED_RED_VERTICAL_GPIO_Port, LED_RED_VERTICAL_Pin);
                        HAL_GPIO_TogglePin(LED_RED_HORIZONTAL_GPIO_Port, LED_RED_HORIZONTAL_Pin);
                        break;
                    case MODE_MOD_AMB:
                    	HAL_GPIO_TogglePin(LED_YELLOW_VERTICAL_GPIO_Port, LED_YELLOW_VERTICAL_Pin);
                    	HAL_GPIO_TogglePin(LED_YELLOW_HORIZONTAL_GPIO_Port, LED_YELLOW_HORIZONTAL_Pin);
                        break;
                    case MODE_MOD_GRN:
                    	HAL_GPIO_TogglePin(LED_GREEN_VERTICAL_GPIO_Port, LED_GREEN_VERTICAL_Pin);
                    	HAL_GPIO_TogglePin(LED_GREEN_HORIZONTAL_GPIO_Port, LED_GREEN_HORIZONTAL_Pin);
                        break;
                    default:
                        break;
                }
            }
        }
    // Chế độ 2–4: chỉnh thời gian cho LED đỏ, vàng, xanh
    if (get_button_pressed_flag(BTN2_IDX)) {
        if (mode == MODE_MOD_RED) inc_wrap(&tem_redDur);
        else if (mode == MODE_MOD_AMB) inc_wrap(&tem_ambDur);
        else if (mode == MODE_MOD_GRN) inc_wrap(&tem_grnDur);
    }

    // Auto-repeat nếu giữ BTN2 >1s (nhập nhanh)
    if (is_button_pressed_1s(BTN2_IDX)) {
        static uint8_t rep;
        if (++rep >= (100 / TICK_MS)) {  // Tăng mỗi 100ms khi giữ
            rep = 0;
            if (mode == MODE_MOD_RED) inc_wrap(&tem_redDur);
            else if (mode == MODE_MOD_AMB) inc_wrap(&tem_ambDur);
            else if (mode == MODE_MOD_GRN) inc_wrap(&tem_grnDur);
        }
    }

    // BTN3: xác nhận và set giá trị cho chế độ hiện tại
    if (get_button_pressed_flag(BTN3_IDX)) {
        // Có thể thêm nháy LED để báo "saved"
    	redDur = tem_redDur;
    	ambDur = tem_ambDur;
    	grnDur = tem_grnDur;
    	update_led_time(RED, redDur);
    	update_led_time(YELLOW, ambDur);
    	update_led_time(GREEN, grnDur);
    }

    // Hiển thị chế độ và giá trị trên LED 7 đoạn
    render_mode2to4();
    seg_scan_task(1, 500);
}
