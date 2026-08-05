#include "font.h"
#include <stdint.h>

#define DEFAULT_HEIGHT 7
#define SPACE_WIDTH 5
static const uint16_t c_32_cols[7] = {0x00}; // ' ' (SP)
static const uint16_t c_33_cols[] = {0x01, 0x01, 0x01, 0x01,
                                     0x01, 0x00, 0x01}; // '!'
static const uint16_t c_34_cols[] = {0x05, 0x05, 0x05, 0x00,
                                     0x00, 0x00, 0x00}; // '"'
static const uint16_t c_35_cols[] = {0x08, 0x0A, 0x1F, 0x0A,
                                     0x1F, 0x0A, 0x02}; // '#'

static const uint16_t c_36_cols[] = {0x04, 0x0f, 0x14, 0x0e,
                                     0x05, 0x1e, 0x04}; // '$'
static const uint16_t c_37_cols[] = {0x19, 0x19, 0x02, 0x04,
                                     0x08, 0x13, 0x13}; // '%'
static const uint16_t c_38_cols[] = {0x0c, 0x12, 0x12, 0x08,
                                     0x15, 0x12, 0x0d}; // '&'
static const uint16_t c_39_cols[] = {0x01, 0x01, 0x00, 0x00,
                                     0x00, 0x00, 0x00}; // '''
static const uint16_t c_40_cols[] = {0x03, 0x04, 0x08, 0x08,
                                     0x08, 0x04, 0x03}; // '('
static const uint16_t c_41_cols[] = {0x0c, 0x02, 0x01, 0x01,
                                     0x01, 0x02, 0x0c}; // ')'
static const uint16_t c_42_cols[] = {0x00, 0x04, 0x15, 0x0e,
                                     0x15, 0x04, 0x00}; // '*'
static const uint16_t c_43_cols[] = {0x00, 0x04, 0x04, 0x1f,
                                     0x04, 0x04, 0x00}; // '+'
static const uint16_t c_44_cols[] = {0x00, 0x00, 0x00, 0x03,
                                     0x03, 0x01, 0x02}; // ','
static const uint16_t c_45_cols[] = {0x00, 0x00, 0x00, 0x1f,
                                     0x00, 0x00, 0x00}; // '-'
static const uint16_t c_46_cols[] = {0x00, 0x00, 0x00, 0x00,
                                     0x00, 0x03, 0x03}; // '.'
static const uint16_t c_47_cols[] = {0x01, 0x01, 0x02, 0x02,
                                     0x02, 0x04, 0x04}; // '/'
static const uint16_t c_48_cols[] = {0x0E, 0x11, 0x13, 0x15,
                                     0x19, 0x11, 0x0e}; // '0'
static const uint16_t c_49_cols[] = {0x04, 0x0c, 0x14, 0x04,
                                     0x04, 0x04, 0x1F}; // '1'
static const uint16_t c_50_cols[] = {0x0E, 0x11, 0x01, 0x02,
                                     0x04, 0x08, 0x1F}; // '2'
static const uint16_t c_51_cols[] = {0x1F, 0x02, 0x04, 0x0e,
                                     0x01, 0x11, 0x0e}; // '3'
static const uint16_t c_52_cols[] = {0x02, 0x04, 0x08, 0x12,
                                     0x1F, 0x02, 0x02}; // '4'
static const uint16_t c_53_cols[] = {0x1f, 0x10, 0x10, 0x1e,
                                     0x01, 0x11, 0x0e}; // '5'
static const uint16_t c_54_cols[] = {0x06, 0x08, 0x10, 0x1E,
                                     0x11, 0x11, 0x0e}; // '6'
static const uint16_t c_55_cols[] = {0x1F, 0x01, 0x01, 0x02,
                                     0x02, 0x04, 0x04}; // '7'
static const uint16_t c_56_cols[] = {0x0e, 0x11, 0x11, 0x0e,
                                     0x11, 0x11, 0x0e}; // '8'
static const uint16_t c_57_cols[] = {0x0e, 0x11, 0x11, 0x0f,
                                     0x01, 0x02, 0x0c}; // '9'
static const uint16_t c_58_cols[] = {0x00, 0x03, 0x03, 0x00,
                                     0x03, 0x03, 0x00}; // ':'
