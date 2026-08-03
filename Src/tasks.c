#include "tasks.h"
#include <stdint.h>
uint8_t active_task_i = 5;
uint8_t task_offset = 0;
Task active_tasks[] = {{"Test 1", 2}, {"Test 2", 1}, {"Test 3", 2},
                       {"Test 4", 2}, {"Test 5", 2}, {"Test 6", 2},
                       {"Test 7", 2}, {"Test 8", 2}};

uint8_t get_active_task_i() { return active_task_i; }
uint8_t get_task_offset() { return task_offset; }

void next_task() {
  uint8_t n = sizeof(active_tasks) / sizeof(active_tasks[0]);
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
  uint8_t n = sizeof(active_tasks) / sizeof(active_tasks[0]);
  if (task_offset > 0 && active_task_i == 0) {
    task_offset--;
  } else {
    if (active_task_i > 0) {
      active_task_i--;
    }
  }
}

Task *get_tasks() { return &active_tasks[task_offset]; }