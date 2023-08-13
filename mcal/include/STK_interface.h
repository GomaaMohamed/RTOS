/*********************************************************************************/
/* Author    : Gomaa Mohammed                                                    */
/* Version   : V01                                                               */
/* Date      : 24 August 2020                                                    */
/*********************************************************************************/

#ifndef _STK_INTERFACE_H_
#define _STK_INTERFACE_H_



/* Apply ClK Choice from Config 
   Disable SysTick Interrupt
   Disable SysTick 
   
*/
void STK_voidInit(void);
void STK_voidSetBusyWait(u32 Copy_u32Ticks);
void STK_voidSetIntervalSingle(u32 Copy_u32Ticks,void (*Copy_ptr)(void));
void STK_voidSetIntervalPeriodic(u32 Copy_u32Ticks,void (*Copy_ptr)(void));
void STK_voidStopInterval(void);
u32  STK_u32GetElapsedTime(void);
u32  STK_u32GetRemainingTime(void);
void STK_voidEnableInterrupt(void);
void STK_voidDisableInterrupt(void);
void STK_voidSetCallback(void (*Copy_ptr)(void));



#endif