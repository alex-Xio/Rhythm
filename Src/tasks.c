#include "tasks.h"
#include "eeprom.h"
#include "render.h"
#include <stdint.h>
uint8_t active_task_i = 5;
uint8_t task_offset = 0;
TaskList active_tasks;
DayRecord today_record;
bool record_dirty = false;

bool is_record_dirty() { return record_dirty; }

static void record_init() {
  char data[sizeof(DayRecord)];
  eeprom_rand_read(get_header().today_addr, sizeof(DayRecord), data);
  if (data[0] == 0xFF) {
    today_record.date = get_header().date_bcd;
    today_record.completed = 0U;
    return;
  }
  today_record = *(DayRecord *)data;
}
void tasks_init() {
  char cnt;
  eeprom_rand_read(EEPROM_TASKS_ADDR, 1, &cnt);
  if (cnt == 0xFFU) {
    active_tasks.task_cnt = 0;
    return;
  }
  char data[sizeof(TaskList)];
  eeprom_rand_read(EEPROM_TASKS_ADDR, sizeof(TaskList), data);
  active_tasks = *(TaskList *)data;
  record_init();
}

void update_record() {
  eeprom_write(get_header().today_addr, sizeof(today_record),
               (char *)&today_record);
  record_dirty = false;
}

uint8_t times_completed_today(uint8_t id) {
  uint8_t out = (today_record.completed >> (2U * id)) & 0x3U;
  return out;
}
void complete_active_task() {
  Task active_task = active_tasks.tasks[active_task_i + task_offset];
  if (times_completed_today(active_task.id) >= active_task.completions) {
    return;
  } else {
    if (times_completed_today(active_task.id) >= MAX_COMPLETIONS) {
      return;
    }
    today_record.completed += (1U << (active_task.id * 2));
    record_dirty = true;
    set_dirty_task(active_task_i);
  }
}

uint8_t get_active_task_i() { return active_task_i; }
uint8_t get_task_offset() { return task_offset; }
uint8_t get_task_cnt() { return active_tasks.task_cnt; }

void next_task() {
  uint8_t n = active_tasks.task_cnt;
  if (active_task_i + 1 + task_offset >= n) {
    return;
  }
  if (active_task_i == TASKS_FIT - 1) {
    task_offset++;
  } else {
    active_task_i++;
  }
}
void prev_task() {
  if (task_offset > 0 && active_task_i == 0) {
    task_offset--;
  } else {
    if (active_task_i > 0) {
      active_task_i--;
    }
  }
}

TaskList get_tasklist() { return active_tasks; }