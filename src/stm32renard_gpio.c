#include "stm32l0xx_hal.h"

#include "stm32renard_flags.h"
#include "stm32renard_gpio.h"
#include "conf_hardware.h"

void stm32renard_gpio_init(void)
{
	STM32RENARD_GPIO_CLOCK_ENABLE();

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pin = STM32RENARD_GPIO_PIN;
	GPIO_InitStruct.Pull = STM32RENARD_GPIO_PUPD;
	GPIO_InitStruct.Speed = STM32RENARD_GPIO_SPEED;
	GPIO_InitStruct.Mode = STM32RENARD_GPIO_EXTI_MODE;

	HAL_GPIO_Init(STM32RENARD_GPIO_PORT, &GPIO_InitStruct);
}

void stm32renard_gpio_interrupt_enable(bool enable)
{
	__HAL_GPIO_EXTI_CLEAR_IT(STM32RENARD_GPIO_PIN);
	HAL_NVIC_SetPriority(STM32RENARD_GPIO_EXTI_IRQN, 0x00, 0x00);

	if (enable)
		HAL_NVIC_EnableIRQ(STM32RENARD_GPIO_EXTI_IRQN);
	else
		HAL_NVIC_DisableIRQ(STM32RENARD_GPIO_EXTI_IRQN);

}

void stm32renard_gpio_interrupt_trigger(bool rising)
{
	if (rising)
	{
		EXTI->FTSR &= ~(uint16_t)STM32RENARD_GPIO_PIN;
		EXTI->RTSR |= (uint16_t)STM32RENARD_GPIO_PIN;
	}
	else
	{
		EXTI->RTSR &= ~(uint16_t)STM32RENARD_GPIO_PIN;
		EXTI->FTSR |= (uint16_t)STM32RENARD_GPIO_PIN;
	}
}

/*
 * The application must register GPIO_EXTI_Callback and call renard_phy_s2lp_hal_stm32_GPIO_EXTI_Callback whenever the
 * interrupt occurs. This allows the application to intercept GPIO interrupts for itself.
 */
void renard_phy_s2lp_hal_stm32_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == STM32RENARD_GPIO_PIN)
	{
		stm32renard_flags.gpio_raised = true;
		__HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);
	}
}
