#include "button.h"
#include "encoder.h"
#include "uart.h"
#include <stdint.h>
#include <stdio.h>

void encoder_loop(void);

bool btn_state;
bool enc_clk_last;
bool enc_clk_actual;
int main(void) {
  uart_init();
  button_init();
  encoder_init();
  enc_clk_last = encoder_clk_read();
  printf("Hello world\r\n");
  while (1) {
    btn_state = button_read();
    if (btn_state) {
      printf("Button pressed\r\n");
    }
    encoder_loop();
  };
}
void encoder_loop() {
  // encoder logic
  enc_clk_actual = encoder_clk_read();
  if (enc_clk_actual != enc_clk_last) {
    if (encoder_dt_read() != enc_clk_actual) {
      printf("Encoder++\r\n");
    } else {
      printf("Encoder--\r\n");
    }
    enc_clk_last = enc_clk_actual;
  };
}