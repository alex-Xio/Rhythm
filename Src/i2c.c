#include "i2c.h"
#include "stm32f411xe.h"

#define TRISE_16MHz = (16000000 / 1000000 + 1);

static void gpio_i2c1_init() {
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN_Msk;

  // PB8 alternate
  GPIOB->MODER &= ~(1U << 16);
  GPIOB->MODER |= (1U << 17);

  // PB9 alternate
  GPIOB->MODER &= ~(1U << 18);
  GPIOB->MODER |= (1U << 19);

  // pull-ups
  GPIOB->PUPDR |= (1U << 16);
  GPIOB->PUPDR &= ~(1U << 17);

  GPIOB->PUPDR |= (1U << 18);
  GPIOB->PUPDR &= ~(1U << 19);

  // AF4
  GPIOB->AFR[1] &= ~(1U << 0);
  GPIOB->AFR[1] &= ~(1U << 1);
  GPIOB->AFR[1] |= (1U << 2);
  GPIOB->AFR[1] &= ~(1U << 3);

  GPIOB->AFR[1] &= ~(1U << 4);
  GPIOB->AFR[1] &= ~(1U << 5);
  GPIOB->AFR[1] |= (1U << 6);
  GPIOB->AFR[1] &= ~(1U << 7);
}

void i2c1_init() {
  gpio_i2c1_init();

  RCC->APB1ENR |= RCC_APB1ENR_I2C1EN_Msk;

  // reset
  I2C1->CR1 |= (1U << 15);
  I2C1->CR1 &= ~(1U << 15);

  // peripheral freq 16MHz
  I2C1->CR2 |= (1U << 4);
  /* for 100Hz
    TPCLK1 = 1/16MHz = 62.5 nanosec
    Thigh for 50% duty cycle = 1/(2*100KHz) = 5000 ns
    CCR = 5000/62.5 = 80
  */
  I2C1->CCR = 80;
  I2C1->TRISE = TRISE_16MHz;

  I2C1->CR1 |= (1U << 0);
}