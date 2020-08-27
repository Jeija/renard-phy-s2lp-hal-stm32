#include "stm32l0xx.h"

#ifndef _STM32RENARD_SPI_H
#define _STM32RENARD_SPI_H

void stm32renard_spi_init(void);
void stm32renard_spi_raw(uint8_t length, uint8_t *in, uint8_t *out);

#endif
