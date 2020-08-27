#include <inttypes.h>

#ifndef _STM32RENARD_TIMER_H
#define _STM32RENARD_TIMER_H

#define MAX_TICKS_PER_WAKEUP         65535

void stm32renard_timer_start(uint32_t milliseconds);
void stm32renard_timer_stop(void);

#endif
