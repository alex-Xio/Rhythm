#include "oled.h"
#include "i2c.h"
#include "systick.h"
#include <stdint.h>
#include <string.h>

#define SIZE 128
#define SADDR 0x3C

uint8_t framebuffer[16][128];

static void oled_command(char c) { i2c1_write(SADDR, 0, 1, &c); }
static void oled_command_ram(char c) { i2c1_write(SADDR, 0x40, 1, &c); }

static void oled_command_list(char *c, uint8_t n) {
  i2c1_write(SADDR, 0, n, c);
}

void oled_set_cursor(uint8_t page, uint8_t col) {
  oled_command(0xb0 | (page & 0x0F));
  oled_command(0x00 | (col & 0x0F));
  oled_command(0x10 | ((col >> 4) & 0x0F));
}
static void set_pixel(uint8_t x, uint8_t y, bool color) {
  if ((x < SIZE) && (y < SIZE)) {
    uint8_t div = y / 8;
    uint8_t mod = y % 8;
    uint8_t num = (1U << mod);
    if (color) {
      framebuffer[div][x] |= num;
    } else {
      framebuffer[div][x] &= ~num;
    }
  }
}

void oled_display(void) {
  for (uint8_t page = 0; page < 16; page++) {
    oled_set_cursor(page, 0);
    for (uint8_t col = 0; col < 128; col++) {
      oled_command_ram(framebuffer[page][col]);
    }
  }
}

static char init[] = {OLED_OFF,
                      OLED_CLKDIVSET,
                      0xF1,
                      OLED_PAGEADDRMODE,
                      OLED_CONTRASTSET,
                      0x4f,
                      OLED_DCDC,
                      0x8a,
                      OLED_SEGREMAP,
                      OLED_COMSCANDIR,
                      OLED_DISPLAYSTARTLINE,
                      0x00,
                      OLED_OFFSET,
                      0x00,
                      OLED_PRECHARGE,
                      0x22,
                      OLED_VCOMDESMODESET,
                      0x35,
                      OLED_MPLEXRATIONSET,
                      0x7f,
                      OLED_ENTIREONDIS,
                      OLED_NORMALDISPLAY

};

void oled_init() {
  i2c1_init();
  memset(framebuffer, 0, sizeof(framebuffer));
  oled_command_list(init, sizeof(init));

  for (int i = 0; i < 128; i++) {
    if (i % 8 == 0 || i == 127) {
      set_pixel(0, i, true);
    }
  }
  for (int i = 0; i < 128; i++) {
    if (i % 8 == 0 || i == 127) {
      set_pixel(i, 0, true);
    }
  }
  set_pixel(64, 64, true);
  oled_display();

  oled_on();
  systick_init_100ms_noint();
  while (!systick_count_flag()) {
  }
  systick_disable();
}

void oled_on() { oled_command(OLED_ON); }

void oled_invertDisplay(bool i) {
  oled_command(i ? OLED_INVERTDISPLAY : OLED_NORMALDISPLAY);
}