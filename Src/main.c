#include "uart.h"
#include <stdint.h>

int main(void) {
  uart_open();
  while (1) {
    uart_write();
  };
};