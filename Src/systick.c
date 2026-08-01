#include "systick.h"
#include "stm32f411xe.h"

#define FIFTY_MS_LOAD 800000U
#define HUNDRED_MS_LOAD 1600000U
#define CTRL_CLKSRC (1U << 2)
#define CTRL_TICKINT (1U << 1)
#define CTRL_ENABLE (1U << 0)
#define CTRL_COUNTFLAG (1U << 16)

void systick_disable() { SysTick->CTRL &= ~CTRL_ENABLE; }
void systick_init_50ms() {
  SysTick->LOAD = FIFTY_MS_LOAD - 1U;

  SysTick->VAL = 0;

  SysTick->CTRL |= CTRL_CLKSRC;

  SysTick->CTRL |= CTRL_TICKINT;

  SysTick->CTRL |= CTRL_ENABLE;
}

void systick_init_100ms_noint() {
  SysTick->LOAD = HUNDRED_MS_LOAD - 1U;

  SysTick->VAL = 0;

  SysTick->CTRL |= CTRL_CLKSRC;

  SysTick->CTRL &= ~CTRL_TICKINT;

  SysTick->CTRL |= CTRL_ENABLE;
}

bool systick_count_flag() { return (SysTick->CTRL & CTRL_COUNTFLAG); }