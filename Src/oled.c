#include "oled.h"
#include "font.h"
#include "i2c.h"
#include "systick.h"
#include "tasks.h"
#include <stdint.h>
#include <string.h>

#define SIZE 128
#define SADDR 0x3C
#define LETTER_SPACE_PX 1
#define TASK_PADDING 5

uint8_t framebuffer[16][128];

uint8_t tasks_offset = 0;
uint8_t active_task_i = 0;

static void oled_command(char c) { i2c1_write(SADDR, 0, 1, &c); }
static void oled_command_ram(char c) { i2c1_write(SADDR, 0x40, 1, &c); }

static void oled_command_list(char *c, uint8_t n) {
  i2c1_write(SADDR, 0, n, c);
}

static bool is_in_bounds(uint8_t x, uint8_t y) {
  return ((x < SIZE) && (y < SIZE));
}
void oled_set_cursor(uint8_t page, uint8_t col) {
  oled_command(0xb0 | (page & 0x0F));
  oled_command(0x00 | (col & 0x0F));
  oled_command(0x10 | ((col >> 4) & 0x0F));
}
static void set_pixel(uint8_t x, uint8_t y, bool color) {
  if (is_in_bounds(x, y)) {
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
static bool get_pixel(uint8_t x, uint8_t y) {
  if (!is_in_bounds(x, y)) {
    return false;
  }
  uint8_t div = y / 8;
  uint8_t mod = y % 8;
  uint8_t num = (1U << mod);
  return framebuffer[div][x] & num;
}

static void oled_drawchar(const Font *font, char character, uint8_t anchor_x,
                          uint8_t anchor_y, bool invert) {
  const Char *font_char = font_find_glyph(font, character);
  if (font_char == NULL) {
    return;
  }
  anchor_y += font_char->voffset;
  if (!is_in_bounds(anchor_x, anchor_y) ||
      !is_in_bounds(anchor_x + font_char->width - 1,
                    anchor_y + font->height - 1)) {
    return;
  }
  for (int i = 0; i < font->height; i++) {
    for (int j = 0; j < font_char->width; j++) {
      if (invert) {
        if (get_pixel(anchor_x + j, anchor_y + i)) {
          bool color = font_char->cols[i] & (1U << (font_char->width - 1 - j));
          set_pixel(anchor_x + j, anchor_y + i, !color);
        }
      } else {
        if (!get_pixel(anchor_x + j, anchor_y + i)) {
          bool color = font_char->cols[i] & (1U << (font_char->width - 1 - j));
          set_pixel(anchor_x + j, anchor_y + i, color);
        }
      }
    }
  }
  // set_pixel(anchor_x, anchor_y, true);
}

static void oled_drawstr(const Font *font, char *s, uint8_t anchor_x,
                         uint8_t anchor_y, bool invert) {
  int i = 0;
  while (s[i] != '\0') {
    const Char *font_char = font_find_glyph(font, s[i]);
    if (font_char == NULL) {
      return;
    }
    if (!is_in_bounds(anchor_x, anchor_y) ||
        !is_in_bounds(anchor_x + font_char->width - 1,
                      anchor_y + font->height - 1)) {
      return;
    }
    oled_drawchar(font, s[i], anchor_x, anchor_y, invert);
    anchor_x += font_char->width + LETTER_SPACE_PX;
    i++;
  }
}
static void oled_drawbox(uint8_t start_x, uint8_t start_y, uint8_t end_x,
                         uint8_t end_y, bool color) {
  for (int i = start_y; i < end_y; i++) {
    for (int j = start_x; j < end_x; j++) {
      set_pixel(j, i, color);
    }
  }
}

static void oled_drawtask(uint8_t y_start, Task task, bool is_active) {
  oled_drawbox(0, y_start, 128, y_start + (TASK_PADDING * 2) + 7, is_active);
  oled_drawstr(&font_kubasta, task.name, TASK_PADDING, y_start + TASK_PADDING,
               is_active);
  oled_drawchar(&font_icons, '0', SIZE - 7 - TASK_PADDING,
                y_start + TASK_PADDING, is_active);
}
static void oled_drawtasklist(Task *tasks, uint8_t y_start, uint8_t n,
                              uint8_t offset) {
  for (int i = 0; i < n; i++) {
    oled_drawtask(y_start + TASK_PADDING, tasks[i], i == active_task_i);
    y_start += (TASK_PADDING * 2) + 8;
  }
}

static void oled_setstatbar() {
  for (int i = 0; i < 128; i++) {
    set_pixel(i, 10, true);
  }
  oled_drawstr(&font_kubasta, "Rhythm", 0, 0, false);
}
static void oled_settitle() {
  oled_drawstr(&font_kubasta, "TODAY", 0, 16, false);
}
static void assemble_frame() {
  oled_setstatbar();
  oled_settitle();
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
  oled_display();

  oled_on();
  systick_init_100ms_noint();
  while (!systick_count_flag()) {
  }
  systick_disable();

  assemble_frame();
  oled_drawtasklist(get_tasks(), 20, 5, 0);
  oled_display();
}

void oled_on() { oled_command(OLED_ON); }

void oled_invertDisplay(bool i) {
  oled_command(i ? OLED_INVERTDISPLAY : OLED_NORMALDISPLAY);
}