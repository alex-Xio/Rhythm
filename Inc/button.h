#ifndef BUTTON_H_
#define BUTTON_H_
#include "stm32f411xe.h"
#include <stdbool.h>

void button_init(void);
bool button_read(void);

#endif // BUTTON_H_H