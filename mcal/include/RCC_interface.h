/***************************************/
/* Author  :Gomaa                      */
/* Date    :8 Aug 2020                 */
/* Version :V01                        */
/***************************************/

#ifndef _RCC_INTERFACE_H_
#define _RCC_INTERFACE_H_


/* Bus Id */
#define     RCC_AHB         0
#define     RCC_APB1        1
#define     RCC_APB2        2

/* Id of AHB Periphirals */
#define     RCC_DMA1                0
#define     RCC_DMA2                1
#define     RCC_SRAM                2
#define     RCC_FLITF               4
#define     RCC_CRCE                6
#define     RCC_FSMC                8
#define     RCC_SDIO                10
/* Id of APB1 Periphirals */
#define     RCC_TIM2                 0
#define     RCC_TIM3                 1
#define     RCC_TIM4                 2
#define     RCC_TIM5                 3
#define     RCC_TIM6                 4
#define     RCC_TIM7                 5
#define     RCC_TIM12                6
#define     RCC_TIM13                7
#define     RCC_TIM14                8
#define     RCC_WWD                  11
#define     RCC_SPI2                 14
#define     RCC_SPI3                 15
#define     RCC_USART2               17
#define     RCC_USART3               18
#define     RCC_UART4                19
#define     RCC_UART5                20
#define     RCC_I2C1                 21
#define     RCC_I2C2                 22
#define     RCC_USB                  23
#define     RCC_CAN                  25
#define     RCC_BKP                  27
#define     RCC_PWR                  28
#define     RCC_DAC                  29
/* Id of APB2 Periphirals */
#define     RCC_AFIO                 0
#define     RCC_IOPA                 2
#define     RCC_IOPB                 3
#define     RCC_IOPC                 4
#define     RCC_IOPD                 5
#define     RCC_IOPE                 6
#define     RCC_IOPF                 7
#define     RCC_IOPG                 8
#define     RCC_ADC1                 9
#define     RCC_ADC2                 10
#define     RCC_TIM1                 11
#define     RCC_SPI1                 12
#define     RCC_TIM8                 13
#define     RCC_USART                14
#define     RCC_ADC3                 15
#define     RCC_TIM9                 19
#define     RCC_TIM10                20
#define     RCC_TIM11                21s


/* Clock Enable For External Periphiral */
void RCC_voidEnableClock(u8 Copy_u8BusId,u8 Copy_u8PerId);
/* Clock Disable For External Periphiral */
void RCC_voidDisableClock(u8 Copy_u8BusId,u8 Copy_u8PerId);
/* Initialize System Clock */
void RCC_voidInitSysClock(void);

// Note: Clock of Core Periphirals are Enabled by Default

#endif