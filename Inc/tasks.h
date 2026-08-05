#ifndef TASKS_H_
#define TASKS_H_
#include <stdint.h>

#define MAX_NAME_SIZE 22
#define TASKS_FIT 6
#define MAX_TASKS_COUNT 20
#define MAX_COMPLETIONS 64
typedef char Name[MAX_NAME_SIZE];
typedef struct {
  Name name;
  uint8_t complt;
} Task;
typedef struct {
  uint8_t task_cnt;
  Task tasks[MAX_TASKS_COUNT];
} Tasklist;
typedef struct {
  Name name;
  uint32_t day;
  uint8_t count;
} Completion;

void tasks_init();
Tasklist get_tasklist();
uint8_t get_task_cnt();
Completion *get_completions();
uint8_t get_active_task_i();
uint8_t get_task_offset();
void next_task();
void prev_task();
uint8_t times_completed_today(char *name);
void complete_active_task();
#endif // TASKS_H_