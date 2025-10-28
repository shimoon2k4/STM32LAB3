/*
 * fsm.c
 *
 *  Created on: Oct 11, 2025
 *      Author: Lenovo
 */

#include "fsm.h"

uint8_t redDur = 5, ambDur = 2, grnDur = 3;

// Chế độ hiển thị
static Mode_t mode = MODE_NORMAL;

// Biến điều khiển nhấp nháy LED (2 Hz)
#define TICK_MS 10
#define BLINK_TOGGLE_TICKS (250 / TICK_MS)
//static uint16_t blinkTick;
//static uint8_t blinkOn;

// Hàm chuyển đổi chế độ (Mode)
static void cycle_mode(void) {
    mode = (mode == MODE_MOD_GRN) ? MODE_NORMAL : (Mode_t)(mode + 1);
}

// Hàm tăng giá trị (quay lại 1 nếu quá 99)
static void inc_wrap(uint8_t *v) {
    if (*v < 99) (*v)++;
    else *v = 1;
}

// Hàm hiển thị chế độ và giá trị trên LED 7 đoạn
static void render_mode2to4(void) {
    int val = 0;
    switch (mode) {
        case MODE_MOD_RED: val = redDur; break;
        case MODE_MOD_AMB: val = ambDur; break;
        case MODE_MOD_GRN: val = grnDur; break;
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
        if (mode == MODE_NORMAL) init_traffic_light(); // Quay lại chế độ bình thường và reset giao thông
    }

    if (mode == MODE_NORMAL) {
        // Hiển thị thời gian còn lại cho cả 2 hướng (A và B) trên LED 7 đoạn
    	traffic_light_run();
        return;
    }

    // Chế độ 2–4: chỉnh thời gian cho LED đỏ, vàng, xanh
    if (get_button_pressed_flag(BTN2_IDX)) {
        if (mode == MODE_MOD_RED) inc_wrap(&redDur);
        else if (mode == MODE_MOD_AMB) inc_wrap(&ambDur);
        else if (mode == MODE_MOD_GRN) inc_wrap(&grnDur);
    }

    // Auto-repeat nếu giữ BTN2 >1s (nhập nhanh)
    if (is_button_pressed_1s(BTN2_IDX)) {
        static uint8_t rep;
        if (++rep >= (100 / TICK_MS)) {  // Tăng mỗi 100ms khi giữ
            rep = 0;
            if (mode == MODE_MOD_RED) inc_wrap(&redDur);
            else if (mode == MODE_MOD_AMB) inc_wrap(&ambDur);
            else if (mode == MODE_MOD_GRN) inc_wrap(&grnDur);
        }
    }

    // BTN3: xác nhận và set giá trị cho chế độ hiện tại
    if (get_button_pressed_flag(BTN3_IDX)) {
        // Có thể thêm nháy LED để báo "saved"
    }

    // Hiển thị chế độ và giá trị trên LED 7 đoạn
    render_mode2to4();
}
