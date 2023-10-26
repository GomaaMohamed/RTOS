/*****************************************************************************
* @file:    GPIO_program.c
* @author:  Copyright (c) 2023 Gomaa Mohammed Gomaa. 
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Sun, 1 Oct 2023 14:21:12 +0200
* @brief:   General Purpose Input Output(GPIO) Driver for STM32F103
******************************************************************************/

/* ==================================================================== */
/* ========================== include files =========================== */
/* ==================================================================== */
#include   "STD_TYPES.h"
#include   "BIT_MATH.h"

#include   "GPIO_interface.h"
#include   "GPIO_private.h"
#include   "GPIO_config.h"


/* ==================================================================== */
/* ================= Public Functions Implementation ================== */
/* ==================================================================== */

// Function to set pin mode
void GPIO_setPinDirection(PortId_type PortId,PinId_type PinId,PinMode_type PinMode)
{
	// Validate input parameters
	ASSERT(PortId >= 0 && PortId < PORT_ID_ERR );
	ASSERT(PinId >= 0 && PinId < PIN_ID_ERR );
	ASSERT(PinMode >= 0 && PinMode < PIN_MODE_ERR );

	// Select PortId and PinId then set its mode
	switch(PortId)
	{
		case GPIOA :
			if(PinId <= GPIO_PIN7)
			{
				GPIOA_CRL &=~ ((0b1111)<<(PinId * 4));
				GPIOA_CRL |=  ((PinMode)<<(PinId * 4));
			}
			else if(PinId <= GPIO_PIN15)
			{   PinId -= 8;
				GPIOA_CRH &=~ ((0b1111)<<(PinId * 4));
				GPIOA_CRH |=  ((PinMode)<<(PinId * 4));
			}
			else
			{
				// Do nothing
			}
			break;
		case GPIOB :
			if(PinId <= GPIO_PIN7)
			{
				GPIOB_CRL &=~ ((0b1111)<<(PinId * 4));
				GPIOB_CRL |=  ((PinMode)<<(PinId * 4));
			}
			else if(PinId <= GPIO_PIN15)
			{   PinId -= 8;
				GPIOB_CRH &=~ ((0b1111)<<(PinId * 4));
				GPIOB_CRH |=  ((PinMode)<<(PinId * 4));
			}
			else
			{
				// Do nothing
			}
		    break;
		case GPIOC :
			if(PinId <= GPIO_PIN7)
			{
				GPIOC_CRL &=~ ((0b1111)<<(PinId * 4));
				GPIOC_CRL |=  ((PinMode)<<(PinId * 4));
			}
			else if(PinId <= GPIO_PIN15)
			{   PinId -= 8;
				GPIOC_CRH &=~ ((0b1111)<<(PinId * 4));
				GPIOC_CRH |=  ((PinMode)<<(PinId * 4));
			}
			else
			{
				// Do nothing
			}
			break;
		default:
			//Do nothing
			break;
	}
}

// Function to set the mode of any pin
void GPIO_setPinValue(PortId_type PortId,PinId_type PinId,PinState_type PinState)
{
	// Validate input parameters
	ASSERT(PortId >= 0 && PortId < PORT_ID_ERR );
	ASSERT(PinId >= 0 && PinId < PIN_ID_ERR );
	ASSERT(PinState >= 0 && PinState < PIN_MODE_ERR );

	// Select PortId and PinId then set its state
	switch(PortId)
	{
		case GPIOA :
			if(PinState == GPIO_HIGH)
			{
				GPIOA_BSRR = 1<<(PinId);
			}
			else if(PinState  == GPIO_LOW)
			{  
	    	    GPIOA_BRR = 1<<(PinId);
			}
			else
			{
				// Do nothing
			}
			break;
		case GPIOB :
			if(PinState == GPIO_HIGH)
			{
				GPIOB_BSRR = 1<<(PinId);
			}
			else if(PinState  == GPIO_LOW)
			{  
	    	    GPIOB_BRR = 1<<(PinId);
			}
			else
			{
				// Do nothing
			}
			break;
		case GPIOC :
			if(PinState == GPIO_HIGH)
			{
				GPIOC_BSRR = 1<<(PinId);
			}
			else if(PinState == GPIO_LOW)
			{
			    GPIOC_BRR = 1<<(PinId);
			}
			else
			{
				// Do nothing
			}
			break;
		default:
			// Do nothing
			break;
	}	
}

// Function to toggle the mode of any pin
void GPIO_togglePinValue(PortId_type PortId,PinId_type PinId)
{
	// Validate input parameters
	ASSERT(PortId >= 0 && PortId < PORT_ID_ERR );
	ASSERT(PinId >= 0 && PinId < PIN_ID_ERR );

	// Select PortId and PinId then toggle its state
	switch(PortId)
	{
		case GPIOA :
			TOG_BIT(GPIOA_ODR,PinId);
			break;
		case GPIOB :
			TOG_BIT(GPIOB_ODR,PinId);
			break;
		case GPIOC :
			TOG_BIT(GPIOC_ODR,PinId);
			break;
		default:
			// Do nothing
			break;
	}	
}

// Function to get pin state
PinState_type GPIO_getPinValue(PortId_type PortId,PinId_type PinId)
{ 
	// Validate input parameters
	ASSERT(PortId >= 0 && PortId < PORT_ID_ERR );
	ASSERT(PinId >= 0 && PinId < PIN_ID_ERR );
	
	// Variable to hold pin state
	PinState_type Result = GPIO_LOW;

	// Select PortId and PinId then get its state
	switch(PortId){
		case GPIOA :
			Result = GET_BIT(GPIOA_IDR,PinId);
			break;
		case GPIOB :
			Result = GET_BIT(GPIOB_IDR,PinId);
			break;
		case GPIOC :
			Result = GET_BIT(GPIOC_IDR,PinId);
			break;
		default:
			// Do nothing
			break;
	}
	return Result;
}

void GPIO_lockPinMode(PortId_type PortId,PinId_type PinId)
{   
	// Validate input parameters
	ASSERT(PortId >= 0 && PortId < PORT_ID_ERR );
	ASSERT(PinId >= 0 && PinId < PIN_ID_ERR );

	// Temp Variable
	u8 Read = 0;

	// Select PortId and PinId to lock its mode
    switch(PortId)
	{   
		case GPIOA:
			SET_BIT(GPIOA_LCKR,PinId);
			SET_BIT(GPIOA_LCKR,16);
			CLR_BIT(GPIOA_LCKR,16);
			SET_BIT(GPIOA_LCKR,16);
			Read = GET_BIT(GPIOA_LCKR,16);
			break;
		case GPIOB: 
			SET_BIT(GPIOB_LCKR,PinId);
			SET_BIT(GPIOB_LCKR,16);
			CLR_BIT(GPIOB_LCKR,16);
			SET_BIT(GPIOB_LCKR,16);
			Read = GET_BIT(GPIOB_LCKR,16);
			break;
		case GPIOC:
			SET_BIT(GPIOC_LCKR,PinId);
			SET_BIT(GPIOC_LCKR,16);
			CLR_BIT(GPIOC_LCKR,16);
			SET_BIT(GPIOC_LCKR,16);
			Read = GET_BIT(GPIOC_LCKR,16);
			break;
		default:
			// Do nothing
	}	
}





