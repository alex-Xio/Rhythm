#ifndef OLED_H_
#define OLED_H_
#include "font.h"
#include <stdbool.h>
#include <stdint.h>

#define OLED_PAGEADDRMODE 0x20
#define OLED_CONTRASTSET 0x81
#define OLED_MPLEXRATIONSET 0xA8
#define OLED_SEGREMAP 0xA0
#define OLED_ENTIREONEN 0xA5
#define OLED_ENTIREONDIS 0xA4
#define OLED_NORMALDISPLAY 0xA6
#define OLED_INVERTDISPLAY 0xA7
#define OLED_DCDC 0xAD
#define OLED_OFFSET 0xD3
#define OLED_CLKDIVSET 0xD5
#define OLED_PRECHARGE 0xD9
#define OLED_OFF 0xAE
#define OLED_ON 0xAF
#define OLED_COMSCANDIR 0xC0
#define OLED_DISPLAYSTARTLINE 0xDC
#define OLED_VCOMDESMODESET 0xDB
#define SIZE 128

void oled_init();
void oled_on();
void oled_invertDisplay(bool i);
bool is_in_bounds(uint8_t x, uint8_t y);
void set_pixel(uint8_t x, uint8_t y, bool color);
bool get_pixel(uint8_t x, uint8_t y);
void oled_drawchar(const Font *font, char character, uint8_t anchor_x,
                   uint8_t anchor_y, bool invert);
void oled_drawstr(const Font *font, char *s, uint8_t anchor_x, uint8_t anchor_y,
                  bool invert);

void oled_drawbox(uint8_t start_x, uint8_t start_y, uint8_t end_x,
                  uint8_t end_y, bool color);
void oled_display();
#endif // OLED_H_