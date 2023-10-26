/*****************************************************************************
* @file:    STK_private.h
* @author:  Copyright (c) 2023 Gomaa Mohammed Gomaa. 
* @license: GNU GPL version 3 or later.
*		  This is free software: you are free to change and redistribute it.  
*		  There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Wed, 4 Oct 2023 13:31:12 +0200
* @brief:   System Timer Counter(SysTick) Driver for STM32F103
******************************************************************************/
#ifndef _STK_PRIVATE_H
#define _STK_PRIVATE_H

/* ==================================================================== */
/* ======================= private data types ========================= */
/* ==================================================================== */

typedef struct{
	u32  CTRL;
     u32  LOAD;
     u32  VAL;
     u32  CALIB;
}SysTick_type;


/* ==================================================================== */
/* =================== Private Variables and Macros =================== */
/* ==================================================================== */

/* Create variable from SysTick_type to define the SysTick Registers */
#define STK  ((volatile SysTick_type*)0xE000E010)

// Callback variable to store the callback of SysTick
void (*STK_Callback)(void);

// Define Variable for interval mode 
static u8 IntervalMode;

// Private configurations for clock source
#define   STK_AHB          0
#define   STK_AHB_DIV_8    1

// Private configurations for interval type
#define     STK_SINGLE_INTERVAL    0
#define     STK_PERIOD_INTERVAL    1


#endif
