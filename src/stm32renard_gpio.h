#include <stdbool.h>

#ifndef _STM32RENARD_GPIO_H
#define _STM32RENARD_GPIO_H

void stm32renard_gpio_init(void);
void stm32renard_gpio_interrupt_enable(bool enable);
void stm32renard_gpio_interrupt_trigger(bool rising);

#endif
