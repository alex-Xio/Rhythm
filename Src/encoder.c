#include "encoder.h"
#include <stdint.h>
/**
CLK -- PC1
DT -- PC0
 */

void encoder_init() {
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN_Msk;

  // PC0 input
  GPIOC->MODER &= ~(1U << 0);
  GPIOC->MODER &= ~(1U << 1);

  // PC0 pull-up
  GPIOC->PUPDR |= (1U << 0);
  GPIOC->PUPDR &= ~(1U << 1);

  // PC1 input
  GPIOC->MODER &= ~(1U << 2);
  GPIOC->MODER &= ~(1U << 3);

  // PC1 pull-up
  GPIOC->PUPDR |= (1U << 2);
  GPIOC->PUPDR &= ~(1U << 3);
}

bool encoder_clk_read(void) {
  if (GPIOC->IDR & (1U << 1)) {
    return false;
  }
  return true;
}
bool encoder_dt_read(void) {
  if (GPIOC->IDR & (1U << 0)) {
    return false;
  }
  return true;
}