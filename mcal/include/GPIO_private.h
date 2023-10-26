/*****************************************************************************
* @file:    GPIO_private.h
* @author:  Copyright (c) 2023 Gomaa Mohammed Gomaa.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Sun, 1 Oct 2023 14:21:12 +0200
* @brief:   General Purpose Input Output(GPIO) Driver for STM32F103
******************************************************************************/
#ifndef _GPIO_PRIVATE_H
#define _GPIO_PRIVATE_H

/* ==================================================================== */
/* =================== Private Variables and Macros =================== */
/* ==================================================================== */

/* Base Adress Definitions*/
#define   GPIOA_BASE_ADRESS  0x40010800
#define   GPIOB_BASE_ADRESS  0x40010C00
#define   GPIOC_BASE_ADRESS  0x40011000

/* Registers Definition of PORTA */
#define   GPIOA_CRL   *((u32*)(GPIOA_BASE_ADRESS+0x00))
#define   GPIOA_CRH   *((u32*)(GPIOA_BASE_ADRESS+0x04))
#define   GPIOA_IDR   *((u32*)(GPIOA_BASE_ADRESS+0x08))
#define   GPIOA_ODR   *((u32*)(GPIOA_BASE_ADRESS+0x0C))
#define   GPIOA_BSRR  *((u32*)(GPIOA_BASE_ADRESS+0x10))
#define   GPIOA_BRR   *((u32*)(GPIOA_BASE_ADRESS+0x14))
#define   GPIOA_LCKR  *((u32*)(GPIOA_BASE_ADRESS+0x18))

/* Registers Definition of PORTB */
#define   GPIOB_CRL   *((u32*)(GPIOB_BASE_ADRESS+0x00))
#define   GPIOB_CRH   *((u32*)(GPIOB_BASE_ADRESS+0x04))
#define   GPIOB_IDR   *((u32*)(GPIOB_BASE_ADRESS+0x08))
#define   GPIOB_ODR   *((u32*)(GPIOB_BASE_ADRESS+0x0C))
#define   GPIOB_BSRR  *((u32*)(GPIOB_BASE_ADRESS+0x10))
#define   GPIOB_BRR   *((u32*)(GPIOB_BASE_ADRESS+0x14))
#define   GPIOB_LCKR  *((u32*)(GPIOB_BASE_ADRESS+0x18))

/* Registers Definition of PORTC */
#define   GPIOC_CRL   *((u32*)(GPIOC_BASE_ADRESS+0x00))
#define   GPIOC_CRH   *((u32*)(GPIOC_BASE_ADRESS+0x04))
#define   GPIOC_IDR   *((u32*)(GPIOC_BASE_ADRESS+0x08))
#define   GPIOC_ODR   *((u32*)(GPIOC_BASE_ADRESS+0x0C))
#define   GPIOC_BSRR  *((u32*)(GPIOC_BASE_ADRESS+0x10))
#define   GPIOC_BRR   *((u32*)(GPIOC_BASE_ADRESS+0x14))
#define   GPIOC_LCKR  *((u32*)(GPIOC_BASE_ADRESS+0x18))


#endif
