#ifndef _RENARD_PHY_S2LP_HAL_STM32_CONF_HARDWARE_H
#define _RENARD_PHY_S2LP_HAL_STM32_CONF_HARDWARE_H

#if defined(RENARD_PHY_S2LP_HAL_STM32_CONF_HT32SX)
	#pragma message("[renard-phy-s2lp-hal-stm32] Compiling for HT32SX")
	#include "presets_hardware/ht32sx.h"
#elif defined(RENARD_PHY_S2LP_HAL_STM32_CONF_FKI868V2) 
	#pragma message("[renard-phy-s2lp-hal-stm32] Compiling for FKI868V2")
	#include "presets_hardware/fki868v2.h"
#else
	// target board unknown: just use FKI868V2 profile
	#pragma message("[renard-phy-s2lp-hal-stm32] Target board unspecified, compiling for FKI868V2")
	#include "presets_hardware/fki868v2.h"
#endif

#endif
