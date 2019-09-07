#include <stdbool.h>

#ifndef _STM32RENARD_GPIO_H
#define _STM32RENARD_GPIO_H

/* The pin configured here must correspond to S2-LP's GPIO3! */
#define STM32RENARD_GPIO_PORT                        GPIOC
#define STM32RENARD_GPIO_PIN                         GPIO_PIN_0
#define STM32RENARD_GPIO_CLOCK_ENABLE()              __GPIOC_CLK_ENABLE()
#define STM32RENARD_GPIO_SPEED                       GPIO_SPEED_HIGH
#define STM32RENARD_GPIO_PUPD                        GPIO_NOPULL
#define STM32RENARD_GPIO_EXTI_MODE                   GPIO_MODE_IT_FALLING
#define STM32RENARD_GPIO_EXTI_IRQN                   EXTI0_1_IRQn

void stm32renard_gpio_init(void);
void stm32renard_gpio_interrupt_enable(bool enable);
void stm32renard_gpio_interrupt_trigger(bool rising);

#endif
