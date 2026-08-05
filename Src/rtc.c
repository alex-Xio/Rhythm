#include "rtc.h"
#include "eeprom.h"
#include "stm32f411xe.h"
#include <stdbool.h>
#include <stdint.h>

#define RTC_ASYNCH_PREDIV ((uint32_t)0x7F)
#define RTC_SYNCH_PREDIV ((uint32_t)0x00F9)
#define RTC_INIT_Msk 0xFFFFFFFFU

static void test_datetime() {
  register uint32_t dt = 0;
  // year
  dt |= (0x26U << 16);
  // weekday
  dt |= (0x3U << 13);
  // month
  dt |= (0x8U << 8);
  // day
  dt |= (0x05U << 0);
  MODIFY_REG(RTC->DR,
             (RTC_DR_WDU | RTC_DR_MT | RTC_DR_MU | RTC_DR_DT | RTC_DR_DU |
              RTC_DR_YT | RTC_DR_YU),
             dt);

  register uint32_t tm = 0;
  // am/24
  tm &= ~(1U << 22);
  // hour
  tm |= (0x18U << 16);
  // minute
  tm |= (0x30U << 8);
  MODIFY_REG(RTC->TR,
             (RTC_TR_PM | RTC_TR_HT | RTC_TR_HU | RTC_TR_MNT | RTC_TR_MNU |
              RTC_TR_ST | RTC_TR_SU),
             tm);
}
void rtc_set_header() {
  char data[sizeof(Header)];
  eeprom_rand_read(EEPROM_HEADER_ADDR, sizeof(Header), data);
  Header header = *(Header *)data;
  header.time_set = true;
  eeprom_write(EEPROM_HEADER_ADDR, sizeof(Header), (char *)&header);
}

void rtc_init() {
  RCC->APB1ENR |= RCC_APB1ENR_PWREN_Msk;
  // backup power
  PWR->CR |= PWR_CR_DBP_Msk;

  RCC->CSR |= RCC_CSR_LSION_Msk;
  while (!(RCC->CSR & RCC_CSR_LSIRDY_Msk)) {
  }

  RCC->BDCR |= RCC_BDCR_BDRST_Msk;
  RCC->BDCR &= ~RCC_BDCR_BDRST_Msk;

  // lsi
  RCC->BDCR &= ~(1U << 8);
  RCC->BDCR |= (1U << 9);

  RCC->BDCR |= RCC_BDCR_RTCEN_Msk;

  // write prot
  RTC->WPR = (uint8_t)0xCAU;
  RTC->WPR = (uint8_t)0x53U;

  RTC->ISR = RTC_INIT_Msk;
  while (((RTC->ISR & RTC_ISR_INITF_Msk) == RTC_ISR_INITF_Msk)) {
  }

  test_datetime();

  RTC->CR |= RTC_CR_FMT_Msk;

  MODIFY_REG(RTC->PRER, RTC_PRER_PREDIV_A,
             RTC_ASYNCH_PREDIV << RTC_PRER_PREDIV_A_Pos);
  MODIFY_REG(RTC->PRER, RTC_PRER_PREDIV_S, RTC_SYNCH_PREDIV);

  RTC->ISR &= ~RTC_INIT_Msk;
  RTC->ISR &= ~RTC_ISR_RSF_Msk;
  while (((RTC->ISR & RTC_ISR_RSF_Msk) == RTC_ISR_RSF_Msk) != 1) {
  }

  RTC->WPR = 0xFF;
  rtc_set_header();
}