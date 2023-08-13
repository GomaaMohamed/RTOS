/*********************************************************************************/
/* Author    : Gomaa Mohammed                                                      */
/* Version   : V01                                                               */
/* Date      : 24 August 2020                                                     */
/*********************************************************************************/

#include      "STD_TYPES.h"
#include      "BIT_MATH.h"


#include      "STK_interface.h"
#include      "STK_private.h"
#include      "STK_config.h"

void STK_voidInit(void)
{
	
#if   CLK_SOURCE  ==  STK_AHB
/* Disable STK - Disable STK Interrupt - Set clock source AHB */
	STK->CTRL = 0x00000004;

#elif   CLK_SOURCE  ==  STK_AHB_DIV_8
    /* Disable STK - Disable STK Interrupt - Set clock source AHB/8 */
	STK->CTRL = 0;
#endif
	
}
void STK_voidSetBusyWait(u32 Copy_u32Ticks)
{   
    
	/* Stop Timer and Make Values = 0 */
	CLR_BIT(STK->CTRL, 0);
	STK->LOAD = 0;
	STK->VAL  = 0;
	/* Load Value To Timer */
	STK->LOAD = Copy_u32Ticks;
	/* Start Timer */
	SET_BIT(STK->CTRL,0);
	/* Check Flag */
	while((GET_BIT(STK->CTRL,16)) == 0){
		asm("NOP");
		
	}
	
}
void STK_voidSetIntervalSingle(u32 Copy_u32Ticks,void (*Copy_ptr)(void))
{  
    /* Stop Timer */
	SET_BIT(STK->CTRL, 0);
	STK -> LOAD = 0;
	STK -> VAL  = 0;
    /* Set Mode to Single */
	STK_u8ModeOfInterval = STK_SINGLE_INTERVAL;
    /* Load ticks to load register */
	STK->LOAD = Copy_u32Ticks;
	/* Enable STK Interrupt */
	SET_BIT(STK->CTRL,1);
	/* Start Timer */
	SET_BIT(STK->CTRL,0);
	/* Save CallBack */
	STK_Callback = Copy_ptr;
}
void STK_voidSetIntervalPeriodic(u32 Copy_u32Ticks,void (*Copy_ptr)(void))
{  
    
    /* Set Mode to Single */
	STK_u8ModeOfInterval = STK_PERIOD_INTERVAL;
    /* Load ticks to load register */
	STK->LOAD = Copy_u32Ticks;
	/* Enable STK Interrupt */
	SET_BIT(STK->CTRL,1);
	/* Start Timer */
	SET_BIT(STK->CTRL,0);
	/* Save CallBack */
	STK_Callback = Copy_ptr;
}
void STK_voidStopInterval(void)
{
	/* Disable STK Interrupt */
	CLR_BIT(STK->CTRL,1);
	/* Stop Timer */
	CLR_BIT(STK->CTRL,0);
	
	/* Stop Timer */
	SET_BIT(STK->CTRL, 0);
	STK->LOAD = 0;
	STK->VAL  = 0;
	
	
}
u32  STK_u32GetElapsedTime(void)
{
	return (STK->LOAD - STK->VAL);
}
u32  STK_u32GetRemainingTime(void)
{
	return (STK->VAL);
}
void STK_voidEnableInterrupt(void)
{
	SET_BIT(STK->CTRL,1);
}
void STK_voidDisableInterrupt(void)
{
	CLR_BIT(STK->CTRL, 1);
}
void STK_voidSetCallback(void (*Copy_ptr)(void))
{
	/* Save CallBack */
	STK_Callback = Copy_ptr;
}
void STK_voidSetFrequency(void (*Copy_ptr)(void))
{
	/* Save CallBack */
	STK_Callback = Copy_ptr;
}

/* ISR of STK */
void SysTick_Handler(void)
{u8 Local_u8Temporary;
	
	if (STK_u8ModeOfInterval == STK_SINGLE_INTERVAL)
	{
		/* Disable STK Interrupt */
		CLR_BIT(STK->CTRL, 1);
	
		/* Stop Timer */
		CLR_BIT(STK->CTRL, 0);
		STK -> LOAD = 0;
		STK -> VAL  = 0;
	}
	
	/* Callback notification */
	STK_Callback();
	
	/* Clear interrupt flag */
	Local_u8Temporary = GET_BIT(STK->CTRL,16);
}
