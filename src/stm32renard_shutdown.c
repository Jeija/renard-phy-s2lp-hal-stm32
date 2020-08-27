#include "stm32l0xx_hal.h"

#include "stm32renard_shutdown.h"
#include "conf_hardware.h"

void stm32renard_shutdown_init(void)
{
	STM32RENARD_SHUTDOWN_CLOCK_ENABLE();

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pin = STM32RENARD_SHUTDOWN_PIN;
	GPIO_InitStruct.Pull = STM32RENARD_SHUTDOWN_PUPD;
	GPIO_InitStruct.Speed = STM32RENARD_SHUTDOWN_SPEED;

	HAL_GPIO_Init(STM32RENARD_SHUTDOWN_PORT, &GPIO_InitStruct);
}

void stm32renard_shutdown_set(bool shutdown)
{
	HAL_GPIO_WritePin(STM32RENARD_SHUTDOWN_PORT, STM32RENARD_SHUTDOWN_PIN, shutdown ? GPIO_PIN_SET : GPIO_PIN_RESET);
}
