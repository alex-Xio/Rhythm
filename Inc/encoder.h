#ifndef ENCODER_H_
#define ENCODER_H_
#include "stm32f4xx.h"
#include <stdbool.h>

void encoder_init(void);

bool encoder_clk_read(void);
bool encoder_dt_read(void);

#endif // ENCODER_H_