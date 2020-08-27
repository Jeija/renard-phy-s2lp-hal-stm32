# `renard-phy-s2lp-hal-stm32` - STM32L0 Hardware Abstraction Layer for [`renard-phy-s2lp`](https://github.com/Jeija/renard-phy-s2lp)

`renard-phy-s2lp-hal-stm32` is the STM32L0 hardware abstraction layer (HAL) for the open source Sigfox PHY layer [`renard-phy-s2lp`](https://github.com/Jeija/renard-phy-s2lp), which interfaces with STMicroelectronics' S2-LP ultra-low power transceiver chip.

See [`renard-phy-s2lp`](https://github.com/Jeija/renard-phy-s2lp) for more information.

# Pin Configuration
`renard-phy-s2lp-hal-stm32` has multiple GPIO configuration profiles: One of them is compatible with [STEVAL-FKI868V2](https://www.st.com/en/evaluation-tools/steval-fki868v2.html), the other one with [HT Micron's HT32SX](https://github.com/htmicron/ht32sx). They use the following pins to interface with the S2-LP:

S2-LP Pin Name | STM32 Pin | HT32SX Pin
---:|:---:|:---
MISO (SPI) | GPIOA 6 | GPIOB 4
MOSI (SPI) | GPIOA 7 | GPIOA 7
SCLK (SPI) | GPIOB 3 | GPIOB 3
CS (SPI) | GPIOA 1 | GPIOA 15
SDN | GPIOA 8 | GPIOB 8
GPIO3 | GPIOC 0 | GPIOB 2

To select your desired configuration profile, use the compile time define switches `-DRENARD_PHY_S2LP_HAL_STM32_CONF_FKI868V2` (for FKI-868V2) or `-DRENARD_PHY_S2LP_HAL_STM32_CONF_HT32SX` (for HT32SX). To add your own GPIO profile(s), take a look at `conf/conf_hardware.h` and the provided profiles in `conf/presets_hardware`. Pull requests for additional profiles are welcome!

# Usage
See [renard-phy-s2lp-demo-stm32](https://github.com/Jeija/renard-phy-s2lp-demo-stm32/) (FKI-868V2) or [renard-phy-s2lp-demo-ht32sx](https://github.com/Jeija/renard-phy-s2lp-demo-stm32/) (HT32SX) for sample code that demonstrates how to integrate this HAL together with `renard-phy-s2lp` into your project.

# Licensing
`renard-phy-s2lp-hal-stm32` is licensed under the MIT License. See `LICENSE` for details.