static const uint16_t c_59_cols[] = {0x03, 0x03, 0x00, 0x03,
                                     0x03, 0x01, 0x02}; // ';'
static const uint16_t c_60_cols[] = {0x00, 0x03, 0x0c, 0x10,
                                     0x0C, 0x03, 0x00}; // '<'
static const uint16_t c_61_cols[] = {0x00, 0x00, 0x07, 0x00,
                                     0x07, 0x00, 0x00}; // '='
static const uint16_t c_62_cols[] = {0x00, 0x18, 0x06, 0x01,
                                     0x06, 0x18, 0x00}; // '>'
static const uint16_t c_63_cols[] = {0x0e, 0x11, 0x01, 0x02,
                                     0x04, 0x00, 0x04}; // '?'
static const uint16_t c_64_cols[] = {0x0f, 0x11, 0x17, 0x15,
                                     0x17, 0x10, 0x0f}; // '@'
static const uint16_t c_65_cols[] = {0xe,  0x11, 0x11, 0x1f,
                                     0x11, 0x11, 0x11}; // 'A'
static const uint16_t c_66_cols[] = {0x1c, 0x12, 0x12, 0x1e,
                                     0x11, 0x11, 0x1e}; // 'B'
static const uint16_t c_67_cols[] = {0x0e, 0x11, 0x10, 0x10,
                                     0x10, 0x10, 0x0F}; // 'C'
static const uint16_t c_68_cols[] = {0x1C, 0x12, 0x11, 0x11,
                                     0x11, 0x12, 0x1C}; // 'D'
static const uint16_t c_69_cols[] = {0x1f, 0x10, 0x10, 0x1e,
                                     0x10, 0x10, 0x1f}; // 'E'
static const uint16_t c_70_cols[] = {0x1f, 0x10, 0x10, 0x1e,
                                     0x10, 0x10, 0x10}; // 'F'
static const uint16_t c_71_cols[] = {0x0e, 0x11, 0x10, 0x17,
                                     0x11, 0x11, 0x0f}; // 'G'
static const uint16_t c_72_cols[] = {0x11, 0x11, 0x11, 0x1f,
                                     0x11, 0x11, 0x11}; // 'H'
static const uint16_t c_73_cols[] = {0x1f, 0x04, 0x04, 0x04,
                                     0x04, 0x04, 0x1f}; // 'I'
static const uint16_t c_74_cols[] = {0x1f, 0x01, 0x01, 0x01,
                                     0x01, 0x11, 0x0E}; // 'J'
static const uint16_t c_75_cols[] = {0x11, 0x12, 0x14, 0x1A,
                                     0x11, 0x11, 0x11}; // 'K'
static const uint16_t c_76_cols[] = {0x10, 0x10, 0x10, 0x10,
                                     0x10, 0x10, 0x1f}; // 'L'
static const uint16_t c_77_cols[] = {0x11, 0x1B, 0x15, 0x15,
                                     0x11, 0x11, 0x11}; // 'M'
static const uint16_t c_78_cols[] = {0x11, 0x11, 0x19, 0x15,
                                     0x13, 0x11, 0x11}; // 'N'
static const uint16_t c_79_cols[] = {0x0e, 0x11, 0x11, 0x11,
                                     0x11, 0x11, 0x0e}; // 'O'
static const uint16_t c_80_cols[] = {0x1E, 0x11, 0x11, 0x1E,
                                     0x10, 0x10, 0x10}; // 'P'
static const uint16_t c_81_cols[] = {0x0e, 0x11, 0x11, 0x11,
                                     0x15, 0x12, 0x0d}; // 'Q'
static const uint16_t c_82_cols[] = {0x1e, 0x11, 0x11, 0x1e,
                                     0x12, 0x11, 0x11}; // 'R'
static const uint16_t c_83_cols[] = {0x0e, 0x11, 0x10, 0x0e,
                                     0x01, 0x11, 0x0e}; // 'S'
static const uint16_t c_84_cols[] = {0x1F, 0x04, 0x04, 0x04,
                                     0x04, 0x04, 0x04}; // 'T'
static const uint16_t c_85_cols[] = {0x11, 0x11, 0x11, 0x11,
                                     0x11, 0x13, 0x0d}; // 'U'
