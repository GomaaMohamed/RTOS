/*****************************************************************************
* @file:    NVIC_interface.h
* @author:  Copyright (c) 2023 Gomaa Mohammed Gomaa.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Thu, 5 Oct 2023 17:21:12 +0200
* @brief:   Nested Vectored Interrupt Controller(NVIC) Driver for STM32F103
******************************************************************************/
#ifndef _NVIC_INTERFACE_H
#define _NVIC_INTERFACE_H

/* ==================================================================== */
/* ======================= public data types ========================== */
/* ==================================================================== */

/* Interrupt Id data type*/
typedef enum
{
    NVIC_MemManage=0,
    NVIC_BusFault,
    NVIC_UsageFault,
    NVIC_SVCall,
    NVIC_DebugMonitor,
    NVIC_PendSV,
    NVIC_SysTick,
    NVIC_WWDG,
    NVIC_PVD,
    NVIC_TAMPER,
    NVIC_RTC,
    NVIC_FLASH,
    NVIC_RCC,
    NVIC_EXTI0,
    NVIC_EXTI1,
    NVIC_EXTI2,
    NVIC_EXTI3,
    NVIC_EXTI4,
    NVIC_DMA1_Channel1,
    NVIC_DMA1_Channel2,
    NVIC_DMA1_Channel3,
    NVIC_DMA1_Channel4,
    NVIC_DMA1_Channel5,
    NVIC_DMA1_Channel6,
    NVIC_DMA1_Channel7,
    NVIC_ADC1_2,
    NVIC_USB_HP_CAN_TX,
    NVIC_USB_LP_CAN_RX0,
    NVIC_CAN_RX1,
    NVIC_CAN_SCE,
    NVIC_EXTI9_5,
    NVIC_TIM1_BRK_TIM9,
    NVIC_TIM1_UP_TIM10,
    NVIC_TIM1_TRG_COM_TIM11,
    NVIC_TIM1_CC,
    NVIC_TIM2,
    NVIC_TIM3,
    NVIC_TIM4,
    NVIC_I2C1_EV,
    NVIC_I2C1_ER,
    NVIC_I2C2_EV,
    NVIC_I2C2_ER,
    NVIC_SPI1,
    NVIC_SPI2,
    NVIC_USART1,
    NVIC_USART2,
    NVIC_USART3,
    NVIC_EXTI15_10,
    NVIC_RTCAlarm,
    NVIC_USBWakeUp,
    NVIC_TIM8_BRK_TIM12,
    NVIC_TIM8_UP_TIM13,
    NVIC_TIM8_TRG_COM_TIM14,
    NVIC_TIM8_CC,
    NVIC_ADC3,
    NVIC_FSMC,
    NVIC_SDIO,
    NVIC_TIM5,
    NVIC_SPI3,
    NVIC_UART4,
    NVIC_UART5,
    NVIC_TIM6,
    NVIC_TIM7,
    NVIC_DMA2_Channel1,
    NVIC_DMA2_Channel2,
    NVIC_DMA2_Channel3,
    NVIC_DMA2_Channel4_5,
    INTERRUPT_ERR
} InterruptId_type;


/* ==================================================================== */
/* ==================== Public Functions Declaration ================== */
/* ==================================================================== */

/***************************** Exeptions Control Prototypes ****************************/

/**
 * @brief---------------------> Initialize nvic module
 * @param---------------------> None
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */

void NVIC_init(void);

/**
 * @brief---------------------> Enable specific interrupt
 * @parameter1----------------> (InterruptId) interrupt id
 * @return--------------------> None
 * @preconditions-------------> Interrupts are enabled and nvic is initialized
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
void NVIC_enableInterrupt(InterruptId_type InterruptId);

/**
 * @brief---------------------> Disable specific interrupt
 * @parameter1----------------> (InterruptId) interrupt id
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
void NVIC_disableInterrupt(InterruptId_type InterruptId);

/**
 * @brief---------------------> Set pending flag
 * @parameter1----------------> (InterruptId) interrupt id
 * @return--------------------> None
 * @preconditions-------------> Interrupts are enabled and nvic is initialized
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
void NVIC_setPendingFlag(InterruptId_type InterruptId);

/**
 * @brief---------------------> Clear pending flag
 * @parameter1----------------> (InterruptId) interrupt id
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
void NVIC_clearPendingFlag(InterruptId_type InterruptId);

/**
 * @brief---------------------> Get active flag
 * @parameter1----------------> (InterruptId) interrupt id
 * @return--------------------> Active flag
 * @preconditions-------------> Interrupts are enabled and nvic is initialized
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
u8   NVIC_getActiveFlag(InterruptId_type InterruptId);

/**
 * @brief---------------------> Set priority
 * @parameter1----------------> (InterruptId) interrupt id
 * @parameter2----------------> (GroupPriority) group priority
 * @parameter3----------------> (SubPriority) sub priority
 * @return--------------------> None
 * @preconditions-------------> Interrupts are enabled and nvic is initialized
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
void NVIC_setPriority(InterruptId_type InterruptId,u8 GroupPriority,u8 SubPriority);


/***************************** System Control Prototypes ****************************/
void __enable_irq(void);
void __disable_irq(void);
void __enable_fault_irq(void);
void __disable_fault_irq(void);
void __ISB(void);
void __DSB(void);
void __DMB(void);
u32 __REV(u32 Value);
u32 __REV16(u32 Value);
u32 __REVSH(u32 Value);
u32 __RBIT(u32 Value);
void __SEV(void);
void __WFE(void);
void __WFI(void);
u32 __get_PRIMASK(void);
void __set_PRIMASK(u32 Value);
u32 __get_FAULTMASK(void);
void __set_FAULTMASK(u32 Value);
u32 __get_BASEPRI(void);
void __set_BASEPRI(u32 Value);
u32 __get_CONTROL(void);
void __set_CONTROL(u32 value);
u32 __get_MSP(void);
void __set_MSP(u32 TopOfMainStack);
u32 __get_PSP(void);
void __set_PSP(u32 TopOfProcStack);
void __set_PENDSV(void);
void __clr_PENDSV(void);
void __set_EXCEPTION_ALIGN4(void);
void __set_EXCEPTION_ALIGN8(void);
void __set_VECTOR_TABLE_IN_RAM(void);
void __set_VECTOR_TABLE_IN_FLASH(void);
void __set_VTOR(u32 VectorTableOffset);
void __reset_System(void);
u32 __LDREXW(u32 *Address);
u32 __STREXW(u32 Value,u32 *Address);
u16 __LDREXH(u16 *Address);
u16 __STREXH(u16 Value,u16 *Address);
u8 __LDREXB( u8 *Address);
u8 __STREXB(u8 Value, u8 *Address);
void __CLREX(void);
   
#endif
