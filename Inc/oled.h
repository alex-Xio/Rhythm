#ifndef OLED_H_
#define OLED_H_
#include <stdbool.h>

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

void oled_init();
void oled_on();
void oled_invertDisplay(bool i);

#endif // OLED_H_