#ifndef EEPROM_H_
#define EEPROM_H_
#include <stdint.h>

// eeprom address needs to be << 1 with r/w bit
#define EEPROM_ADDR 0x50

void eeprom_init();
void eeprom_page_write(uint16_t addr, uint64_t page);
void eeprom_byte_write(uint16_t addr, char data);
void eeprom_rand_read(uint16_t addr, uint16_t n, char *data);
void eeprom_curr_addr_read(uint16_t n);

#endif // EEPROM_H_