#include "uart.h"
#include <stdint.h>
#include <stdio.h>

int main(void) {
  uart_init();
  while (1) {
    printf("Hello\r\n");
    for (int i = 0; i < 100000; i++) {
    }
  };
}