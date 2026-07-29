#include "encoder.h"
#include <stdint.h>
/**
CLK -- PC1
DT -- PC0
 */

#define RCC_AHB2EN_SYSCFG (1U << 14)

void encoder_init() {
  __disable_irq();

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

  RCC->APB2ENR |= RCC_AHB2EN_SYSCFG;

  // PC1 EXTI enable
  SYSCFG->EXTICR[0] &= ~(1U << 4);
  SYSCFG->EXTICR[0] |= (1U << 5);
  SYSCFG->EXTICR[0] &= ~(1U << 6);
  SYSCFG->EXTICR[0] &= ~(1U << 7);
  // unmask
  EXTI->IMR |= EXTI_IMR_MR1_Msk;

  EXTI->FTSR |= EXTI_FTSR_TR1_Msk;
  EXTI->RTSR |= EXTI_RTSR_TR1_Msk;

  NVIC_EnableIRQ(EXTI1_IRQn);

  __enable_irq();
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