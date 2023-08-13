/*********************************************************************************/
/* Author    : Gomaa Mohammed                                                      */
/* Version   : V01                                                               */
/* Date      : 19 August 2020                                                     */
/*********************************************************************************/

#ifndef _NVIC_INTERFACE_H_
#define _NVIC_INTERFACE_H_

/*************** exeptions control *****************/
void NVIC_voidInit(void);
void NVIC_voidEnableInterrupt(u8 Copy_s8IntId);
void NVIC_voidDisableInterrupt(u8 Copy_s8IntId);
void NVIC_voidSetPendingFlag(u8 Copy_s8IntId);
void NVIC_voidClearPendingFlag(u8 Copy_s8IntId);
u8   NVIC_voidGetActiveFlag(u8 Copy_s8IntId);
void NVIC_voidSetPriority(u8 Copy_s8IntId,u8 Copy_u8GroupPriority,u8 Copy_u8SubPriority);

/***************** system control *******************/
void __enable_irq(void);
void __disable_irq(void);
void __enable_fault_irq(void);
void __disable_fault_irq(void);
void __ISB(void);
void __DSB(void);
void __DMB(void);
u32 __REV(u32 value);
u32 __REV16(u32 value);
u32 __REVSH(u32 value);
u32 __RBIT(u32 value);
void __SEV(void);
void __WFE(void);
void __WFI(void);
u32 __get_PRIMASK(void);
void __set_PRIMASK(u32 value);
u32 __get_FAULTMASK(void);
void __set_FAULTMASK(u32 value);
u32 __get_BASEPRI(void);
void __set_BASEPRI(u32 value);
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
u32 __LDREXW(u32 *address);
u32 __STREXW(u32 value,u32 *address);
u16 __LDREXH(u16 *address);
u16 __STREXH(u16 value,u16 *address);
u8 __LDREXB( u8 *address);
u8 __STREXB(u8 value, u8 *address);
void __CLREX(void);

// interrupt IDs
#define  MemManage            0
#define  BusFault             1
#define  UsageFault           2
#define  SVCall               3
#define  DebugMonitor         4
#define  PendSV               5
#define  SysTick              6
#define  WWDG                 7 
#define  PVD                  8
#define  TAMPER               9
#define  RTC                  10
#define  FLASH                11
#define  RCC                  12
#define  EXTI0                13
#define  EXTI1                14
#define  EXTI2                15
#define  EXTI3                16
#define  EXTI4                17
#define  DMA1_Channel1        18
#define  DMA1_Channel2        19
#define  DMA1_Channel3        20
#define  DMA1_Channel4        21
#define  DMA1_Channel5        22
#define  DMA1_Channel6        23
#define  DMA1_Channel7        24
#define  ADC1_2               25
#define  USB_HP_CAN_TX        26
#define  USB_LP_CAN_RX0       27
#define  CAN_RX1 CAN RX1      28
#define  CAN_SCE              29
#define  EXTI9_5              30
#define  TIM1_BRK_TIM9        31
#define  TIM1_UP_TIM10        32
#define  TIM1_TRG_COM_TIM11   33
#define  TIM1_CC              34
#define  TIM2                 35
#define  TIM3                 36
#define  TIM4                 37
#define  I2C1_EV              38
#define  I2C1_ER              39
#define  I2C2_EV              40
#define  I2C2_ER              41
#define  SPI1                 42
#define  SPI2                 43
#define  USART1               44
#define  USART2               45
#define  USART3               46
#define  EXTI15_10            47
#define  RTCAlarm             48
#define  USBWakeUp            49
#define  TIM8_BRK_TIM12       50
#define  TIM8_UP_TIM13        51
#define  TIM8_TRG_COM_TIM14   52
#define  TIM8_CC              53
#define  ADC3                 54
#define  FSMC                 55
#define  SDIO                 56
#define  TIM5                 57
#define  SPI3                 58
#define  UART4                59
#define  UART5                60
#define  TIM6                 61
#define  TIM7                 62
#define  DMA2_Channel1        63
#define  DMA2_Channel2        64
#define  DMA2_Channel3        65
#define  DMA2_Channel4_5      66

   
#endif
