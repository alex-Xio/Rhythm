#ifndef TASKS_H_
#define TASKS_H_
#include <stdint.h>

#define MAX_NAME_SIZE 17
#define TASKS_FIT 6
#define MAX_TASKS_COUNT 32
#define MAX_COMPLETIONS 4
typedef char Name[MAX_NAME_SIZE];
typedef struct {
  Name name;
  uint8_t id;
  uint8_t completions;
} Task;
typedef struct {
  uint8_t task_cnt;
  Task tasks[MAX_TASKS_COUNT];
} TaskList;
typedef struct {
  uint32_t date;      // BCD
  uint16_t completed; // 2y: 2y+1 bits are for completions (10 -> 2 etc.)
} DayRecord;
void tasks_init();
TaskList get_tasklist();
uint8_t get_task_cnt();
DayRecord *get_today_record();
uint8_t get_active_task_i();
uint8_t get_task_offset();
void next_task();
void prev_task();
uint8_t times_completed_today(char *name);
void complete_active_task();
#endif // TASKS_H_