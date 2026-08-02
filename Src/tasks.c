#include "tasks.h"
Task active_tasks[] = {
    {"Test 1", 2}, {"Test 2", 3}, {"Test 3", 3}, {"Test4", 3}, {"Test 5", 3}};

Task *get_tasks() { return active_tasks; }