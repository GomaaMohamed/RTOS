/*****************************************************************************
* @file:    GPIO_program.c
* @author:  Copyright (c) 2023 Gomaa Mohammed Gomaa.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Thu, 5 Oct 2023 17:21:12 +0200
* @brief:   General Purpose Input Output(GPIO) Driver for STM32F103
******************************************************************************/

/* ==================================================================== */
/* ========================== include files =========================== */
/* ==================================================================== */
#include      "STD_TYPES.h"
#include      "BIT_MATH.h"

#include      "NVIC_interface.h"
#include      "NVIC_private.h"
#include      "NVIC_config.h"

/* ==================================================================== */
/* ================= Public Functions Implementation ================== */
/* ==================================================================== */

// Function to initialize NVIC module
void NVIC_init(void){

    // set priority group combination
    SCB_AIRCR = PRIORITY_GROUP_COMBINATION;
    
    // set initial group/subgroup priority for the nedded interrupts
    
    // enable needed interrupts 
     
}

// Function to enable an interrupt
void NVIC_enableInterrupt(InterruptId_type InterruptId){
	
	// Validate input parameters
	ASSERT(InterruptId >= 0 && InterruptId < INTERRUPT_ERR);

	// Make the offset of internal exeptions
    InterruptId -= 7;

	// Select an interrupt to be enabled
	if(InterruptId <= 31)
	{
		NVIC_ISER0 = 1<<(InterruptId);
	}
	else if(InterruptId <= 59)
	{
		InterruptId -= 32;
		NVIC_ISER1 = 1<<(InterruptId);
	}
}

// Function to disable an interrupt
void NVIC_disableInterrupt(InterruptId_type InterruptId){
       
    // Make the offset of internal exeptions
    InterruptId -= 7;

	// Select an interrupt to be disabled
	if(InterruptId <= 31)
	{
		NVIC_ICER0 = 1<<(InterruptId);
	}
	else if(InterruptId <= 59)
	{
		InterruptId -= 32;
		NVIC_ICER1 = 1<<(InterruptId);
	}
}

// Function to set pending flag
void NVIC_setPendingFlag(InterruptId_type InterruptId){

	// Validate input parameters
	ASSERT(InterruptId >= 0 && InterruptId < INTERRUPT_ERR);

    // Make the offset of internal exeptions
    InterruptId -= 7;

	// Select an interrupt to set its pending flag
	if(InterruptId <= 31)
	{
		NVIC_ISPR0 = 1<<(InterruptId);
	}
	else if(InterruptId <= 59)
	{
		InterruptId -= 32;
		NVIC_ISPR1 = 1<<(InterruptId);
	}
}

// Function to clear pending flag
void NVIC_clearPendingFlag(InterruptId_type InterruptId){

	// Validate input parameters
	ASSERT(InterruptId >= 0 && InterruptId < INTERRUPT_ERR);

    // Make the offset of internal exeptions
    InterruptId -= 7;

	// Select an interrupt to clear its pending flag
	if(InterruptId <= 31)
	{
		NVIC_ICPR0 = 1<<(InterruptId);
	}
	else if(InterruptId <= 59)
	{
		InterruptId -= 32;
		NVIC_ICPR1 = 1<<(InterruptId);
	}
}

// Function to get the active flag
u8 NVIC_getActiveFlag(InterruptId_type InterruptId){

	// Validate input parameters
	ASSERT(InterruptId >= 0 && InterruptId < INTERRUPT_ERR);

    // Make the offset of internal exeptions
    InterruptId -= 7;

	u8 Result;

	// Select an interrupt to get active flag
	if(InterruptId <= 31)
	{
		Result = GET_BIT(NVIC_IAPR0,InterruptId);
	}
	else if(InterruptId <= 59)
	{
		InterruptId -= 32;
		Result = GET_BIT(NVIC_IAPR1,InterruptId);
	}
	return Result;
}

// Function to set priority
void NVIC_setPriority(InterruptId_type InterruptId,u8 GroupPriority,u8 SubPriority){

	// Validate input parameters
	ASSERT(InterruptId >= 0 && InterruptId < INTERRUPT_ERR);

	// Adjust priority
    u8 Priority = SubPriority | (GroupPriority << ((PRIORITY_GROUP_COMBINATION - 0x05FA0300)/256));
	
	// Set Core Periphirals	priority
	if(InterruptId <= 6)
	{       
	    if(InterruptId <= 2)
		{
			SCB_SHPR[InterruptId] = Priority << 4;
		}
		else if(InterruptId == 3)
		{
			SCB_SHPR[InterruptId + 4] = Priority << 4;
		}
		else if(InterruptId > 4)
		{
			SCB_SHPR[InterruptId + 5] = Priority << 4;
		}
		else 
		{
			// Do nothing
		}
	}
	// Set other Periphirals priority
    else if(InterruptId > 6)
	{       
		NVIC_IPR[InterruptId-7] = Priority << 4;
	}	
	else 
	{
		// Do nothing
	}
	
}

/********************************* System calls *********************************/
void __enable_irq(void){
    asm("CPSIE i");
}

