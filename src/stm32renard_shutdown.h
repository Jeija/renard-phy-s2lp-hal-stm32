#include <stdbool.h>

#ifndef _STM32RENARD_SHUTDOWN_H
#define _STM32RENARD_SHUTDOWN_H

#define STM32RENARD_SHUTDOWN_PORT                        GPIOB
#define STM32RENARD_SHUTDOWN_PIN                         GPIO_PIN_8
#define STM32RENARD_SHUTDOWN_CLOCK_ENABLE()              __GPIOB_CLK_ENABLE()
#define STM32RENARD_SHUTDOWN_SPEED                       GPIO_SPEED_HIGH
#define STM32RENARD_SHUTDOWN_PUPD                        GPIO_NOPULL

void stm32renard_shutdown_init(void);
void stm32renard_shutdown_set(bool shutdown);

#endif
