/*****************************************************************************
* @file:    RCC_interface.h
* @author:  Copyright (c) 2023 Gomaa Mohammed Gomaa.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Sun, 1 Oct 2023 14:21:12 +0200
* @brief:   Reset Clock Control(RCC) Driver for STM32F103
******************************************************************************/
#ifndef _RCC_INTERFACE_H
#define _RCC_INTERFACE_H

/* ==================================================================== */
/* ======================= public data types ========================== */
/* ==================================================================== */

/* Bus Id data type */
typedef enum
{
    RCC_AHB=0,
    RCC_APB1,
    RCC_APB2,
    BUS_ERR
} BusId_type;

/* Id of AHB Periphirals data type */
typedef enum
{
    /****** AHB Periphirals Ids ********/
    RCC_DMA1=0,
    RCC_DMA2,
    RCC_SRAM,
    RCC_FLITF=4,
    RCC_CRCE=6,
    RCC_FSMC=8,
    RCC_SDIO=10,
    /****** ABP1 Periphirals Ids *******/
    RCC_TIM2=0,
    RCC_TIM3,
    RCC_TIM4,
    RCC_TIM5,
    RCC_TIM6,
    RCC_TIM7,
    RCC_TIM12,
    RCC_TIM13,
    RCC_TIM14,
    RCC_WWD=11,
    RCC_SPI2=14,
    RCC_SPI3,
    RCC_USART2=17,
    RCC_USART3,
    RCC_UART4,
    RCC_UART5,
    RCC_I2C1,
    RCC_I2C2,
    RCC_USB,
    RCC_CAN=25,
    RCC_BKP=27,
    RCC_PWR,
    RCC_DAC,
    /****** ABP2 Periphirals Ids *******/
    RCC_AFIO=0,
    RCC_IOPA=2,
    RCC_IOPB,
    RCC_IOPC,
    RCC_IOPD,
    RCC_IOPE,
    RCC_IOPF,
    RCC_IOPG,
    RCC_ADC1,
    RCC_ADC2,
    RCC_TIM1,
    RCC_SPI1,
    RCC_TIM8,
    RCC_USART,
    RCC_ADC3,
    RCC_TIM9=19,
    RCC_TIM10,
    RCC_TIM11,
    PERIPHIRAL_ERR=30
}PeriphiralId_type;

/* ==================================================================== */
/* ==================== Public Functions Declaration ================== */
/* ==================================================================== */

/**
 * @brief---------------------> Initialize system clock
 * @param---------------------> None
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant             
 */
void RCC_initSysClock(void);

/**
 * @brief---------------------> Enable periphiral clock
 * @parameter1----------------> (BusId) bus in which the periphiral is connected
 * @parameter2----------------> (PeriphiralId) periphiral to be enabled its clock 
 * @return--------------------> None
 * @preconditions-------------> System clock is initialized
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant      
 */
void RCC_enableClock(BusId_type BusId,PeriphiralId_type PeriphiralId);


/**
 * @brief---------------------> Disable periphiral clock
 * @parameter1----------------> (BusId) bus in which the periphiral is connected
 * @parameter2----------------> (PeriphiralId) periphiral to be disabled its clock 
 * @return--------------------> None
 * @preconditions-------------> System clock is initialized
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant     
 */
void RCC_disableClock(BusId_type BusId,PeriphiralId_type PeriphiralId);



#endif
