#include <stdbool.h>
#include <stdio.h>

#include "stm32renard_gpio.h"
#include "stm32renard_spi.h"
#include "conf_hardware.h"

static SPI_HandleTypeDef SpiHandle;
static DMA_HandleTypeDef hdma_tx;
static DMA_HandleTypeDef hdma_rx;

void stm32renard_spi_init(void)
{
	/* Enable SPI periph and SCLK, MOSI, MISO and CS GPIO clocks */
	STM32RENARD_SPI_CLK_ENABLE();
	STM32RENARD_SPI_DMA_CLK_ENABLE();

	/* Configure TX DMA */
	hdma_tx.Instance                 = STM32RENARD_SPI_TX_DMA_CHANNEL;
	hdma_tx.Init.Request             = STM32RENARD_SPI_TX_DMA_REQUEST;
	hdma_tx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
	hdma_tx.Init.PeriphInc           = DMA_PINC_DISABLE;
	hdma_tx.Init.MemInc              = DMA_MINC_ENABLE;
	hdma_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	hdma_tx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
	hdma_tx.Init.Mode                = DMA_NORMAL;
	hdma_tx.Init.Priority            = DMA_PRIORITY_HIGH;

	HAL_DMA_Init(&hdma_tx);
	__HAL_LINKDMA(&SpiHandle, hdmatx, hdma_tx);

	/* Configure RX DMA */
	hdma_rx.Instance                 = STM32RENARD_SPI_RX_DMA_CHANNEL;
	hdma_rx.Init.Request             = STM32RENARD_SPI_RX_DMA_REQUEST;
	hdma_rx.Init.Direction           = DMA_PERIPH_TO_MEMORY;
	hdma_rx.Init.PeriphInc           = DMA_PINC_DISABLE;
	hdma_rx.Init.MemInc              = DMA_MINC_ENABLE;
	hdma_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	hdma_rx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
	hdma_rx.Init.Mode                = DMA_NORMAL;
	hdma_rx.Init.Priority            = DMA_PRIORITY_HIGH;

	HAL_DMA_Init(&hdma_rx);
	__HAL_LINKDMA(&SpiHandle, hdmarx, hdma_rx);

	/* Configure SPI */
	SpiHandle.Instance               = STM32RENARD_SPI;
	SpiHandle.Init.Mode              = SPI_MODE_MASTER;
	SpiHandle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
	SpiHandle.Init.Direction         = SPI_DIRECTION_2LINES;
	SpiHandle.Init.CLKPhase          = SPI_PHASE_1EDGE;
	SpiHandle.Init.CLKPolarity       = SPI_POLARITY_LOW;
	SpiHandle.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLED;
	SpiHandle.Init.CRCPolynomial     = 7;
	SpiHandle.Init.DataSize          = SPI_DATASIZE_8BIT;
	SpiHandle.Init.FirstBit          = SPI_FIRSTBIT_MSB;
	SpiHandle.Init.NSS               = SPI_NSS_SOFT;
	SpiHandle.Init.TIMode            = SPI_TIMODE_DISABLED;

	HAL_SPI_Init(&SpiHandle);
	__HAL_SPI_ENABLE(&SpiHandle);
}

void HAL_SPI_MspInit(SPI_HandleTypeDef* pSpiHandle)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	STM32RENARD_SPI_CLK_ENABLE();

	if (pSpiHandle->Instance==STM32RENARD_SPI)
	{
		STM32RENARD_SPI_SCLK_CLK_ENABLE();
		STM32RENARD_SPI_MISO_CLK_ENABLE();
		STM32RENARD_SPI_MOSI_CLK_ENABLE();
		STM32RENARD_SPI_CS_CLK_ENABLE();

		/* SCLK, MISO, MOSI */
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
		GPIO_InitStruct.Alternate = STM32RENARD_SPI_AF;

		GPIO_InitStruct.Pin = STM32RENARD_SPI_SCLK_PIN;
		HAL_GPIO_Init(STM32RENARD_SPI_SCLK_PORT, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = STM32RENARD_SPI_MISO_PIN;
		HAL_GPIO_Init(STM32RENARD_SPI_MISO_PORT, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = STM32RENARD_SPI_MOSI_PIN;
		HAL_GPIO_Init(STM32RENARD_SPI_MOSI_PORT, &GPIO_InitStruct);

		/* CS */
		GPIO_InitStruct.Pin = STM32RENARD_SPI_CS_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
		HAL_GPIO_Init(STM32RENARD_SPI_CS_PORT, &GPIO_InitStruct);

		/* Set CS high and wait for it to rise */
		HAL_GPIO_WritePin(STM32RENARD_SPI_CS_PORT, STM32RENARD_SPI_CS_PIN, GPIO_PIN_SET);
	}
}

void STM32RENARD_SPI_DMA_IRQHandler(void)
{
	HAL_DMA_IRQHandler(SpiHandle.hdmatx);
	HAL_DMA_IRQHandler(SpiHandle.hdmarx);
}

void stm32renard_spi_raw(uint8_t length, uint8_t *in, uint8_t *out)
{
	static uint8_t ignore[128];
	uint8_t *out_or_ignore = out != NULL ? out : ignore;

	HAL_NVIC_DisableIRQ(STM32RENARD_SPI_DMA_RX_IRQn);
	HAL_NVIC_DisableIRQ(STM32RENARD_SPI_DMA_TX_IRQn);

	/* Begin, pull CS low and don't let GPIO interrupt us for now */
	stm32renard_gpio_interrupt_enable(false);
	HAL_GPIO_WritePin(STM32RENARD_SPI_CS_PORT, STM32RENARD_SPI_CS_PIN, GPIO_PIN_RESET);

	/* Transfer and wait for transfer to complete */
	HAL_SPI_TransmitReceive_DMA(&SpiHandle, in, out_or_ignore, length);
	while(!__HAL_DMA_GET_FLAG(SpiHandle.hdmarx, __HAL_DMA_GET_TC_FLAG_INDEX(SpiHandle.hdmarx)));
	do {
		HAL_DMA_IRQHandler(SpiHandle.hdmarx);
		HAL_DMA_IRQHandler(SpiHandle.hdmatx);
	} while(HAL_SPI_GetState(&SpiHandle) != HAL_SPI_STATE_READY);

	/* Done, pull CS back high and re-enable GPIO interrupts */
	HAL_GPIO_WritePin(STM32RENARD_SPI_CS_PORT, STM32RENARD_SPI_CS_PIN, GPIO_PIN_SET);
	stm32renard_gpio_interrupt_enable(true);
}
