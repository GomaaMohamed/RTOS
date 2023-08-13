/*********************************************************************************/
/* Author    : Gomaa Mohammed                                                    */
/* Version   : V01                                                               */
/* Date      : 19 August 2020                                                    */
/*********************************************************************************/

#include      "STD_TYPES.h"
#include      "BIT_MATH.h"


#include      "NVIC_interface.h"
#include      "NVIC_private.h"
#include      "NVIC_config.h"

void NVIC_voidInit(void){

     // set priority group combination
     SCB_AIRCR = PRIORITY_GROUP_COMBINATION;
     
     // set initial group/subgroup priority for the nedded interrupts
     
     // enable needed interrupts 
     
}

void NVIC_voidEnableInterrupt(u8 Copy_s8IntId){

    Copy_s8IntId -= 7;
	if(Copy_s8IntId <= 31)
	{
		NVIC_ISER0 = 1<<(Copy_s8IntId);
	}
	else if(Copy_s8IntId <= 59)
	{
		Copy_s8IntId -= 32;
		NVIC_ISER1 = 1<<(Copy_s8IntId);
	}
}
void NVIC_voidDisableInterrupt(u8 Copy_s8IntId){
       
    Copy_s8IntId -= 7;
	if(Copy_s8IntId <= 31)
	{
		NVIC_ICER0 = 1<<(Copy_s8IntId);
	}
	else if(Copy_s8IntId <= 59)
	{
		Copy_s8IntId -= 32;
		NVIC_ICER1 = 1<<(Copy_s8IntId);
	}
}
void NVIC_voidSetPendingFlag(u8 Copy_s8IntId){

    Copy_s8IntId -= 7;
	if(Copy_s8IntId <= 31)
	{
		NVIC_ISPR0 = 1<<(Copy_s8IntId);
	}
	else if(Copy_s8IntId <= 59)
	{
		Copy_s8IntId -= 32;
		NVIC_ISPR1 = 1<<(Copy_s8IntId);
	}
}
void NVIC_voidClearPendingFlag(u8 Copy_s8IntId){

        Copy_s8IntId -= 7;
	if(Copy_s8IntId <= 31)
	{
		NVIC_ICPR0 = 1<<(Copy_s8IntId);
	}
	else if(Copy_s8IntId <= 59)
	{
		Copy_s8IntId -= 32;
		NVIC_ICPR1 = 1<<(Copy_s8IntId);
	}
}
u8 NVIC_voidGetActiveFlag(u8 Copy_s8IntId){

        Copy_s8IntId -= 7;
	u8 LocalResult;
	if(Copy_s8IntId <= 31)
	{
		LocalResult = GET_BIT(NVIC_IAPR0,Copy_s8IntId);
	}
	else if(Copy_s8IntId <= 59)
	{
		Copy_s8IntId -= 32;
		LocalResult = GET_BIT(NVIC_IAPR1,Copy_s8IntId);
	}
	return LocalResult;
}
void NVIC_voidSetPriority(u8 Copy_s8IntId,u8 Copy_u8GroupPriority,u8 Copy_u8SubPriority){

       u8 Local_u8Priority = Copy_u8SubPriority | (Copy_u8GroupPriority << ((PRIORITY_GROUP_COMBINATION - 0x05FA0300)/256));
	/* Core Periphiral */	
	if(Copy_s8IntId <= 6)
	{       
	    if(Copy_s8IntId <= 2){
		SCB_SHPR[Copy_s8IntId] = Local_u8Priority << 4;
		}
		else if(Copy_s8IntId == 3){
		SCB_SHPR[Copy_s8IntId + 4] = Local_u8Priority << 4;
		}
		else if(Copy_s8IntId > 4){
		SCB_SHPR[Copy_s8IntId + 5] = Local_u8Priority << 4;
		}
	}
	/* other Periphiral */
    else if(Copy_s8IntId > 6)
	{       
		NVIC_IPR[Copy_s8IntId-7] = Local_u8Priority << 4;
	}	
}

/**************** system calls ****************/
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

u32 __REV(u32 value) {
    u32 result;
    asm("rev %0, %1" : "=r" (result) : "r" (value));
    return result;
}

u32 __REV16(u32 value) {
    u32 result;
    asm("rev16 %0, %1" : "=r" (result) : "r" (value));
    return result;
}

u32 __REVSH(u32 value) {
    u32 result;
    asm("revsh %0, %1" : "=r" (result) : "r" (value));
    return result;
}

u32 __RBIT(u32 value) {
    u32 result;
    asm("rbit %0, %1" : "=r" (result) : "r" (value));
    return result;
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
	u32 result;
    asm("MRS %0, PRIMASK" : "=r" (result));
	result &= 1;
	return result;
}

void __set_PRIMASK(u32 value){
	asm("MSR PRIMASK, %0" : : "r" (value));
}

u32 __get_FAULTMASK(void){
	u32 result;
    asm("MRS %0, FAULTMASK" : "=r" (result));
	result &= 1;
    return result;
}

void __set_FAULTMASK(u32 value){
	asm("MSR FAULTMASK, %0" : : "r" (value));
}

u32 __get_BASEPRI(void){
	u32 result;
    asm("MRS %0, BASEPRI" : "=r" (result));
	result = (result >> 4);
	return result;
}

void __set_BASEPRI(u32 value){
	asm("MSR BASEPRI, %0" : : "r" (value));
}

u32 __get_CONTROL(void){
	u32 result;
    asm("MRS %0, CONTROL" : "=r" (result));
	result &= 3;
    return result;
}

void __set_CONTROL(u32 value){
	asm("MSR CONTROL, %0" : : "r" (value));
}

u32 __get_MSP(void){
	u32 result;
    asm("MRS %0, MSP" : "=r" (result));
    return result;
}

void __set_MSP(u32 TopOfMainStack){
	asm("MSR MSP, %0" : : "r" (TopOfMainStack));
}

u32 __get_PSP(void){
	u32 result;
    asm("MRS %0, PSP" : "=r" (result));
    return result;
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

u32 __LDREXW(u32 *address) {
    u32 result;
    asm volatile("ldrex %0, [%1]" : "=r" (result) : "r" (address));
    return result;
}

u32 __STREXW(u32 value, u32 *address) {
    u32 result;
    asm volatile("strex %0, %1, [%2]" : "=&r" (result) : "r" (value), "r" (address));
    return result;
}

u16 __LDREXH( u16 *address) {
    u16 result;
    asm volatile("ldrexh %0, [%1]" : "=r" (result) : "r" (address));
    return result;
}

u16 __STREXH(u16 value, u16 *address) {
    u16 result;
    asm volatile("strexh %0, %1, [%2]" : "=&r" (result) : "r" (value), "r" (address));
    return result;
}

u8 __LDREXB(u8 *address){
    u8 result;
    asm volatile("ldrexb %0, [%1]" : "=r" (result) : "r" (address));
    return result;
}

u8 __STREXB(u8 value, u8 *address) {
    u8 result;
    asm volatile("strexb %0, %1, [%2]" : "=&r" (result) : "r" (value), "r" (address));
    return result;
}

void __CLREX(void){
	asm("clrex" ::: "memory");
}