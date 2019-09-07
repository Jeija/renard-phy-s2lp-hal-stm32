#include "stm32l0xx.h"

#ifndef _STM32RENARD_SPI_H
#define _STM32RENARD_SPI_H

/* SPI Hardware Configuration */
#define STM32RENARD_SPI                               SPI1
#define STM32RENARD_SPI_CLK_ENABLE()                  __SPI1_CLK_ENABLE()
#define STM32RENARD_SPI_AF                            GPIO_AF0_SPI1

#define STM32RENARD_SPI_MISO_PORT                     GPIOA
#define STM32RENARD_SPI_MISO_PIN                      GPIO_PIN_6
#define STM32RENARD_SPI_MISO_CLK_ENABLE()             __GPIOA_CLK_ENABLE()

#define STM32RENARD_SPI_MOSI_PORT                     GPIOA
#define STM32RENARD_SPI_MOSI_PIN                      GPIO_PIN_7
#define STM32RENARD_SPI_MOSI_CLK_ENABLE()             __GPIOA_CLK_ENABLE()

#define STM32RENARD_SPI_SCLK_PORT                     GPIOB
#define STM32RENARD_SPI_SCLK_PIN                      GPIO_PIN_3
#define STM32RENARD_SPI_SCLK_CLK_ENABLE()             __GPIOB_CLK_ENABLE()

#define STM32RENARD_SPI_CS_PORT                       GPIOA
#define STM32RENARD_SPI_CS_PIN                        GPIO_PIN_1
#define STM32RENARD_SPI_CS_CLK_ENABLE()               __GPIOA_CLK_ENABLE()

/* DMA Hardware Configuration */
#define STM32RENARD_SPI_DMA_CLK_ENABLE()              __DMA1_CLK_ENABLE()
#define STM32RENARD_SPI_TX_DMA_CHANNEL                DMA1_Channel3
#define STM32RENARD_SPI_RX_DMA_CHANNEL                DMA1_Channel2
#define STM32RENARD_SPI_DMA_TX_IRQn                   DMA1_Channel2_3_IRQn
#define STM32RENARD_SPI_DMA_RX_IRQn                   DMA1_Channel2_3_IRQn
#define STM32RENARD_SPI_DMA_IRQHandler                DMA1_Channel2_3_IRQHandler
#define STM32RENARD_SPI_RX_DMA_REQUEST                DMA_REQUEST_1
#define STM32RENARD_SPI_TX_DMA_REQUEST                DMA_REQUEST_1

void stm32renard_spi_init(void);
void stm32renard_spi_raw(uint8_t length, uint8_t *in, uint8_t *out);

#endif
