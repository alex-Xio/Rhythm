#ifndef TASKS_H_
#define TASKS_H_
#include <stdint.h>

#define MAX_NAME_SIZE 22
typedef struct {
  char name[MAX_NAME_SIZE];
  uint8_t complt;
} Task;

Task *get_tasks();
uint8_t get_active_task_i();
#endif // TASKS_H_