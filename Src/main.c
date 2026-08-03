#include "button.h"
#include "encoder.h"
#include "oled.h"
#include "render.h"
#include "stm32f411xe.h"
#include "systick.h"
#include "tasks.h"
#include "uart.h"
#include <stdint.h>
#include <stdio.h>

#define LINE0 (1U << 0)
#define LINE1 (1U << 1)

void encoder_loop(void);

bool enc_clk_last;
bool enc_clk_actual;

int8_t encoder_change = 0;

int main(void) {
  uart_init();
  button_init();
  encoder_init();
  oled_init();
  assemble_frame();
  render();

  printf("Hello world\r\n");
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
    if (is_ui_dirty()) {
      NVIC_DisableIRQ(EXTI1_IRQn);
      render();
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
    }
  }
}