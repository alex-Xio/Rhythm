#include "button.h"
#include "cmsis_gcc.h"

#define RCC_AHB2EN_SYSCFG (1U << 14)

void button_init() {
  __disable_irq();

  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN_Msk;

  // PA0 input
  GPIOA->MODER &= ~(1U << 0);
  GPIOA->MODER &= ~(1U << 1);

  // PA0 pull-up
  GPIOA->PUPDR |= (1U << 0);
  GPIOA->PUPDR &= ~(1U << 1);

  RCC->APB2ENR |= RCC_AHB2EN_SYSCFG;

  // PA0 EXTI enable
  SYSCFG->EXTICR[0] &= ~(1U << 0);
  SYSCFG->EXTICR[0] &= ~(1U << 1);
  SYSCFG->EXTICR[0] &= ~(1U << 2);
  SYSCFG->EXTICR[0] &= ~(1U << 3);

  // unmask
  EXTI->IMR |= EXTI_IMR_MR0_Msk;

  EXTI->FTSR |= EXTI_FTSR_TR0_Msk;
  EXTI->RTSR &= ~EXTI_RTSR_TR0_Msk;

  NVIC_EnableIRQ(EXTI0_IRQn);

  __enable_irq();
}

bool button_read() {
  if (GPIOA->IDR & (1U << 0)) {
    return false;
  }
  return true;
}