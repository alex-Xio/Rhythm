#include "render.h"
#include "oled.h"
#include "tasks.h"
#include <stdint.h>
#define TASK_PADDING 4
uint8_t dirty_tasks = 0xFF;
uint8_t last_active_task_i = 0;
uint8_t last_task_offset = 0;

void set_dirty_task(uint8_t i) { dirty_tasks |= (1U << i); }

void oled_drawhline(uint8_t y, bool color) {
  for (int i = 0; i < SIZE; i++) {
    set_pixel(i, y, color);
  }
}
void oled_drawtask(uint8_t y_start, Task task, bool is_active) {
  oled_drawbox(0, y_start, 128, y_start + (TASK_PADDING * 2) + 7, is_active);
  oled_drawstr(&font_kubasta, task.name, TASK_PADDING, y_start + TASK_PADDING,
               is_active);
  uint16_t times_completed = times_completed_today(task.name);
  char c = '0';
  if (times_completed == 0) {
    c = '0';
  } else if (times_completed < task.complt) {
    c = '1';
  } else {
    c = '2';
  }
  oled_drawchar(&font_icons, c, SIZE - 7 - TASK_PADDING, y_start + TASK_PADDING,
                is_active);
}

void oled_drawtasklist(Task *tasks, uint8_t y_start, uint8_t n,
                       uint8_t offset) {
  for (int i = 0; i < n; i++) {
    if (dirty_tasks & (1U << i)) {
      oled_drawtask(y_start, tasks[i], i == get_active_task_i());
      dirty_tasks &= ~(1U << i);
    }
    y_start += (TASK_PADDING * 2) + 8;
  }
}
void oled_setstatbar() {
  oled_drawhline(10, true);
  oled_drawstr(&font_kubasta, "Rhythm", 0, 0, false);
}
void oled_settitle() { oled_drawstr(&font_kubasta, "TODAY", 0, 17, false); }
void reload_tasklist() {
  if (last_active_task_i != get_active_task_i()) {
    dirty_tasks |= (1U << last_active_task_i);
    dirty_tasks |= (1U << get_active_task_i());
    last_active_task_i = get_active_task_i();
  }
  if (last_task_offset != get_task_offset()) {
    dirty_tasks = 0xFF;
    last_task_offset = get_task_offset();
  }
  oled_drawtasklist(get_tasks(), 27, TASKS_FIT, get_task_offset());
}
void assemble_frame() {
  oled_setstatbar();
  oled_settitle();
  reload_tasklist();
}
void render() { oled_display(); }