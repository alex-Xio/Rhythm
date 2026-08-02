#ifndef FONT_H_
#define FONT_H_
#include <stdint.h>
#include <stdio.h>

typedef struct {
  char character;
  uint8_t width;
  int8_t voffset;
  const uint8_t *cols;
} Char;

typedef struct {
  uint8_t count;
  uint8_t height;
  const Char *chars;
} Font;

extern const Font font_kubasta;
extern const Font font_icons;

static inline const Char *font_find_glyph(const Font *font, char character) {
  for (uint8_t i = 0; i < font->count; i++) {
    if (font->chars[i].character == character) {
      return &font->chars[i];
    }
  }
  return NULL;
}

#endif // FONT_H_