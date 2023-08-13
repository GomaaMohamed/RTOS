/***************************************/
/* Author  :Gomaa                      */
/* Date    :8 Aug 2020                 */
/* Version :V01                        */
/***************************************/

#include  "STD_TYPES.h"
#include  "BIT_MATH.h"

#include  "RCC_interface.h"
#include  "RCC_private.h"
#include  "RCC_config.h"

void RCC_voidEnableClock(u8 Copy_u8BusId,u8 Copy_u8PerId){
	
	if (Copy_u8PerId <=31){
		switch (Copy_u8BusId){
			case RCC_AHB  : SET_BIT(RCC_AHBENR , Copy_u8PerId);  break;
			case RCC_APB1 : SET_BIT(RCC_APB1ENR , Copy_u8PerId);  break;
			case RCC_APB2 : SET_BIT(RCC_APB2ENR , Copy_u8PerId);  break;
			
			
		}
    	
		
		
	}
	
}

void RCC_voidDisableClock(u8 Copy_u8BusId,u8 Copy_u8PerId){
	
	if (Copy_u8PerId <=31){
		switch (Copy_u8BusId){
			case RCC_AHB  : CLR_BIT(RCC_AHBENR , Copy_u8PerId);  break;
			case RCC_APB1 : CLR_BIT(RCC_APB1ENR , Copy_u8PerId);  break;
			case RCC_APB2 : CLR_BIT(RCC_APB2ENR , Copy_u8PerId);  break;
			
			
		}
    	
		
		
	}
	
}

void RCC_voidInitSysClock(void){
#if       RCC_CLOCK_TYPE == RCC_HSE_CRYSTAL
RCC_CR    =  0x00010001;       /* Enable HSE Crystal*/
RCC_CFGR  =  0x00000001;
#elif    RCC_CLOCK_TYPE == RCC_HSE_RC
RCC_CR    =  0x00050000 ;      /* Enable HSE RC */
RCC_CFGR  =  0x00000001;
#elif	   RCC_CLOCK_TYPE == RCC_HSI
RCC_CR    =  0x00000001 ;      /* Enable HSI */
RCC_CFGR  =  0x00000000;
#elif     RCC_CLOCK_TYPE == RCC_PLL
       /* Enable PLL */
	 u32  Copy_u32BitField = RCC_MUL_VAL;
	 Copy_u32BitField = Copy_u32BitField<<18;
     #if          RCC_PLL_INPUT == RCC_PLL_IN_HSI_DIV_2
	 RCC_CR    =  0x01000000;	 /* Enable HSI */
     RCC_CFGR  |= Copy_u32BitField;
	 CLR_BIT(RCC_CFGR,16);
	 CLR_BIT(RCC_CFGR,17);
	 #elif       RCC_PLL_INPUT == RCC_PLL_IN_HSE_DIV_2
	 RCC_CR    =  0x01000000;       /* Enable HSI */
	 RCC_CFGR  |= Copy_u32BitField;
	 SET_BIT(RCC_CFGR,16);
	 SET_BIT(RCC_CFGR,17);
	 #elif       RCC_PLL_INPUT == RCC_PLL_IN_HSE
	 RCC_CR    =  0x01000000 ;      /* Enable HSI */
	 RCC_CFGR  |= Copy_u32BitField;
	 SET_BIT(RCC_CFGR,16);
	 CLR_BIT(RCC_CFGR,17);
	 #endif 
#else
    #error("You chosed wrong clock type")
#endif
}
