#include "uart.h"
#include <stdint.h>

#define CR1_UE (1U << 13)
#define CR1_TE (1U << 3)
#define CR1_RE (1U << 2)
#define CR1_M (1U << 12)
#define SR_TXE (1U << 7)
#define PERIPH_CLK 16000000
#define BAUD_RATE 115200
// #define DEBUG_UART

static uint16_t compute_uart_bd(uint32_t periph_clk, uint32_t baudrate) {
  return ((periph_clk + (baudrate / 2U)) / baudrate);
}
static void uart_write(int);

int __io_putchar(int ch) {
#ifdef DEBUG_UART
  uart_write(ch);
#endif
  return ch;
}

void uart_init(void) {

  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN_Msk;

  // PA2 alternate
  GPIOA->MODER &= ~(1U << 4);
  GPIOA->MODER |= (1U << 5);

  // PA3 alternate
  GPIOA->MODER &= ~(1U << 6);
  GPIOA->MODER |= (1U << 7);

  GPIOA->AFR[0] |= (1U << 8);
  GPIOA->AFR[0] |= (1U << 9);
  GPIOA->AFR[0] |= (1U << 10);
  GPIOA->AFR[0] &= ~(1U << 11);

  GPIOA->AFR[0] |= (1U << 12);
  GPIOA->AFR[0] |= (1U << 13);
  GPIOA->AFR[0] |= (1U << 14);
  GPIOA->AFR[0] &= ~(1U << 15);

  RCC->APB1ENR |= RCC_APB1ENR_USART2EN_Msk;

  USART2->CR1 &= ~CR1_M;

  USART2->BRR = compute_uart_bd(PERIPH_CLK, BAUD_RATE);

  USART2->CR1 |= CR1_TE;

  USART2->CR1 |= CR1_UE;
}

static void uart_write(int ch) {
  while (!(USART2->SR & SR_TXE)) {
  }
  USART2->DR = (ch & 0xFF);
}
