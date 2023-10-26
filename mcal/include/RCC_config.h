/*****************************************************************************
* @file:    RCC_config.h
* @author:  Copyright (c) 2023 Gomaa Mohammed Gomaa.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Sat, 8 Aug 2023 14:21:12 +0200
* @brief:   Reset Clock Control(RCC) Driver for STM32F103
******************************************************************************/
#ifndef    _RCC_CONFIG_H
#define    _RCC_CONFIG_H 

/* ==================================================================== */
/* =================== Configurations Selection ======================= */
/* ==================================================================== */

/* RCC_SYSTEM_CLOCK options: [ RCC_HSE_CRYSTAL | RCC_HSE_RC | RCC_HSI | RCC_PLL ] */
#define     RCC_SYSTEM_CLOCK    RCC_HSE_CRYSTAL

/* RCC_PLL_INPUT options: [ RCC_PLL_IN_HSI_2 | RCC_PLL_IN_HSE_2 | RCC_PLL_IN_HSE ] */
/* Note: only in case of pll */
#if        RCC_SYSTEM_CLOCK == RCC_PLL
#define    RCC_PLL_INPUT    RCC_PLL_IN_HSI_2
#endif

/* RCC_MUL_VAL options: [ from 0 to 16 ] */
/* Note: only in case of pll*/
#if        RCC_SYSTEM_CLOCK == RCC_PLL
#define    RCC_MUL_VAL   4
#endif

/* RCC_AHB_CLOCK options: [ RCC_SYSTEM_CLOCK_DIV_1
                            RCC_SYSTEM_CLOCK_DIV_2
                            RCC_SYSTEM_CLOCK_DIV_4
                            RCC_SYSTEM_CLOCK_DIV_8
                            RCC_SYSTEM_CLOCK_DIV_16
                            RCC_SYSTEM_CLOCK_DIV_64
                            RCC_SYSTEM_CLOCK_DIV_128
                            RCC_SYSTEM_CLOCK_DIV_256
                            RCC_SYSTEM_CLOCK_DIV_512 ] */
#define RCC_AHB_CLOCK  RCC_SYSTEM_CLOCK_DIV_1

/* RCC_APB1_CLOCK: [ RCC_AHB_CLOCK_DIV_1
                     RCC_AHB_CLOCK_DIV_2
                     RCC_AHB_CLOCK_DIV_4
                     RCC_AHB_CLOCK_DIV_8
                     RCC_AHB_CLOCK_DIV_16 ] */
#define RCC_APB1_CLOCK  RCC_AHB_CLOCK_DIV_8

/* RCC_APB2_CLOCK: [ RCC_AHB_CLOCK_DIV_1
                     RCC_AHB_CLOCK_DIV_2
                     RCC_AHB_CLOCK_DIV_4
                     RCC_AHB_CLOCK_DIV_8
                     RCC_AHB_CLOCK_DIV_16 ] */
#define RCC_APB2_CLOCK  RCC_AHB_CLOCK_DIV_1

/* RCC_ADC_CLOCK: [ RCC_APB2_CLOCK_DIV_2
                    RCC_APB2_CLOCK_DIV_4
                    RCC_APB2_CLOCK_DIV_6
                    RCC_APB2_CLOCK_DIV_8 ] */
#define RCC_ADC_CLOCK  RCC_APB2_CLOCK_DIV_2



#endif
