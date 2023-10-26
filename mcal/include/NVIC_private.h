/*****************************************************************************
* @file:    NVIC_private.h
* @author:  Copyright (c) 2023 Gomaa Mohammed Gomaa.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Thu, 5 Oct 2023 17:21:12 +0200
* @brief:   Nested Vectored Interrupt Controller(NVIC) Driver for STM32F103
******************************************************************************/
#ifndef _NVIC_PRIVATE_H
#define _NVIC_PRIVATE_H

/* ==================================================================== */
/* =================== Private Variables and Macros =================== */
/* ==================================================================== */

/* Registers Definition of NVIC */
#define  NVIC_ISER0    *((volatile u32 *)(0xE000E100))  // Enable External Interrupt from 0 to 31  
#define  NVIC_ISER1    *((volatile u32 *)(0xE000E104))  // Enable External Interrupt from 32 to 59  

#define  NVIC_ICER0    *((volatile u32 *)(0xE000E180))  // Disable External Interrupt from 0 to 31  
#define  NVIC_ICER1    *((volatile u32 *)(0xE000E184))  // Disable External Interrupt from 32 to 59  

#define  NVIC_ISPR0    *((volatile u32 *)(0xE000E200))  // Set Pending Flag from 0 to 31  
#define  NVIC_ISPR1    *((volatile u32 *)(0xE000E204))  // Set Pending Interrupt from 32 to 59  

#define  NVIC_ICPR0    *((volatile u32 *)(0xE000E280))  // Clear Pending Flag from 0 to 31  
#define  NVIC_ICPR1    *((volatile u32 *)(0xE000E284))  // Clear Pending Interrupt from 32 to 59  
#define  NVIC_IAPR0    *((volatile u32 *)(0xE000E300))  // Get Active Flag from 0 to 31  
#define  NVIC_IAPR1    *((volatile u32 *)(0xE000E304))  // Get Active Interrupt from 32 to 59  


#define  NVIC_IPR      ((volatile u8 *)(0xE000E300))    // Manage Interrupt Priority 
#define  SCB_SHPR      ((volatile u8 *)(0xE000ED18))    // Manage Interrupt Priority 

#define  SCB_CPUID    *((volatile u32 *)(0xE000ED00))
#define  SCB_AIRCR    *((volatile u32 *)(0xE000ED0C))   // Control NVIC_IPR 
#define  SCB_ICSR     *((volatile u32 *)(0xE000ED04))   // Control NVIC_IPR 
#define  SCB_VTOR     *((volatile u32 *)(0xE000ED08))
#define  SCB_CCR      *((volatile u32 *)(0xE000ED14))


// priority group definitions
#define     NVIC_GROUP3   0x05FA0300   // 4 bits for group (IPR)  ->  group
#define     NVIC_GROUP4   0x05FA0400   // 3 bits for group & 1 bit for sub
#define     NVIC_GROUP5   0x05FA0500   // 2 bits for group & 2 bit for sub
#define     NVIC_GROUP6   0x05FA0600   // 1 bits for group & 3 bit for sub
#define     NVIC_GROUP7   0x05FA0700   // 0 bits for group & 4 bit for sub

#endif

