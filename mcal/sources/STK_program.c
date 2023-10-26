/*****************************************************************************
* @file:    STK_program.c
* @author:  Copyright (c) 2023 Gomaa Mohammed Gomaa. 
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Wed, 4 Oct 2023 13:31:12 +0200
* @brief:   Reset Clock Control(RCC) Driver for STM32F103
******************************************************************************/

/* ==================================================================== */
/* ========================== include files =========================== */
/* ==================================================================== */
#include      "STD_TYPES.h"
#include      "BIT_MATH.h"

#include      "STK_interface.h"
#include      "STK_private.h"
#include      "STK_config.h"


/* ==================================================================== */
/* ================ Public Functions Implementation =================== */
/* ==================================================================== */

// Function to initialize SysTick module
void STK_init(void)
{
	// Select clock source of SysTick
	#if   CLK_SOURCE  ==  STK_AHB
		// Disable STK - Disable STK Interrupt - Set clock source AHB 
		STK->CTRL = 0x00000004;

	#elif   CLK_SOURCE  ==  STK_AHB_DIV_8
	    // Disable STK - Disable STK interrupt - Set clock source AHB/8 
		STK->CTRL = 0;
	#endif	
}

// Function to make a delay with number of ticks
void STK_setBusyWait(u32 Ticks)
{   
    
	// Stop Timer and Make Values = 0 
	CLR_BIT(STK->CTRL, 0);
	STK->LOAD = 0;
	STK->VAL  = 0;

	// Load value to timer 
	STK->LOAD = Ticks;

	// Start timer 
	SET_BIT(STK->CTRL,0);

	// Check Flag 
	while((GET_BIT(STK->CTRL,16)) == 0);

}

// Function to execute a specific a single event after specific number of ticks
void STK_setSingleInterval(u32 Ticks,void (*Callback)(void))
{  
	// Validate input parameters
	ASSERT(Callback != NULL);

	// Stop Timer 
	SET_BIT(STK->CTRL, 0);
	STK -> LOAD = 0;
	STK -> VAL  = 0;

    // Set Mode to Single 
	IntervalMode = STK_SINGLE_INTERVAL;

    // Load ticks to load register
	STK->LOAD = Ticks;

	// Enable STK interrupt 
	SET_BIT(STK->CTRL,1);

	// Save CallBack */
	STK_Callback = Callback;

	// Start Timer 
	SET_BIT(STK->CTRL,0);
}

void STK_setPeriodicInterval(u32 Ticks,void (*Callback)(void))
{     
	// Validate input parameters
	ASSERT(Callback != NULL);

    // Set Mode to Periodic 
	IntervalMode = STK_PERIOD_INTERVAL;

    // Load ticks to load register 
	STK->LOAD = Ticks;

	// Enable STK Interrupt 
	SET_BIT(STK->CTRL,1);

	// Save CallBack 
	STK_Callback = Callback;

	// Start timer 	
	SET_BIT(STK->CTRL,0);
}
void STK_stopInterval(void)
{
	// Disable STK Interrupt 
	CLR_BIT(STK->CTRL,1);
	// Stop Timer 
	CLR_BIT(STK->CTRL,0);
	
	// Stop Timer 
	SET_BIT(STK->CTRL, 0);
	STK->LOAD = 0;
	STK->VAL  = 0;
	
	
}

// Function to get elapsed number of ticks
u32  STK_getElapsedTime(void)
{
	return (STK->LOAD - STK->VAL);
}

// Function to get remaining number of ticks
u32  STK_getRemainingTime(void)
{
	return (STK->VAL);
}

// Function to enable SysTick interrupt
void STK_enableInterrupt(void)
{
	SET_BIT(STK->CTRL,1);
}

// Function to disable SysTick interrupt
void STK_disableInterrupt(void)
{
	CLR_BIT(STK->CTRL, 1);
}

// Function to set callback of SysTick
void STK_setCallback(void (*Callback)(void))
{
	// Validate input parameters
	ASSERT(Callback != NULL);
	
	//Save CallBack 
	STK_Callback = Callback;
}

/* ==================================================================== */
/* ================ Private Functions Implementation ================== */
/* ==================================================================== */

// ISR of SysTick
void SysTick_Handler(void)
{
	// Temporary variable used to clear SysTick flag
	u8 Temp;
	
	if (IntervalMode == STK_SINGLE_INTERVAL)
	{
		// Disable STK interrupt 
		CLR_BIT(STK->CTRL, 1);
	
		// Stop timer 
		CLR_BIT(STK->CTRL, 0);
		STK -> LOAD = 0;
		STK -> VAL  = 0;
	}
	
	// Callback notification 
	STK_Callback();
	
	// Clear interrupt flag 
	Temp = GET_BIT(STK->CTRL,16);
}
