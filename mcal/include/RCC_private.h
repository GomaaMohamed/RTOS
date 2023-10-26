/*****************************************************************************
* @file:    RCC_private.h
* @author:  Copyright (c) 2023 Gomaa Mohammed Gomaa.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Sun, 1 Oct 2023 14:21:12 +0200
* @brief:   Reset Clock Control(RCC) Driver for STM32F103
******************************************************************************/
#ifndef _RCC_PRIVATE_H
#define _RCC_PRIVATE_H

/* ==================================================================== */
/* =================== Private Variables and Macros =================== */
/* ==================================================================== */

/********* RCC Registers Definition ***********/
#define    RCC_CR           *((u32*)0x40021000)      //processor clock reg
#define    RCC_CFGR         *((u32*)0x40021004)      //processor clock reg
#define    RCC_CIR          *((u32*)0x40021008)
#define    RCC_APB2RSTR     *((u32*)0x4002100C)
#define    RCC_APB1RSTR     *((u32*)0x40021010)
#define    RCC_AHBENR       *((u32*)0x40021014)      //periphral clock reg
#define    RCC_APB2ENR      *((u32*)0x40021018)      //periphral clock reg
#define    RCC_APB1ENR      *((u32*)0x4002101C)      //periphral clock reg
#define    RCC_BDCR         *((u32*)0x40021020)
#define    RCC_CSR          *((u32*)0x40021024)


/* Clock Options */
#define   RCC_HSE_CRYSTAL        0
#define   RCC_HSE_RC             1
#define   RCC_HSI                2
#define   RCC_PLL                3

/* Clock Source */
#define   RCC_PLL_IN_HSI_DIV_2      0
#define   RCC_PLL_IN_HSE_DIV_2      1
#define   RCC_PLL_IN_HSE            2

/* AHB clock options */
#define  RCC_SYSTEM_CLOCK_DIV_1    0b0000
#define  RCC_SYSTEM_CLOCK_DIV_2    0b1000
#define  RCC_SYSTEM_CLOCK_DIV_4    0b1001
#define  RCC_SYSTEM_CLOCK_DIV_8    0b1010
#define  RCC_SYSTEM_CLOCK_DIV_16   0b1011
#define  RCC_SYSTEM_CLOCK_DIV_64   0b1100
#define  RCC_SYSTEM_CLOCK_DIV_128  0b1101
#define  RCC_SYSTEM_CLOCK_DIV_256  0b1110
#define  RCC_SYSTEM_CLOCK_DIV_512  0b1111

/* APB1 and APB2 options */
#define  RCC_AHB_CLOCK_DIV_1   0b000
#define  RCC_AHB_CLOCK_DIV_2   0b100
#define  RCC_AHB_CLOCK_DIV_4   0b101
#define  RCC_AHB_CLOCK_DIV_8   0b110
#define  RCC_AHB_CLOCK_DIV_16  0b111

/* ADC clock options */
#define  RCC_APB2_CLOCK_DIV_2  0
#define  RCC_APB2_CLOCK_DIV_4  1
#define  RCC_APB2_CLOCK_DIV_6  2
#define  RCC_APB2_CLOCK_DIV_8  3


#endif
