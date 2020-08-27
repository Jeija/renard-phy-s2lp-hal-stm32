#include <stdbool.h>

#ifndef _STM32RENARD_SHUTDOWN_H
#define _STM32RENARD_SHUTDOWN_H

void stm32renard_shutdown_init(void);
void stm32renard_shutdown_set(bool shutdown);

#endif
