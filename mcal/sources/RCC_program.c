/*****************************************************************************
* @file:    RCC_program.c
* @author:  Copyright (c) 2023 Gomaa Mohammed Gomaa.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Sun, 1 Oct 2023 14:21:12 +0200
* @brief:   Reset Clock Control(RCC) Driver for STM32F103
******************************************************************************/

/* ==================================================================== */
/* ========================== Include Files =========================== */
/* ==================================================================== */
#include  "STD_TYPES.h"
#include  "BIT_MATH.h"

#include  "RCC_interface.h"
#include  "RCC_private.h"
#include  "RCC_config.h"


/* ==================================================================== */
/* ================= Public Functions Implementation ================== */
/* ==================================================================== */

void RCC_initSysClock(void){

	// Select clock source
	#if   RCC_SYSTEM_CLOCK == RCC_HSE_CRYSTAL
		RCC_CR    =  0x00010000;       // Enable HSE Crystal
		RCC_CFGR  =  0x00000001;
	#elif RCC_SYSTEM_CLOCK == RCC_HSE_RC
		RCC_CR    =  0x00050000 ;      // Enable HSE RC 
		RCC_CFGR  =  0x00000001	;
	#elif RCC_SYSTEM_CLOCK == RCC_HSI
		RCC_CR    =  0x00000001 ;      // Enable HSI 
		RCC_CFGR  =  0x00000000;
	#elif RCC_SYSTEM_CLOCK == RCC_PLL
		u32  BitField = RCC_MUL_VAL;   // Enable PLL 
		BitField = BitField<<18;
	    #if   RCC_PLL_INPUT == RCC_PLL_IN_HSI_DIV_2
			RCC_CR    =  0x01000000;	            // Enable HSI 
	    	RCC_CFGR  |= BitField;
			CLR_BIT(RCC_CFGR,16);
			CLR_BIT(RCC_CFGR,17);
		#elif RCC_PLL_INPUT == RCC_PLL_IN_HSE_DIV_2
			RCC_CR    =  0x01000000;                // Enable HSI 
			RCC_CFGR  |= BitField;
			SET_BIT(RCC_CFGR,16);
			SET_BIT(RCC_CFGR,17);
		#elif RCC_PLL_INPUT == RCC_PLL_IN_HSE
			RCC_CR    =  0x01000000 ;               // Enable HSI 
			RCC_CFGR  |= BitField;
			SET_BIT(RCC_CFGR,16);
			CLR_BIT(RCC_CFGR,17);
		#endif 
	#else
	    #error("You chosed wrong clock type")
	#endif

	// Slect AHB clock
	RCC_CFGR  |= (RCC_AHB_CLOCK << 4);

	// Slect APB1 clock
	RCC_CFGR  |= (RCC_APB1_CLOCK << 8);

	// Slect APB2 clock
	RCC_CFGR  |= (RCC_APB2_CLOCK << 11);

	// Select ADC clock
	RCC_CFGR  |= (RCC_ADC_CLOCK << 14);

}


// Function to enable clock of periphirals
void RCC_enableClock(BusId_type BusId,PeriphiralId_type PeriphiralId){

	// Validate input parameters
	ASSERT(BusId >= 0 && BusId < BUS_ERR);
	ASSERT(PeriphiralId >= 0 && PeriphiralId < PERIPHIRAL_ERR);

	// Select bus and periphiral to enable its clock
	switch (BusId)
	{
		case RCC_AHB  : SET_BIT(RCC_AHBENR  , PeriphiralId);  break;
		case RCC_APB1 : SET_BIT(RCC_APB1ENR , PeriphiralId);  break;
		case RCC_APB2 : SET_BIT(RCC_APB2ENR , PeriphiralId);  break;
	}
}

// Function to disable clock of periphirals
void RCC_disableClock(BusId_type BusId,PeriphiralId_type PeriphiralId){
	
	// Validate input parameters
	ASSERT(BusId >= 0 && BusId < BUS_ERR);
	ASSERT(PeriphiralId >= 0 && PeriphiralId < PERIPHIRAL_ERR);

	// Select bus and periphiral to enable its clock
	switch (BusId)
	{
		case RCC_AHB  : CLR_BIT(RCC_AHBENR , PeriphiralId);  break;
		case RCC_APB1 : CLR_BIT(RCC_APB1ENR , PeriphiralId);  break;
		case RCC_APB2 : CLR_BIT(RCC_APB2ENR , PeriphiralId);  break;
	}
	
}

