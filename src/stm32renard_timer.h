#include <inttypes.h>

#ifndef _STM32RENARD_TIMER_H
#define _STM32RENARD_TIMER_H

/* LSE clock speed is ~38kHz; divided by 16, that is ~2.313kHz */
#define STM32RENARD_TIMER_PRESCALER  RTC_WAKEUPCLOCK_RTCCLK_DIV16
#define STM32RENARD_WAKEUP_FREQUENCY 2357
#define MAX_TICKS_PER_WAKEUP         65535

void stm32renard_timer_start(uint32_t milliseconds);
void stm32renard_timer_stop(void);

#endif
