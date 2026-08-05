#ifndef RENDER_H_
#define RENDER_H_
#include "tasks.h"
#include <stdbool.h>
#include <stdint.h>

void oled_drawtask(uint8_t y_start, Task task, bool is_active);
void oled_drawtasklist(Tasklist tasks, uint8_t y_start, uint8_t n,
                       uint8_t offset);
void oled_setstatbar();
void oled_settitle();
void assemble_frame();
void render();
void reload_tasklist();
void set_dirty_task(uint8_t i);
#endif // RENDER_H_