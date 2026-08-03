#include "tasks.h"
uint8_t active_task_i = 0;
Task active_tasks[] = {
    {"Test 1", 2}, {"Test 2", 3}, {"Test 3", 3}, {"Test4", 3}, {"Test 5", 3}};

uint8_t get_active_task_i() { return active_task_i; }

Task *get_tasks() { return active_tasks; }