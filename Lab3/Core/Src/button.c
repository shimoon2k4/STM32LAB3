/*
 * button.c
 *
 *  Created on: Oct 11, 2025
 *      Author: Lenovo
 */
#include "button.h"
#ifndef BTN1_GPIO_Port
#define BTN1_GPIO_Port GPIOA
#define BTN1_Pin       GPIO_PIN_11
#define BTN2_GPIO_Port GPIOA
#define BTN2_Pin       GPIO_PIN_12
#define BTN3_GPIO_Port GPIOA
#define BTN3_Pin       GPIO_PIN_13
#endif

#define BUTTON_IS_PRESSED   GPIO_PIN_RESET
#define BUTTON_IS_RELEASED  GPIO_PIN_SET

#define DURATION_FOR_AUTO_INCREASING 100

static GPIO_TypeDef* BTN_PORT[N0_OF_BUTTONS] = {
  BTN1_GPIO_Port, BTN2_GPIO_Port, BTN3_GPIO_Port
};
static uint16_t BTN_PIN[N0_OF_BUTTONS] = {
  BTN1_Pin, BTN2_Pin, BTN3_Pin
};

// Khử dội (N=2 mẫu liên tiếp) + đệm kết quả ổn định
static GPIO_PinState debounce1[N0_OF_BUTTONS];
static GPIO_PinState debounce2[N0_OF_BUTTONS];
static GPIO_PinState stableBuf[N0_OF_BUTTONS];

// Edge flag: 1 khi chuyển từ RELEASED -> PRESSED
static uint8_t pressEdgeFlag[N0_OF_BUTTONS];

// Đếm & cờ giữ >1s
static uint16_t holdCounter1s[N0_OF_BUTTONS];
static uint8_t  holdFlag1s[N0_OF_BUTTONS];

void button_reading(void) {
  for (uint8_t i = 0; i < N0_OF_BUTTONS; i++) {
    debounce2[i] = debounce1[i];
    debounce1[i] = HAL_GPIO_ReadPin(BTN_PORT[i], BTN_PIN[i]);

    // Khử dội N=2
    if (debounce1[i] == debounce2[i]) {
      GPIO_PinState prev = stableBuf[i];
      stableBuf[i] = debounce1[i];

      // Phát hiện cạnh nhấn
      if (prev == BUTTON_IS_RELEASED && stableBuf[i] == BUTTON_IS_PRESSED) {
        pressEdgeFlag[i] = 1;
      }
    }

    // Xử lý giữ >1s
    if (stableBuf[i] == BUTTON_IS_PRESSED) {
      if (holdCounter1s[i] < DURATION_FOR_AUTO_INCREASING) {
        holdCounter1s[i]++;
      } else {
        holdFlag1s[i] = 1;
      }
    } else {
      holdCounter1s[i] = 0;
      holdFlag1s[i] = 0;
    }
  }
}

uint8_t is_button_pressed(uint8_t index) {
  if (index >= N0_OF_BUTTONS) return 0;
  return (stableBuf[index] == BUTTON_IS_PRESSED);
}

uint8_t get_button_pressed_flag(uint8_t index) {
  if (index >= N0_OF_BUTTONS) return 0;
  if (pressEdgeFlag[index]) {
    pressEdgeFlag[index] = 0;
    return 1;
  }
  return 0;
}

uint8_t is_button_pressed_1s(uint8_t index) {
  if (index >= N0_OF_BUTTONS) return 0;
  return holdFlag1s[index];
}
