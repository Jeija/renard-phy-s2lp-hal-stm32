#include "stm32l0xx_hal.h"

#include "stm32renard_timer.h"
#include "stm32renard_flags.h"
#include "conf_hardware.h"

static RTC_HandleTypeDef RtcHandle = {.Instance = RTC};
static volatile uint32_t remaining_milliseconds = 0;

static void stm32renard_timer_init(void)
{
	HAL_PWR_EnableBkUpAccess();

	/* Configure LSI Oscillator */
	RCC_OscInitTypeDef RCC_OscInitStruct;
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_LSE;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	RCC_OscInitStruct.LSIState = RCC_LSI_ON;
	RCC_OscInitStruct.LSEState = RCC_LSE_OFF;
	HAL_RCC_OscConfig(&RCC_OscInitStruct);

	/* Configure RTC derived from LSI */
	RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;
	PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
	PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
	HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);
	__HAL_RCC_RTC_ENABLE();

	HAL_NVIC_SetPriority(RTC_IRQn, 0x01, 0);
	HAL_NVIC_EnableIRQ(RTC_IRQn);
}

void stm32renard_timer_stop(void)
{
	HAL_RTCEx_DeactivateWakeUpTimer(&RtcHandle);
}

void stm32renard_timer_start(uint32_t milliseconds)
{
	stm32renard_timer_init();

	__HAL_RTC_WAKEUPTIMER_CLEAR_FLAG(&RtcHandle, RTC_FLAG_WUTF);
	__HAL_RTC_CLEAR_FLAG(RTC_EXTI_LINE_WAKEUPTIMER_EVENT);

	/*
	 * Try to time next wakeup so that it occurs exactly after the desired duration.
	 * If that is impossible because the desired duration is too long (> MAX_TICKS_PER_WAKEUP), just wait
	 * as long as possible and store how much time remains.
	 */
	uint32_t ticks_to_next_wakeup = STM32RENARD_WAKEUP_FREQUENCY * milliseconds / 1000;
	if (ticks_to_next_wakeup > MAX_TICKS_PER_WAKEUP)
	{
		remaining_milliseconds = milliseconds - 1000 * MAX_TICKS_PER_WAKEUP / STM32RENARD_WAKEUP_FREQUENCY;
		ticks_to_next_wakeup = MAX_TICKS_PER_WAKEUP;
	} else {
		remaining_milliseconds = 0;
	}

	HAL_RTCEx_SetWakeUpTimer_IT(&RtcHandle, ticks_to_next_wakeup, STM32RENARD_TIMER_PRESCALER);
}

void RTC_IRQHandler(void)
{
	stm32renard_timer_init();

	HAL_RTCEx_WakeUpTimerIRQHandler(&RtcHandle);
	HAL_RTCEx_DeactivateWakeUpTimer(&RtcHandle);

	if (remaining_milliseconds == 0)
		stm32renard_flags.timeout_raised = true;
	else
		stm32renard_timer_start(remaining_milliseconds);
}
