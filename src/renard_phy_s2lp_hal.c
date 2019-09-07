#include <stdbool.h>
#include <stdint.h>

#include "stm32renard_shutdown.h"
#include "stm32renard_timer.h"
#include "stm32renard_flags.h"
#include "stm32renard_gpio.h"
#include "stm32renard_spi.h"

void renard_phy_s2lp_hal_init(void)
{
	stm32renard_shutdown_init();
	stm32renard_gpio_init();
	stm32renard_spi_init();
}

void renard_phy_s2lp_hal_spi(uint8_t length, uint8_t *in, uint8_t *out)
{
	stm32renard_spi_raw(length, in, out);
}

void renard_phy_s2lp_hal_shutdown(bool shutdown)
{
	stm32renard_shutdown_set(shutdown);
}

void renard_phy_s2lp_hal_interrupt_timeout(uint32_t milliseconds)
{
	stm32renard_timer_start(milliseconds);
}

void renard_phy_s2lp_hal_interrupt_gpio(bool risingTrigger)
{
	stm32renard_gpio_interrupt_enable(true);
	stm32renard_gpio_interrupt_trigger(risingTrigger);
}

void renard_phy_s2lp_hal_interrupt_clear(void)
{
	stm32renard_timer_stop();
	stm32renard_gpio_interrupt_enable(false);
}

/*
 * Application must implement this function and override the weak symbol. Function will be called when STM32 exits
 * from STOP mode and must initialize system clocks.
 */
__weak void renard_phy_s2lp_hal_stm32_sysclk_init(void)
{
}

int renard_phy_s2lp_hal_interrupt_wait(void)
{
	while (true)
	{
		HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
		renard_phy_s2lp_hal_stm32_sysclk_init();

		if (stm32renard_flags.gpio_raised) {
			stm32renard_flags.gpio_raised = false;
			return true;
		} else if (stm32renard_flags.timeout_raised) {
			stm32renard_flags.timeout_raised = false;
			return false;
		}
	}
}