void __disable_irq(void){
	asm("CPSID i");
}

void __enable_fault_irq(void){
    asm("CPSIE f");
}

void __disable_fault_irq(void){
	asm("CPSID f");
}

void __ISB(void){
	asm("ISB");
}

void __DSB(void){
	asm("DSB");
}

void __DMB(void){
	asm("DMB");
}

u32 __REV(u32 Value) {
    u32 Result;
    asm("rev %0, %1" : "=r" (Result) : "r" (Value));
    return Result;
}

u32 __REV16(u32 Value) {
    u32 Result;
    asm("rev16 %0, %1" : "=r" (Result) : "r" (Value));
    return Result;
}

u32 __REVSH(u32 Value) {
    u32 Result;
    asm("revsh %0, %1" : "=r" (Result) : "r" (Value));
    return Result;
}

u32 __RBIT(u32 Value) {
    u32 Result;
    asm("rbit %0, %1" : "=r" (Result) : "r" (Value));
    return Result;
}

void __SEV(void){
	asm("SEV");
}

void __WFE(void){
	asm("WFE");
}

void __WFI(void){
	asm("WFI");
}

u32 __get_PRIMASK(void){
	u32 Result;
    asm("MRS %0, PRIMASK" : "=r" (Result));
	Result &= 1;
	return Result;
}

u32 __get_CPUID(void)
{
	return SCB_CPUID;
}

void __set_PRIMASK(u32 Value){
	asm("MSR PRIMASK, %0" : : "r" (Value));
}

u32 __get_FAULTMASK(void){
	u32 Result;
    asm("MRS %0, FAULTMASK" : "=r" (Result));
	Result &= 1;
    return Result;
}

void __set_FAULTMASK(u32 Value){
	asm("MSR FAULTMASK, %0" : : "r" (Value));
}

u32 __get_BASEPRI(void){
	u32 Result;
    asm("MRS %0, BASEPRI" : "=r" (Result));
	Result = (Result >> 4);
	return Result;
}

void __set_BASEPRI(u32 Value){
	asm("MSR BASEPRI, %0" : : "r" (Value));
}

u32 __get_CONTROL(void){
	u32 Result;
    asm("MRS %0, CONTROL" : "=r" (Result));
	Result &= 3;
    return Result;
}

void __set_CONTROL(u32 Value){
	asm("MSR CONTROL, %0" : : "r" (Value));
}

u32 __get_MSP(void){
	u32 Result;
    asm("MRS %0, MSP" : "=r" (Result));
    return Result;
}

void __set_MSP(u32 TopOfMainStack){
	asm("MSR MSP, %0" : : "r" (TopOfMainStack));
}

u32 __get_PSP(void){
	u32 Result;
    asm("MRS %0, PSP" : "=r" (Result));
    return Result;
}

void __set_PSP(u32 TopOfProcStack){
	asm("MSR PSP, %0" : : "r" (TopOfProcStack));
}


void __set_PENDSV(void){
   SET_BIT(SCB_ICSR, 28);
}

void __clr_PENDSV(void){
   SET_BIT(SCB_ICSR, 27);
}

void __reset_System(void){
	SET_BIT(SCB_AIRCR, 2);
}

void __set_EXCEPTION_ALIGN4(void){
    CLR_BIT(SCB_CCR, 9);
}

void __set_EXCEPTION_ALIGN8(void){
    SET_BIT(SCB_CCR, 9);
}

void __set_VECTOR_TABLE_IN_RAM(void){
    SET_BIT(SCB_VTOR, 29);
}

void __set_VECTOR_TABLE_IN_FLASH(void){
	CLR_BIT(SCB_VTOR, 29);
}

void __set_VTOR(u32 VectorTableOffset){
	SCB_VTOR = VectorTableOffset << 9;
}

u32 __LDREXW(u32 *Address) {
    u32 Result;
    asm volatile("ldrex %0, [%1]" : "=r" (Result) : "r" (Address));
    return Result;
}

u32 __STREXW(u32 Value, u32 *Address) {
    u32 Result;
    asm volatile("strex %0, %1, [%2]" : "=&r" (Result) : "r" (Value), "r" (Address));
    return Result;
}

u16 __LDREXH( u16 *Address) {
    u16 Result;
    asm volatile("ldrexh %0, [%1]" : "=r" (Result) : "r" (Address));
    return Result;
}

u16 __STREXH(u16 Value, u16 *Address) {
    u16 Result;
    asm volatile("strexh %0, %1, [%2]" : "=&r" (Result) : "r" (Value), "r" (Address));
    return Result;
}

u8 __LDREXB(u8 *Address){
    u8 Result;
    asm volatile("ldrexb %0, [%1]" : "=r" (Result) : "r" (Address));
    return Result;
}

u8 __STREXB(u8 Value, u8 *Address) {
    u8 Result;
    asm volatile("strexb %0, %1, [%2]" : "=&r" (Result) : "r" (Value), "r" (Address));
    return Result;
}

void __CLREX(void){
	asm("clrex" ::: "memory");
}
