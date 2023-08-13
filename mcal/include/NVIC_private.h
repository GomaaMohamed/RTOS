/*********************************************************************************/
/* Author    : Gomaa Mohammed                                                    */
/* Version   : V01                                                               */
/* Date      : 19 August 2020                                                    */
/*********************************************************************************/

#ifndef _NVIC_PRIVATE_H_
#define _NVIC_PRIVATE_H_

/* Registers Definition */
#define  NVIC_ISER0    *((u32 *)(0xE000E100))             /* Enable External Interrupt from 0 to 31  */
#define  NVIC_ISER1    *((u32 *)(0xE000E104))             /* Enable External Interrupt from 32 to 59  */

#define  NVIC_ICER0    *((u32 *)(0xE000E180))             /* Disable External Interrupt from 0 to 31  */
#define  NVIC_ICER1    *((u32 *)(0xE000E184))             /* Disable External Interrupt from 32 to 59  */

#define  NVIC_ISPR0    *((u32 *)(0xE000E200))             /* Set Pending Flag from 0 to 31  */
#define  NVIC_ISPR1    *((u32 *)(0xE000E204))             /* Set Pending Interrupt from 32 to 59  */

#define  NVIC_ICPR0    *((u32 *)(0xE000E280))             /* Clear Pending Flag from 0 to 31  */
#define  NVIC_ICPR1    *((u32 *)(0xE000E284))             /* Clear Pending Interrupt from 32 to 59  */
#define  NVIC_IAPR0    *((volatile u32 *)(0xE000E300))    /* Get Active Flag from 0 to 31  */
#define  NVIC_IAPR1    *((volatile u32 *)(0xE000E304))     /* Get Active Interrupt from 32 to 59  */


#define  NVIC_IPR      ((volatile u8 *)(0xE000E300))        /* Manage Interrupt Priority */
#define  SCB_SHPR      ((volatile u8 *)(0xE000ED18))        /* Manage Interrupt Priority */

#define  SCB_AIRCR    *((volatile u32 *)(0xE000ED0C))  /* Control NVIC_IPR */
#define  SCB_ICSR     *((volatile u32 *)(0xE000ED04))  /* Control NVIC_IPR */
#define  SCB_VTOR     *((volatile u32 *)(0xE000ED08))
#define  SCB_CCR      *((volatile u32 *)(0xE000ED14))


// priority group definitions

#define     NVIC_GROUP3   0x05FA0300   // 4 bits for group (IPR)  ->  group
#define     NVIC_GROUP4   0x05FA0400   // 3 bits for group & 1 bit for sub
#define     NVIC_GROUP5   0x05FA0500   // 2 bits for group & 2 bit for sub
#define     NVIC_GROUP6   0x05FA0600   // 1 bits for group & 3 bit for sub
#define     NVIC_GROUP7   0x05FA0700   // 0 bits for group & 4 bit for sub

#endif

