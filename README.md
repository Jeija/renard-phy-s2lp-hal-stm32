# `renard-phy-s2lp-hal-stm32` - STM32L0 Hardware Abstraction Layer for [`renard-phy-s2lp`](https://github.com/Jeija/renard-phy-s2lp)

`renard-phy-s2lp-hal-stm32` is the STM32L0 hardware abstraction layer (HAL) for the open source Sigfox PHY layer [`renard-phy-s2lp`](https://github.com/Jeija/renard-phy-s2lp), which interfaces with STMicroelectronics' S2-LP ultra-low power transceiver chip.

See [`renard-phy-s2lp`](https://github.com/Jeija/renard-phy-s2lp) for more information.

# Pin Configuration
`renard-phy-s2lp-hal-stm32` is configured so that it is compatible with [STEVAL-FKI868V2](https://www.st.com/en/evaluation-tools/steval-fki868v2.html) by default. It uses the following pins to interface with the S2-LP:

S2-LP Pin Name | STM32 Pin
---:|:---
MISO (SPI) | GPIOA 6
MOSI (SPI) | GPIOA 7
SCLK (SPI) | GPIOB 3
CS (SPI) | GPIOA 1
SDN | GPIOA 8
GPIO3 | GPIOC 0

You can configure these pin definitions in `stm32renard_spi.h`, `stm32renard_shutdown.h` and `stm32renard_gpio.h`.

# Usage
See [renard-phy-s2lp-demo-stm32](https://github.com/Jeija/renard-phy-s2lp-demo-stm32/) for sample code that demonstrates how to integrate this HAL together with `renard-phy-s2lp` into your project.

# Licensing
`renard-phy-s2lp-hal-stm32` is licensed under the MIT License. See `LICENSE` for details.