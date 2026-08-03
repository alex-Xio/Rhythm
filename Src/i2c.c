#include "i2c.h"
#include "stm32f411xe.h"
#include <stdint.h>

#define TRISE_16MHz 17 // (16000000 / 1000000 + 1)

static void gpio_i2c1_init() {
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN_Msk;

  // PB8 alternate
  GPIOB->MODER &= ~(1U << 16);
  GPIOB->MODER |= (1U << 17);

  // PB9 alternate
  GPIOB->MODER &= ~(1U << 18);
  GPIOB->MODER |= (1U << 19);

  // open-drain
  GPIOB->OTYPER |= (1U << 8);
  GPIOB->OTYPER |= (1U << 9);

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
  /* for 100KHz
    TPCLK1 = 1/16MHz = 62.5 nanosec
    Thigh for 50% duty cycle = 1/(2*100KHz) = 5000 ns
    CCR = 5000/62.5 = 80
  */
  /* for 400KHz
    TPCLK1 = 1/16MHz = 62.5 nanosec
    Thigh for 50% duty cycle = 1/(2*400KHz) = 1250 ns
    CCR = 1250/62.5 = 20
  */
  I2C1->CCR = 20;
  I2C1->TRISE = TRISE_16MHz;

  I2C1->CR1 |= (1U << 0);
}

void i2c1_read(char saddr, char maddr, unsigned int n, char *data) {
  volatile uint32_t tmp;
  while (I2C1->SR2 & I2C_SR2_BUSY_Msk) {
  }
  I2C1->CR1 |= I2C_CR1_START_Msk;
  while (!(I2C1->SR1 & I2C_SR1_SB_Msk)) {
  }
  // saddr + W
  I2C1->DR = saddr << 1;
  while (!(I2C1->SR1 & I2C_SR1_ADDR_Msk)) {
  }

  // clear addr
  tmp = I2C1->SR2;

  while (!(I2C1->SR1 & I2C_SR1_TXE_Msk)) {
  }

  // maddr
  I2C1->DR = maddr;
  while (!(I2C1->SR1 & I2C_SR1_TXE_Msk)) {
  }

  I2C1->CR1 |= I2C_CR1_START_Msk;

  while (!(I2C1->SR1 & I2C_SR1_SB_Msk)) {
  }

  I2C1->DR = saddr << 1 | 1;

  while (!(I2C1->SR1 & (I2C_SR1_ADDR_Msk))) {
  }

  tmp = I2C1->SR2;

  I2C1->CR1 |= I2C_CR1_ACK_Msk;

  while (n > 0U) {
    if (n == 1U) {
      I2C1->CR1 &= ~I2C_CR1_ACK_Msk;

      I2C1->CR1 |= I2C_CR1_STOP_Msk;

      while (!(I2C1->SR1 & I2C_SR1_RXNE_Msk)) {
      }

      *data++ = I2C1->DR;
      break;
    } else {
      while (!(I2C1->SR1 & I2C_SR1_RXNE_Msk)) {
      }

      (*data++) = I2C1->DR;

      n--;
    }
  }
}
void i2c1_write(char saddr, char maddr, unsigned int n, char *data) {
  volatile uint32_t tmp;

  while (I2C1->SR2 & (I2C_SR2_BUSY_Msk)) {
  }

  I2C1->CR1 |= I2C_CR1_START_Msk;

  while (!(I2C1->SR1 & (I2C_SR1_SB_Msk))) {
  }

  I2C1->DR = saddr << 1;

  while (!(I2C1->SR1 & (I2C_SR1_ADDR_Msk))) {
  }

  // clear addr
  tmp = I2C1->SR2;

  while (!(I2C1->SR1 & (I2C_SR1_TXE_Msk))) {
  }

  I2C1->DR = maddr;

  for (unsigned int i = 0; i < n; i++) {

    while (!(I2C1->SR1 & (I2C_SR1_TXE_Msk))) {
    }

    I2C1->DR = *data++;
  }

  // transfer finished
  while (!(I2C1->SR1 & (I2C_SR1_BTF_Msk))) {
  }

  I2C1->CR1 |= I2C_CR1_STOP_Msk;
}

