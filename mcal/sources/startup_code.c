#include "STD_TYPES.h"

//extern the start and the end of all Memory Sections that defined in the linker script
extern u32  __intvects_start__  ;
extern u32  __intvects_end__  ;
extern u32  __text_start__  ;
extern u32  __text_end__  ;
extern u32  __rodata_start__  ;
extern u32  __rodata_end__  ;
extern u32  __data_start__  ;
extern u32  __data_end__  ;
extern u32  __data_load__  ;
extern u32  __bss_end__  ;
extern u32  __bss_start__  ;
extern u32  __stack__  ;
extern int main(void);
extern u32 _estack;

// weak declarations for handlers
void __attribute__((weak)) Reset_Handler(void);
void __attribute__((weak)) NMI_Handler(void);
void __attribute__((weak)) HardFault_Handler(void);
void __attribute__((weak)) SVCall_Handler(void);
void __attribute__((weak)) PendSV_Handler(void);
void __attribute__((weak)) SysTick_Handler(void);
void __attribute__((weak)) TIM2_IRQHandler(void);

// Definitions
#define SCB_VTOR   *((volatile u32*)0xE000ED08)
#define FLASH_BASE  ((u32)0x08000000)
#define OFFSET 0x0000 
typedef void (* const pHandler)(void);

//Force an Array of Vectors to be stored in .intvects Section
__attribute__((section(".intvects")))
pHandler __isr_vectors[] = {
	[0]=(pHandler)&_estack, // initial stack pointer
	[1]=Reset_Handler,		
    [2]=HardFault_Handler, 
    [11]=SVCall_Handler,
    [14]=PendSV_Handler,  
	[15]=SysTick_Handler,
	[44]=TIM2_IRQHandler
};
void NMI_Handler(void){while(1);}
void HardFault_Handler(void){while(1);}
void Reset_Handler(void){

    //Initialize Stack Pointer
	asm("LDR r0, =0x20005000");
	asm("MOV sp, r0");

    //Disable all Interrupts and Faults
	asm("CPSID i");
    asm("CPSID f");
	
	//Assigen the Bounderies of the SRAM and Flash Sections 
	u32 *ptr2sbss = (u32 *)&__bss_start__;
	u32 *ptr2ebss = (u32 *)&__bss_end__;
	u32 *ptr2sdes = (u32 *)&__data_start__;
	u32 *ptr2edes = (u32 *)&__data_end__;
	u32 *ptr2src = (u32 *)&__data_load__;
	
    //Initialize .data Section
	while(ptr2sdes < ptr2edes){
		
		*ptr2sdes++ = *ptr2src++ ;
	} 

	//Initialize .bss Section with Zeros
	while(ptr2sbss < ptr2ebss){
           *ptr2sbss++ = 0;
		   }

	//Relocate Vector Table 
	SCB_VTOR = FLASH_BASE | (OFFSET & (u32)0x1FFFFF80);
	asm("DMB");
	asm("DSB");

	//Enable all Interrupts and Faults
    asm("CPSIE i");
    asm("CPSIE f");

	//Call Main
	main();
	
	//Protect the CPU
	while(1);
	
}

  
