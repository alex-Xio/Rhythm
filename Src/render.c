#include "render.h"
#include "oled.h"
#include "tasks.h"
#define TASK_PADDING 5

void oled_drawtask(uint8_t y_start, Task task, bool is_active) {
  oled_drawbox(0, y_start, 128, y_start + (TASK_PADDING * 2) + 7, is_active);
  oled_drawstr(&font_kubasta, task.name, TASK_PADDING, y_start + TASK_PADDING,
               is_active);
  oled_drawchar(&font_icons, '0', SIZE - 7 - TASK_PADDING,
                y_start + TASK_PADDING, is_active);
}

void oled_drawtasklist(Task *tasks, uint8_t y_start, uint8_t n,
                       uint8_t offset) {
  for (int i = 0; i < n; i++) {
    oled_drawtask(y_start + TASK_PADDING, tasks[i], i == get_active_task_i());
    y_start += (TASK_PADDING * 2) + 8;
  }
}
void oled_setstatbar() {
  for (int i = 0; i < 128; i++) {
    set_pixel(i, 10, true);
  }
  oled_drawstr(&font_kubasta, "Rhythm", 0, 0, false);
}
void oled_settitle() { oled_drawstr(&font_kubasta, "TODAY", 0, 16, false); }
void assemble_frame() {
  oled_setstatbar();
  oled_settitle();
  oled_drawtasklist(get_tasks(), 20, 5, 0);
}
void render() {
  assemble_frame();
  oled_display();
}