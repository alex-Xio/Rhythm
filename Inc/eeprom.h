#ifndef EEPROM_H_
#define EEPROM_H_
#include "tasks.h"
#include <stdbool.h>
#include <stdint.h>

#define EEPROM_ADDR 0x50
#define EEPROM_HEADER_ADDR 0x00U
#define EEPROM_START_ADDR (0x00U + sizeof(Header))
#define EEPROM_TASKS_ADDR EEPROM_START_ADDR
#define EEPROM_COMPLETIONS_ADDR (EEPROM_TASKS_ADDR + sizeof(TaskList))

typedef struct {
  uint32_t date_bcd;
  uint16_t today_addr;
  uint16_t last_addr;
  bool time_set;
} Header;

void eeprom_init();
void eeprom_page_write(uint16_t addr, uint64_t page);
void eeprom_write(uint16_t addr, uint16_t n, char *data);
void eeprom_rand_read(uint16_t addr, uint16_t n, char *data);
void eeprom_curr_addr_read(uint16_t n);
Header get_header();

#endif // EEPROM_H_