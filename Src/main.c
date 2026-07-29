#include "button.h"
#include "encoder.h"
#include "uart.h"
#include <stdint.h>
#include <stdio.h>

#define LINE0 (1U << 0)
#define LINE1 (1U << 1)

void encoder_loop(void);

bool enc_clk_last;
bool enc_clk_actual;
int main(void) {
  uart_init();
  button_init();
  encoder_init();
  // enc_clk_last = encoder_clk_read();
  printf("Hello world\r\n");
  while (1) {
    // encoder_loop();
  };
}
void encoder_loop() {
  if (encoder_dt_read() != encoder_clk_read()) {
    printf("Encoder++\r\n");
  } else {
    printf("Encoder--\r\n");
  }
}

void EXTI0_IRQHandler() {
  if (EXTI->PR & LINE0) {
    EXTI->PR |= LINE0;
    printf("Button pressed\r\n");
  }
}
void EXTI1_IRQHandler() {
  if (EXTI->PR & LINE1) {
    EXTI->PR |= LINE1;
    encoder_loop();
  }
}