#include "eeprom.h"
#include "i2c.h"

void eeprom_init() { i2c2_init(); }
void eeprom_rand_read(uint16_t addr, uint16_t n, char *data) {
  i2c2_read_16baddr(EEPROM_ADDR, addr, n, data);
}
void eeprom_byte_write(uint16_t addr, char data) {
  i2c2_bytewrite_16baddr(EEPROM_ADDR, addr, data);
}