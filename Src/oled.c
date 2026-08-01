#include "oled.h"
#include "i2c.h"
#include <stdint.h>

#define SIZE 128
#define SADDR 0x3C
#define OLED_NORMALDISPLAY 0xA6
#define OLED_INVERTDISPLAY 0xA7
#define OLED_DISPLAYON 0xAF

uint8_t framebuffer[(SIZE * SIZE) / 8];

static void oled_command(char c) {
  //   char buf[2] = {0x00, c}; // Co = 0, D/C = 0
  i2c1_write(SADDR, 0, 1, &c);
}

void oled_init() {
  i2c1_init();
  oled_command(0xAE);

  oled_command(0xd5);
  oled_command(0x51);

  oled_command(0x20);

  oled_command(0x81);
  oled_command(0x4f);

  oled_command(0xad);
  oled_command(0x8a);

  oled_command(0xa0);

  oled_command(0xc0);

  oled_command(0xdc);
  oled_command(0x00);

  oled_command(0xd3);
  oled_command(0x60);

  oled_command(0xd9);
  oled_command(0x22);

  oled_command(0xdb);
  oled_command(0x35);

  oled_command(0xa8);
  oled_command(0x3f);

  oled_command(0xa4);

  oled_command(0xa6);

  // 128x128
  oled_command(0xd3);
  oled_command(0x00);
  oled_command(0xa8);
  oled_command(0x7f);

  // on?
  oled_command(0xa5);
}

// static void oled_command_list(uint8_t c, uint8_t n) {
//   i2c1_write(SADDR, 0, n, (char *)c);
// }
void oled_on() { oled_command(OLED_DISPLAYON); }

void oled_invertDisplay(bool i) {
  oled_command(i ? OLED_INVERTDISPLAY : OLED_NORMALDISPLAY);
}