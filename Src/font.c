#include "font.h"

#define DEFAULT_HEIGHT 7
#define SPACE_WIDTH 5
static const uint8_t c_32_cols[7] = {0x00}; // '0'
static const uint8_t c_48_cols[] = {0x0E, 0x11, 0x13, 0x15,
                                    0x19, 0x11, 0x0e}; // '0'

const Char font_kubasta_chars[] = {
    {' ', SPACE_WIDTH, DEFAULT_HEIGHT, 0, c_32_cols},
    {'0', 5, sizeof(c_48_cols), 0, c_48_cols}};

const Font font_kubasta = {1, font_kubasta_chars};