static const uint16_t c_86_cols[] = {0x11, 0x11, 0x11, 0x0A,
                                     0x0A, 0x0A, 0x04}; // 'V'
static const uint16_t c_87_cols[] = {0x11, 0x11, 0x15, 0x15,
                                     0x15, 0x0a, 0x0a}; // 'W'
static const uint16_t c_88_cols[] = {0x11, 0x11, 0x0a, 0x04,
                                     0x0a, 0x11, 0x11}; // 'X'
static const uint16_t c_89_cols[] = {0x11, 0x11, 0x11, 0x0a,
                                     0x04, 0x04, 0x04}; // 'Y'
static const uint16_t c_90_cols[] = {0x1f, 0x01, 0x02, 0x04,
                                     0x08, 0x10, 0x1F}; // 'Z'
static const uint16_t c_91_cols[] = {0x0f, 0x08, 0x08, 0x08,
                                     0x08, 0x08, 0x0f}; // '['
static const uint16_t c_92_cols[] = {0x04, 0x04, 0x02, 0x02,
                                     0x02, 0x01, 0x01}; // '\'
static const uint16_t c_93_cols[] = {0x0f, 0x01, 0x01, 0x01,
                                     0x01, 0x01, 0x0f}; // ']'
static const uint16_t c_94_cols[] = {0x04, 0x0a, 0x11, 0x00,
                                     0x00, 0x00, 0x00}; // '^'
static const uint16_t c_95_cols[] = {0x00, 0x00, 0x00, 0x00,
                                     0x00, 0x00, 0x1f}; // '_'
static const uint16_t c_96_cols[] = {0x06, 0x01, 0x00, 0x00,
                                     0x00, 0x00, 0x00}; // '`'

static const uint16_t c_97_cols[] = {0x00, 0x00, 0x0f, 0x11,
                                     0x11, 0x13, 0x0d}; // 'a'
static const uint16_t c_98_cols[] = {0x10, 0x10, 0x16, 0x19,
                                     0x11, 0x11, 0x1e}; // 'b'
static const uint16_t c_99_cols[] = {0x00, 0x00, 0x0e, 0x11,
                                     0x10, 0x10, 0x0f}; // 'c'
static const uint16_t c_100_cols[] = {0x01, 0x01, 0x0f, 0x11,
                                      0x11, 0x13, 0x0d}; // 'd'
static const uint16_t c_101_cols[] = {0x00, 0x00, 0x0e, 0x11,
                                      0x1f, 0x10, 0x0f}; // 'e'
static const uint16_t c_102_cols[] = {0x06, 0x09, 0x08, 0x1e,
                                      0x08, 0x08, 0x08}; // 'f'
static const uint16_t c_103_cols[] = {0x0f, 0x11, 0x11, 0x0f,
                                      0x01, 0x11, 0x0e}; // 'g'
static const uint16_t c_104_cols[] = {0x10, 0x10, 0x16, 0x19,
                                      0x11, 0x11, 0x11}; // 'h'
static const uint16_t c_105_cols[] = {0x04, 0x00, 0x1C, 0x04,
                                      0x04, 0x04, 0x1F}; // 'i'
static const uint16_t c_106_cols[] = {0x01, 0x00, 0x07, 0x01,
                                      0x01, 0x11, 0x0e}; // 'j'
static const uint16_t c_107_cols[] = {0x10, 0x10, 0x13, 0x14,
                                      0x1a, 0x11, 0x11}; // 'k'
static const uint16_t c_108_cols[] = {0x18, 0x08, 0x08, 0x08,
                                      0x08, 0x09, 0x06}; // 'l'
static const uint16_t c_109_cols[] = {0x00, 0x00, 0x1a, 0x15,
                                      0x15, 0x15, 0x15}; // 'm'
static const uint16_t c_110_cols[] = {0x00, 0x00, 0x16, 0x19,
                                      0x11, 0x11, 0x11}; // 'n'
static const uint16_t c_111_cols[] = {0x00, 0x00, 0x0e, 0x11,
                                      0x11, 0x11, 0x0e}; // 'o'
static const uint16_t c_112_cols[] = {0x16, 0x19, 0x11, 0x11,
                                      0x1e, 0x10, 0x10}; // 'p'
