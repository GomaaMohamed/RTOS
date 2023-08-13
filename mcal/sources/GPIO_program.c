/*********************************************************************************/
/* Author    : Gomaa Mohammed                                                      */
/* Version   : V01                                                               */
/* Date      : 8 August 2020                                                     */
/*********************************************************************************/


#include   "STD_TYPES.h"
#include   "BIT_MATH.h"

#include   "GPIO_interface.h"
#include   "GPIO_private.h"
#include   "GPIO_config.h"

/* Pin Operations*/
void GPIO_voidSetPinDirection(u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8Mode)
{
	switch(Copy_u8Port){
		case GPIOA :
		if(Copy_u8Pin <= 7)
		{
			GPIOA_CRL &=~ ((0b1111)<<(Copy_u8Pin * 4));
			GPIOA_CRL |=  ((Copy_u8Mode)<<(Copy_u8Pin * 4));
		}
		else if(Copy_u8Pin <= 15)
		{   Copy_u8Pin -= 8;
			GPIOA_CRH &=~ ((0b1111)<<(Copy_u8Pin * 4));
			GPIOA_CRH |=  ((Copy_u8Mode)<<(Copy_u8Pin * 4));
		}
		break;
		case GPIOB :
		if(Copy_u8Pin <= 7)
		{
			GPIOB_CRL &=~ ((0b1111)<<(Copy_u8Pin * 4));
			GPIOB_CRL |=  ((Copy_u8Mode)<<(Copy_u8Pin * 4));
		}
		else if(Copy_u8Pin <= 15)
		{   Copy_u8Pin -= 8;
			GPIOB_CRH &=~ ((0b1111)<<(Copy_u8Pin * 4));
			GPIOB_CRH |=  ((Copy_u8Mode)<<(Copy_u8Pin * 4));
		}
		break;
		
		case GPIOC :
		if(Copy_u8Pin <= 7)
		{
			GPIOC_CRL &=~ ((0b1111)<<(Copy_u8Pin * 4));
			GPIOC_CRL |=  ((Copy_u8Mode)<<(Copy_u8Pin * 4));
		}
		else if(Copy_u8Pin <= 15)
		{   Copy_u8Pin -= 8;
			GPIOC_CRH &=~ ((0b1111)<<(Copy_u8Pin * 4));
			GPIOC_CRH |=  ((Copy_u8Mode)<<(Copy_u8Pin * 4));
		}
		break;
		
	}
	
	
}

void GPIO_voidSetPinValue(u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8Value)
{
	
	switch(Copy_u8Port){
		case GPIOA :
		if(Copy_u8Value == GPIO_HIGH)
		{
			GPIOA_BSRR = 1<<(Copy_u8Pin);
		}
		else if(Copy_u8Value  == GPIO_LOW)
		{  
	        GPIOA_BRR = 1<<(Copy_u8Pin);
		}
		break;
		case GPIOB :
		if(Copy_u8Value == GPIO_HIGH)
		{
			GPIOB_BSRR = 1<<(Copy_u8Pin);
		}
		else if(Copy_u8Value  == GPIO_LOW)
		{  
	        GPIOB_BRR = 1<<(Copy_u8Pin);
		}
		
		break;
		
		case GPIOC :
				if(Copy_u8Value == GPIO_HIGH)
				{
					GPIOC_BSRR = 1<<(Copy_u8Pin);
				}
				else if(Copy_u8Value  == GPIO_LOW)
				{
			        GPIOC_BRR = 1<<(Copy_u8Pin);
				}
		break;
		
	}
	
}

u8 GPIO_voidGetPinValue(u8 Copy_u8Port,u8 Copy_u8Pin)
{ 
u8 Loc_u8Result = 0;

	switch(Copy_u8Port){
		case GPIOA :
		Loc_u8Result = GET_BIT(GPIOA_IDR,Copy_u8Pin);
		break;
		case GPIOB :
		Loc_u8Result = GET_BIT(GPIOB_IDR,Copy_u8Pin);
		
		break;
		
		case GPIOC :
		Loc_u8Result = GET_BIT(GPIOC_IDR,Copy_u8Pin);
		break;
		
	}
	
	return Loc_u8Result;
	
}

void GPIO_voidLockPinMode(u8 Copy_u8Port,u8 Copy_u8Pin)
{   u8 read = 0;
    switch(Copy_u8Port)
	{   
		case GPIOA:
		SET_BIT(GPIOA_LCKR,Copy_u8Pin);
		SET_BIT(GPIOA_LCKR,16);
		CLR_BIT(GPIOA_LCKR,16);
		SET_BIT(GPIOA_LCKR,16);
		read = GET_BIT(GPIOA_LCKR,16);
		
		break;
		case GPIOB: 
		
		SET_BIT(GPIOB_LCKR,Copy_u8Pin);
		SET_BIT(GPIOB_LCKR,16);
		CLR_BIT(GPIOB_LCKR,16);
		SET_BIT(GPIOB_LCKR,16);
		read = GET_BIT(GPIOB_LCKR,16);
		break;
		case GPIOC:
		SET_BIT(GPIOC_LCKR,Copy_u8Pin);
		SET_BIT(GPIOC_LCKR,16);
		CLR_BIT(GPIOC_LCKR,16);
		SET_BIT(GPIOC_LCKR,16);
		read = GET_BIT(GPIOC_LCKR,16);
		break;
	}	
	
}

