#include "button.h"

void button_init() {
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN_Msk;

  // PA0 input
  GPIOA->MODER &= ~(1U << 0);
  GPIOA->MODER &= ~(1U << 1);

  // PA0 pull-up
  GPIOA->PUPDR |= (1U << 0);
  GPIOA->PUPDR &= ~(1U << 1);
}

bool button_read() {
  if (GPIOA->IDR & (1U << 0)) {
    return false;
  }
  return true;
}