#include "tasks.h"
#include "eeprom.h"
#include "render.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
uint8_t active_task_i = 5;
uint8_t task_offset = 0;
Tasklist active_tasks;
// Task active_tasks[] = {{"1 Completion", 1},  {"2 Completions", 2},
//                        {"3 Completions", 3}, {"!@#$%^&*()", 2},
//                        {"Test 5", 2},        {"Test 6", 2},
//                        {"Test 7", 2},        {"Test 8", 2}};

void tasks_init() {
  char cnt;
  eeprom_rand_read(EEPROM_TASKS_ADDR, 1, &cnt);
  if (cnt == 0xFFU) {
    memset(&active_tasks, 0, sizeof(active_tasks));
    return;
  }
  // uint16_t tsize = 1 + sizeof(Task) * cnt;
  uint16_t tsize = sizeof(Tasklist);
  char data[tsize];
  eeprom_rand_read(EEPROM_TASKS_ADDR, tsize, data);
  active_tasks = *(Tasklist *)data;
}
Completion completions[MAX_COMPLETIONS];
uint16_t n_completions = 1;
uint16_t completions_dirty = 0xFF;

uint8_t times_completed_today(char *name) {
  uint8_t out = 0;
  // TODO: actual completion logic
  out = 1;
  // for (uint8_t i = 0; i < n_completions; i++) {
  //   if (strcmp(name, completions[i].name) == 0) {
  //     out++;
  //   }
  // }
  return out;
}
void complete_active_task() {
  Task active_task = active_tasks.tasks[active_task_i + task_offset];
  if (times_completed_today(active_task.name) >= active_task.complt) {
    return;
  } else {
    // Completion new_comp = {"", 1};
    // strcpy(new_comp.name, active_task.name);
    // completions[n_completions++] = new_comp;
  }
  set_dirty_task(active_task_i);
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

Tasklist get_tasklist() { return active_tasks; }