static const uint16_t c_113_cols[] = {0x0f, 0x11, 0x11, 0x13,
                                      0x0d, 0x01, 0x01}; // 'q'
static const uint16_t c_114_cols[] = {0x00, 0x00, 0x16, 0x19,
                                      0x10, 0x10, 0x10}; // 'r'
static const uint16_t c_115_cols[] = {0x00, 0x00, 0x0f, 0x10,
                                      0x0e, 0x01, 0x1e}; // 's'
static const uint16_t c_116_cols[] = {0x08, 0x08, 0x1e, 0x08,
                                      0x08, 0x09, 0x06}; // 't'
static const uint16_t c_117_cols[] = {0x00, 0x00, 0x11, 0x11,
                                      0x11, 0x13, 0x0d}; // 'u'
static const uint16_t c_118_cols[] = {0x00, 0x00, 0x11, 0x11,
                                      0x0a, 0x0a, 0x04}; // 'v'
static const uint16_t c_119_cols[] = {0x00, 0x00, 0x11, 0x15,
                                      0x15, 0x0a, 0x0a}; // 'w'
static const uint16_t c_120_cols[] = {0x00, 0x00, 0x11, 0x0a,
                                      0x04, 0x0a, 0x11}; // 'x'
static const uint16_t c_121_cols[] = {0x11, 0x11, 0x13, 0x0d,
                                      0x01, 0x11, 0x0e}; // 'y'
static const uint16_t c_122_cols[] = {0x00, 0x00, 0x1F, 0x02,
                                      0x04, 0x08, 0x1F}; // 'z'

static const uint16_t c_123_cols[] = {0x03, 0x04, 0x04, 0x08,
                                      0x04, 0x04, 0x03}; // '{'
static const uint16_t c_124_cols[] = {0x01, 0x01, 0x01, 0x01,
                                      0x01, 0x01, 0x01}; // '|'
static const uint16_t c_125_cols[] = {0x0c, 0x02, 0x02, 0x01,
                                      0x02, 0x02, 0x0c}; // '}'
static const uint16_t c_126_cols[] = {0x09, 0x15, 0x12, 0x00,
                                      0x00, 0x00, 0x00}; // '~'

// static const uint16_t i_cog_cols[] = {0x10, 0x1C, 0x1F, 0x36, 0x7E, 0x1C,
// 0x04}; static const uint16_t i_mus_cols[] = {0x3f, 0x21, 0x21, 0x021, 0x21,
// 0x63, 0x63}; static const uint16_t i_box1_cols[] = {0x7f, 0x41, 0x41, 0x41,
// 0x41, 0x41, 0x7f}; static const uint16_t i_box2_cols[] = {0x7f, 0x55, 0x6b,
// 0x55, 0x6b, 0x55, 0x7f}; static const uint16_t i_box3_cols[] = {0x7f, 0x7f,
// 0x7f, 0x7f, 0x7f, 0x7f, 0x7f};
static const uint16_t i_box1_cols[] = {0x7FF, 0x401, 0x401, 0x401, 0x401, 0x401,
                                       0x401, 0x401, 0x401, 0x401, 0x7FF};
static const uint16_t i_box2_cols[] = {0x7FF, 0x555, 0x6AB, 0x555, 0x6AB, 0x555,
                                       0x6AB, 0x555, 0x6AB, 0x555, 0x7FF};
static const uint16_t i_box3_cols[] = {0x7ff, 0x7FF, 0x7FF, 0x7FF, 0x7FF, 0x7FF,
                                       0x7FF, 0x7FF, 0x7FF, 0x7FF, 0x7FF};