/**
PB3 - SDA
PB10 - SCL

*/
static void gpio_i2c2_init() {
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN_Msk;

  // PB3 alternate
  GPIOB->MODER &= ~(1U << 6);
  GPIOB->MODER |= (1U << 7);

  // PB10 alternate
  GPIOB->MODER &= ~(1U << 20);
  GPIOB->MODER |= (1U << 21);

  // open-drain
  GPIOB->OTYPER |= (1U << 3);
  GPIOB->OTYPER |= (1U << 10);

  // pull-ups
  GPIOB->PUPDR |= (1U << 6);
  GPIOB->PUPDR &= ~(1U << 7);

  GPIOB->PUPDR |= (1U << 20);
  GPIOB->PUPDR &= ~(1U << 21);

  // AF9
  GPIOB->AFR[0] |= (1U << 12);
  GPIOB->AFR[0] &= ~(1U << 13);
  GPIOB->AFR[0] &= ~(1U << 14);
  GPIOB->AFR[0] |= (1U << 15);

  GPIOB->AFR[1] |= (1U << 8);
  GPIOB->AFR[1] &= ~(1U << 9);
  GPIOB->AFR[1] &= ~(1U << 10);
  GPIOB->AFR[1] |= (1U << 11);
}

void i2c2_init() {
  gpio_i2c2_init();

  RCC->APB1ENR |= RCC_APB1ENR_I2C2EN_Msk;

  // reset
  I2C2->CR1 |= (1U << 15);
  I2C2->CR1 &= ~(1U << 15);

  // peripheral freq 16MHz
  I2C2->CR2 |= (1U << 4);

  I2C2->CCR = 20;
  I2C2->TRISE = TRISE_16MHz;

  I2C2->CR1 |= (1U << 0);
}

void i2c2_read(char saddr, char maddr, unsigned int n, char *data) {
  volatile uint32_t tmp;
  while (I2C2->SR2 & I2C_SR2_BUSY_Msk) {
  }
  I2C2->CR1 |= I2C_CR1_START_Msk;
  while (!(I2C2->SR1 & I2C_SR1_SB_Msk)) {
  }
  // saddr + W
  I2C2->DR = saddr << 1;
  while (!(I2C2->SR1 & I2C_SR1_ADDR_Msk)) {
  }

  // clear addr
  tmp = I2C2->SR2;

  while (!(I2C2->SR1 & I2C_SR1_TXE_Msk)) {
  }

  // maddr
  I2C2->DR = maddr;
  while (!(I2C2->SR1 & I2C_SR1_TXE_Msk)) {
  }

  I2C2->CR1 |= I2C_CR1_START_Msk;

  while (!(I2C2->SR1 & I2C_SR1_SB_Msk)) {
  }

  I2C2->DR = saddr << 1 | 1;

  while (!(I2C2->SR1 & (I2C_SR1_ADDR_Msk))) {
  }

  tmp = I2C2->SR2;

  I2C2->CR1 |= I2C_CR1_ACK_Msk;

  while (n > 0U) {
    if (n == 1U) {
      I2C2->CR1 &= ~I2C_CR1_ACK_Msk;

      I2C2->CR1 |= I2C_CR1_STOP_Msk;

      while (!(I2C2->SR1 & I2C_SR1_RXNE_Msk)) {
      }

      *data++ = I2C2->DR;
      break;
    } else {
      while (!(I2C2->SR1 & I2C_SR1_RXNE_Msk)) {
      }

      (*data++) = I2C2->DR;

      n--;
    }
  }
}
void i2c2_write(char saddr, char maddr, unsigned int n, char *data) {
  volatile uint32_t tmp;

  while (I2C2->SR2 & (I2C_SR2_BUSY_Msk)) {
  }

  I2C2->CR1 |= I2C_CR1_START_Msk;

  while (!(I2C2->SR1 & (I2C_SR1_SB_Msk))) {
  }

  I2C2->DR = saddr << 1;

  while (!(I2C2->SR1 & (I2C_SR1_ADDR_Msk))) {
  }

  // clear addr
  tmp = I2C2->SR2;

  while (!(I2C2->SR1 & (I2C_SR1_TXE_Msk))) {
  }

  I2C2->DR = maddr;

  for (unsigned int i = 0; i < n; i++) {

    while (!(I2C2->SR1 & (I2C_SR1_TXE_Msk))) {
    }

    I2C2->DR = *data++;
  }

  // transfer finished
  while (!(I2C2->SR1 & (I2C_SR1_BTF_Msk))) {
  }

  I2C2->CR1 |= I2C_CR1_STOP_Msk;
}
