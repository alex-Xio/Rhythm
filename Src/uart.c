#include "uart.h"
#include "stm32f411xe.h"
#include <stdint.h>

#define USART_BRR_155200 (0x312U)
#define CR1_UE (1U << 13)
#define CR1_TE (1U << 3)
#define CR1_RE (1U << 2)
#define CR1_M (1U << 12)
#define SR_TXE (1U << 7)

void uart_open(void) {

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

  USART2->BRR |= USART_BRR_155200;

  USART2->CR1 |= CR1_TE;

  USART2->CR1 |= CR1_UE;
}

void uart_write(void) {
  while (!(USART2->SR & SR_TXE)) {
  }
  USART2->DR = ('A' & 0xFF);
}