/* Half Port Operations */
void GPIO_voidSetHalfPortDirection(u8 Copy_u8Port,u8 Copy_u8HalfPort,u32 Copy_u32HalfPortMode)
{
	switch(Copy_u8Port){
		case GPIOA :
		if(Copy_u8HalfPort == GPIO_FIRST_HALF)
		{
			GPIOA_CRL &=~ (0xFFFFFFFF);
			GPIOA_CRL =  Copy_u32HalfPortMode;
		}
		else if(Copy_u8HalfPort == GPIO_SECOND_HALF)
		{   
	        GPIOA_CRH &=~ (0xFFFFFFFF);
			GPIOA_CRH =  Copy_u32HalfPortMode;
		}
		break;
		case GPIOB :
		if(Copy_u8HalfPort == GPIO_FIRST_HALF)
		{
			GPIOB_CRL &=~ (0xFFFFFFFF);
			GPIOB_CRL =  Copy_u32HalfPortMode;
		}
		else if(Copy_u8HalfPort == GPIO_SECOND_HALF)
		{   
	        GPIOB_CRH &=~ (0xFFFFFFFF);
			GPIOB_CRH =  Copy_u32HalfPortMode;
		}
		break;
		
		case GPIOC :
		if(Copy_u8HalfPort == GPIO_FIRST_HALF)
		{
			GPIOC_CRL &=~ (0xFFFFFFFF);
			GPIOC_CRL =  Copy_u32HalfPortMode;
		}
		else if(Copy_u8HalfPort == GPIO_SECOND_HALF)
		{   
	        GPIOC_CRH &=~ (0xFFFFFFFF);
			GPIOC_CRH =  Copy_u32HalfPortMode;
		}
		break;
		
	}
	
	
}

void GPIO_voidSetHalfPortValue(u8 Copy_u8Port,u8 Copy_u8HalfPort,u16 Copy_u8Value)
{
	
	switch(Copy_u8Port){
		case GPIOA :
		if(Copy_u8HalfPort == GPIO_FIRST_HALF )
		{
			GPIOA_ODR &=~ (0xFFFF);
			GPIOA_ODR |= Copy_u8Value;
			//asm("NOP");
		}
		else if(Copy_u8HalfPort == GPIO_SECOND_HALF)
		{  
			GPIOA_ODR &=~ (0xFFFF0000);
	        GPIOA_ODR |= ((Copy_u8Value)<<8);
		}
		break;
		case GPIOB :
		if(Copy_u8HalfPort == GPIO_FIRST_HALF )
		{
			GPIOA_ODR &=~ (0xFFFF);
			GPIOB_ODR = Copy_u8Value;
		}
		else if(Copy_u8HalfPort == GPIO_SECOND_HALF)
		{  
			GPIOA_ODR &=~ (0xFFFF0000);
	        GPIOB_ODR |= ((Copy_u8Value)<<8);
		}
		
		break;
		
		case GPIOC :
		if(Copy_u8HalfPort == GPIO_FIRST_HALF )
		{
			GPIOA_ODR &=~ (0xFFFF);
			GPIOC_ODR = Copy_u8Value;
		}
		else if(Copy_u8HalfPort == GPIO_SECOND_HALF)
		{  
			GPIOA_ODR &=~ (0xFFFF0000);
	        GPIOC_ODR |= ((Copy_u8Value)<<8);
		}
		break;
		
	}
	
}

u8 GPIO_voidGetHalfPortValue(u8 Copy_u8Port,u8 Copy_u8HalfPort)
{
	
u8 Loc_u8Result = 0;

	switch(Copy_u8Port){
		case GPIOA :
		if(Copy_u8HalfPort == GPIO_FIRST_HALF )
		{
			Loc_u8Result = GPIOA_IDR;
		}
		else if(Copy_u8HalfPort == GPIO_SECOND_HALF)
		{  
	        Loc_u8Result = (GPIOA_IDR >> 8);
		}
		break;
		case GPIOB :
		if(Copy_u8HalfPort == GPIO_FIRST_HALF )
		{
			Loc_u8Result = GPIOB_IDR;
		}
		else if(Copy_u8HalfPort == GPIO_SECOND_HALF)
		{  
	        Loc_u8Result = (GPIOB_IDR >> 8);
		}
		
		break;
		
		case GPIOC :
		if(Copy_u8HalfPort == GPIO_FIRST_HALF )
		{
			Loc_u8Result = GPIOC_IDR;
		}
		else if(Copy_u8HalfPort == GPIO_SECOND_HALF)
		{  
	        Loc_u8Result = (GPIOC_IDR >> 8);
		}
		break;
		
	}
	
	return Loc_u8Result;
	
}


