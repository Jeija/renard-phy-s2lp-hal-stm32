/* Shutdown pin configuration */
#define STM32RENARD_SHUTDOWN_PORT                    GPIOB
#define STM32RENARD_SHUTDOWN_PIN                     GPIO_PIN_8
#define STM32RENARD_SHUTDOWN_CLOCK_ENABLE()          __GPIOB_CLK_ENABLE()
#define STM32RENARD_SHUTDOWN_SPEED                   GPIO_SPEED_HIGH
#define STM32RENARD_SHUTDOWN_PUPD                    GPIO_NOPULL

/* IRQ pin ( = S2-LP's GPIO3) configuration */
#define STM32RENARD_GPIO_PORT                        GPIOB
#define STM32RENARD_GPIO_PIN                         GPIO_PIN_2
#define STM32RENARD_GPIO_CLOCK_ENABLE()              __GPIOB_CLK_ENABLE()
#define STM32RENARD_GPIO_SPEED                       GPIO_SPEED_HIGH
#define STM32RENARD_GPIO_PUPD                        GPIO_NOPULL
#define STM32RENARD_GPIO_EXTI_MODE                   GPIO_MODE_IT_FALLING
#define STM32RENARD_GPIO_EXTI_IRQN                   EXTI2_3_IRQn

/* Clock configuration */
// LSE clock speed is ~38kHz; divided by 16, that is ~2.313kHz
#define STM32RENARD_TIMER_PRESCALER                  RTC_WAKEUPCLOCK_RTCCLK_DIV16
#define STM32RENARD_WAKEUP_FREQUENCY                 2357

/* SPI Configuration */
// Pinout
#define STM32RENARD_SPI                              SPI1
#define STM32RENARD_SPI_CLK_ENABLE()                 __SPI1_CLK_ENABLE()
#define STM32RENARD_SPI_AF                           GPIO_AF0_SPI1

#define STM32RENARD_SPI_MISO_PORT                    GPIOB
#define STM32RENARD_SPI_MISO_PIN                     GPIO_PIN_4
#define STM32RENARD_SPI_MISO_CLK_ENABLE()            __GPIOB_CLK_ENABLE()

#define STM32RENARD_SPI_MOSI_PORT                    GPIOA
#define STM32RENARD_SPI_MOSI_PIN                     GPIO_PIN_7
#define STM32RENARD_SPI_MOSI_CLK_ENABLE()            __GPIOA_CLK_ENABLE()

#define STM32RENARD_SPI_SCLK_PORT                    GPIOB
#define STM32RENARD_SPI_SCLK_PIN                     GPIO_PIN_3
#define STM32RENARD_SPI_SCLK_CLK_ENABLE()            __GPIOB_CLK_ENABLE()

#define STM32RENARD_SPI_CS_PORT                      GPIOA
#define STM32RENARD_SPI_CS_PIN                       GPIO_PIN_15
#define STM32RENARD_SPI_CS_CLK_ENABLE()              __GPIOA_CLK_ENABLE()

// DMA
#define STM32RENARD_SPI_DMA_CLK_ENABLE()             __DMA1_CLK_ENABLE()
#define STM32RENARD_SPI_TX_DMA_CHANNEL               DMA1_Channel3
#define STM32RENARD_SPI_RX_DMA_CHANNEL               DMA1_Channel2
#define STM32RENARD_SPI_DMA_TX_IRQn                  DMA1_Channel2_3_IRQn
#define STM32RENARD_SPI_DMA_RX_IRQn                  DMA1_Channel2_3_IRQn
#define STM32RENARD_SPI_DMA_IRQHandler               DMA1_Channel2_3_IRQHandler
#define STM32RENARD_SPI_RX_DMA_REQUEST               DMA_REQUEST_1
#define STM32RENARD_SPI_TX_DMA_REQUEST               DMA_REQUEST_1
