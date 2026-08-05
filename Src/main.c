#include "button.h"
#include "eeprom.h"
#include "encoder.h"
#include "i2c.h"
#include "oled.h"
#include "render.h"
#include "rtc.h"
#include "systick.h"
#include "tasks.h"
#include "uart.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define LINE0 (1U << 0)
#define LINE1 (1U << 1)

void encoder_loop(void);

bool enc_clk_last;
bool enc_clk_actual;
bool btn_flag;

int8_t encoder_change = 0;
void init() {
  uart_init();
  button_init();
  encoder_init();
  oled_init();
  eeprom_init();
  tasks_init();
  rtc_init();
  printf("Hello world\r\n");
}

int main(void) {
  // eeprom_init();
  // TaskList tsks = {8,
  //                  {{"1 Test", 1, 1},
  //                   {"2 Completions", 2, 2},
  //                   {"3 Completions", 3, 3},
  //                   {"test17characters_", 4, 4},
  //                   {"Test 5", 5, 1},
  //                   {"Test 6", 6, 2},
  //                   {"Test 7", 7, 3},
  //                   {"Test 8", 8, 4}}};
  // char data[0x7FFFU];
  // memset(data, 0xFF, sizeof(data));
  // eeprom_write(EEPROM_HEADER_ADDR, sizeof(data), data);
  // eeprom_write(EEPROM_TASKS_ADDR, sizeof(TaskList), (char *)&tsks);
  // for (int i = 0; i < 500000; i++) {
  // }
  init();
  assemble_frame();
  render();
  while (1) {
    if (encoder_change > 0) {
      NVIC_DisableIRQ(EXTI1_IRQn);
      while (encoder_change > 0) {
        next_task();
        encoder_change--;
      }
      NVIC_EnableIRQ(EXTI1_IRQn);
      reload_tasklist();
    } else if (encoder_change < 0) {
      NVIC_DisableIRQ(EXTI1_IRQn);
      while (encoder_change < 0) {
        prev_task();
        encoder_change++;
      }
      NVIC_EnableIRQ(EXTI1_IRQn);
      reload_tasklist();
    }
    if (btn_flag) {
      NVIC_DisableIRQ(EXTI0_IRQn);
      complete_active_task();
      reload_tasklist();
      btn_flag = 0;
      NVIC_EnableIRQ(EXTI0_IRQn);
    }
    if (is_ui_dirty()) {
      NVIC_DisableIRQ(EXTI1_IRQn);
      NVIC_DisableIRQ(EXTI0_IRQn);
      render();
      NVIC_EnableIRQ(EXTI0_IRQn);
      NVIC_EnableIRQ(EXTI1_IRQn);
    }
    if (is_record_dirty()) {
      NVIC_DisableIRQ(EXTI1_IRQn);
      NVIC_DisableIRQ(EXTI0_IRQn);
      update_record();
      NVIC_EnableIRQ(EXTI0_IRQn);
      NVIC_EnableIRQ(EXTI1_IRQn);
    }
  };
}
void encoder_loop() {
  if (encoder_dt_read() != encoder_clk_read()) {
    encoder_change++;
    printf("Encoder++\r\n");
  } else {
    printf("Encoder--\r\n");
    encoder_change--;
  }
}

void EXTI0_IRQHandler() {
  if (EXTI->PR & LINE0) {
    EXTI->PR |= LINE0;
    systick_init_50ms();
  }
}
void EXTI1_IRQHandler() {
  if (EXTI->PR & LINE1) {
    EXTI->PR |= LINE1;
    encoder_loop();
  }
}
void SysTick_Handler() {
  if (systick_count_flag()) {
    systick_disable();
    if (button_read()) {
      printf("Button pressed\r\n");
      btn_flag = true;
    }
  }
}