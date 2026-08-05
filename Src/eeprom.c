#include "eeprom.h"
#include "i2c.h"
#include <stdint.h>
#include <stdio.h>

Header eeprom_header;
uint32_t curr_date = 0x00050826; // TODO: change to actual rtc date

static void init_header() {
  const uint32_t dummy_date = 0x00050826; // TODO: change to actual rtc date
  const Header new_header = {dummy_date, EEPROM_START_ADDR, EEPROM_START_ADDR,
                             MAX_TASKS_COUNT};
  eeprom_write(EEPROM_HEADER_ADDR, sizeof(new_header), (char *)&new_header);
}
void eeprom_init() {
  char data[sizeof(Header)];
  i2c2_init();
  eeprom_rand_read(EEPROM_HEADER_ADDR, sizeof(Header), data);
  if (data[0] == 0xFFU) {
    init_header();
  }
  eeprom_header = *(Header *)data;
  if (eeprom_header.date_bcd != curr_date) {
    eeprom_header.today_addr = eeprom_header.last_addr;
    eeprom_header.date_bcd = curr_date;
    eeprom_write(EEPROM_HEADER_ADDR, sizeof(Header), (char *)&eeprom_header);
  }
}
void eeprom_rand_read(uint16_t addr, uint16_t n, char *data) {
  i2c2_read_16baddr(EEPROM_ADDR, addr, n, data);
}
void eeprom_write(uint16_t addr, uint16_t n, char *data) {
  while (n > 0) {
    uint16_t page_remaining = 64 - (addr & 0x3F);
    uint16_t chunk = (n < page_remaining) ? n : page_remaining;

    i2c2_write_16baddr(EEPROM_ADDR, addr, chunk, data);

    addr += chunk;
    data += chunk;
    n -= chunk;
  }
}