const Char font_kubasta_chars[] = {
    {' ', SPACE_WIDTH, 0, c_32_cols}, {'!', 1, 0, c_33_cols},
    {'"', 3, 0, c_34_cols},           {'#', 5, 0, c_35_cols},

    {'$', 5, 0, c_36_cols},           {'%', 5, 0, c_37_cols},
    {'&', 5, 0, c_38_cols},           {'\'', 5, 0, c_39_cols},

    {'(', 4, 0, c_40_cols},           {')', 4, 0, c_41_cols},
    {'*', 5, 0, c_42_cols},           {'+', 5, 0, c_43_cols},
    {',', 2, 2, c_44_cols},           {'-', 5, 0, c_45_cols},
    {'.', 2, 0, c_46_cols},           {'/', 3, 0, c_47_cols},
    {'0', 5, 0, c_48_cols},           {'1', 5, 0, c_49_cols},
    {'2', 5, 0, c_50_cols},           {'3', 5, 0, c_51_cols},
    {'3', 5, 0, c_51_cols},           {'4', 5, 0, c_52_cols},
    {'5', 5, 0, c_53_cols},           {'6', 5, 0, c_54_cols},
    {'7', 5, 0, c_55_cols},           {'8', 5, 0, c_56_cols},
    {'9', 5, 0, c_57_cols},           {':', 2, 0, c_58_cols},
    {';', 2, 1, c_59_cols},           {'<', 5, 0, c_60_cols},
    {'=', 3, 0, c_61_cols},           {'>', 5, 0, c_62_cols},
    {'?', 5, 0, c_63_cols},           {'@', 5, 0, c_64_cols},
    {'A', 5, 0, c_65_cols},           {'B', 5, 0, c_66_cols},
    {'C', 5, 0, c_67_cols},           {'D', 5, 0, c_68_cols},
    {'E', 5, 0, c_69_cols},           {'F', 5, 0, c_70_cols},
    {'G', 5, 0, c_71_cols},           {'H', 5, 0, c_72_cols},
    {'I', 5, 0, c_73_cols},           {'J', 5, 0, c_74_cols},
    {'K', 5, 0, c_75_cols},           {'L', 5, 0, c_76_cols},
    {'M', 5, 0, c_77_cols},           {'N', 5, 0, c_78_cols},
    {'O', 5, 0, c_79_cols},           {'P', 5, 0, c_80_cols},
    {'Q', 5, 0, c_81_cols},           {'R', 5, 0, c_82_cols},
    {'S', 5, 0, c_83_cols},           {'T', 5, 0, c_84_cols},
    {'U', 5, 0, c_85_cols},           {'V', 5, 0, c_86_cols},
    {'W', 5, 0, c_87_cols},           {'X', 5, 0, c_88_cols},
    {'Y', 5, 0, c_89_cols},           {'Z', 5, 0, c_90_cols},
    {'[', 4, 0, c_91_cols},           {'\\', 3, 0, c_92_cols},
    {']', 4, 0, c_93_cols},           {'^', 5, 0, c_94_cols},
    {'_', 5, 0, c_95_cols},           {'`', 5, 0, c_96_cols},
    {'a', 5, 0, c_97_cols},           {'b', 5, 0, c_98_cols},
    {'c', 5, 0, c_99_cols},           {'d', 5, 0, c_100_cols},
    {'e', 5, 0, c_101_cols},          {'f', 5, 0, c_102_cols},
    {'g', 5, 2, c_103_cols},          {'h', 5, 0, c_104_cols},
    {'i', 5, 0, c_105_cols},          {'j', 5, 0, c_106_cols},
    {'k', 5, 0, c_107_cols},          {'l', 5, 0, c_108_cols},
    {'m', 5, 0, c_109_cols},          {'n', 5, 0, c_110_cols},
    {'o', 5, 0, c_111_cols},          {'p', 5, 2, c_112_cols},
    {'q', 5, 2, c_113_cols},          {'r', 5, 0, c_114_cols},
    {'s', 5, 0, c_115_cols},          {'t', 5, 0, c_116_cols},
    {'u', 5, 0, c_117_cols},          {'v', 5, 0, c_118_cols},
    {'w', 5, 0, c_119_cols},          {'x', 5, 0, c_120_cols},
    {'y', 5, 2, c_121_cols},          {'z', 5, 0, c_122_cols},
    {'{', 4, 0, c_123_cols},          {'|', 1, 0, c_124_cols},
    {'}', 4, 0, c_125_cols},          {'~', 5, 0, c_126_cols}};

const Font font_kubasta = {96, DEFAULT_HEIGHT, font_kubasta_chars};

const Char font_icons_chars[] = {{'0', 11, 0, i_box1_cols},
                                 {'1', 11, 0, i_box2_cols},
                                 {'2', 11, 0, i_box3_cols}};

const Font font_icons = {3, 11, font_icons_chars};