#ifndef SYSTICK_H_
#define SYSTICK_H_
#include <stdbool.h>

void systick_disable();
void systick_init_50ms();
bool systick_count_flag();

#endif // SYSTICK_H_