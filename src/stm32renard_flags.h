#include <stdbool.h>

#ifndef _STM32RENARD_FLAGS_H
#define _STM32RENARD_FLAGS_H

typedef struct {
	volatile bool timeout_raised;
	volatile bool gpio_raised;
} stm32renard_flags_t;

extern stm32renard_flags_t stm32renard_flags;

#endif
