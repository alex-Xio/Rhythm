#ifndef TASKS_H_
#define TASKS_H_
#include <stdint.h>

#define MAX_NAME_SIZE 22
#define TASKS_FIT 6
typedef struct {
  char name[MAX_NAME_SIZE];
  uint8_t complt;
} Task;

Task *get_tasks();
uint8_t get_active_task_i();
uint8_t get_task_offset();
void next_task();
void prev_task();
#endif // TASKS_H_