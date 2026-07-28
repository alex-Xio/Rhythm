#include "button.h"
#include "uart.h"
#include <stdint.h>
#include <stdio.h>

bool btn_state;
int main(void) {
  uart_init();
  button_init();
  printf("Hello world\r\n");
  while (1) {
    btn_state = button_read();
    if (btn_state) {
      printf("Button pressed\r\n");
    } else {
      printf("Button unpressed\r\n");
    }
  };
}