/*********************************************************************************/
/* Author    : Gomaa Mohammed                                                      */
/* Version   : V01                                                               */
/* Date      : 12 August 2020                                                     */
/*********************************************************************************/

#ifndef _GPIO_PRIVATE_H_
#define _GPIO_PRIVATE_H_

/* Base Adress Definitions*/
#define   GPIOA_BASE_ADRESS  0x40010800
#define   GPIOB_BASE_ADRESS  0x40010C00
#define   GPIOC_BASE_ADRESS  0x40011000

/* Register Definition of PORTA*/
#define   GPIOA_CRL   *((u32*)(GPIOA_BASE_ADRESS+0x00))
#define   GPIOA_CRH   *((u32*)(GPIOA_BASE_ADRESS+0x04))
#define   GPIOA_IDR   *((u32*)(GPIOA_BASE_ADRESS+0x08))
#define   GPIOA_ODR   *((u32*)(GPIOA_BASE_ADRESS+0x0C))
#define   GPIOA_BSRR  *((u32*)(GPIOA_BASE_ADRESS+0x10))
#define   GPIOA_BRR   *((u32*)(GPIOA_BASE_ADRESS+0x14))
#define   GPIOA_LCKR   *((u32*)(GPIOA_BASE_ADRESS+0x18))

/* Register Definition of PORTB*/
#define   GPIOB_CRL   *((u32*)(GPIOB_BASE_ADRESS+0x00))
#define   GPIOB_CRH   *((u32*)(GPIOB_BASE_ADRESS+0x04))
#define   GPIOB_IDR   *((u32*)(GPIOB_BASE_ADRESS+0x08))
#define   GPIOB_ODR   *((u32*)(GPIOB_BASE_ADRESS+0x0C))
#define   GPIOB_BSRR  *((u32*)(GPIOB_BASE_ADRESS+0x10))
#define   GPIOB_BRR   *((u32*)(GPIOB_BASE_ADRESS+0x14))
#define   GPIOB_LCKR   *((u32*)(GPIOB_BASE_ADRESS+0x18))

/* Register Definition of PORTC*/
#define   GPIOC_CRL   *((u32*)(GPIOC_BASE_ADRESS+0x00))
#define   GPIOC_CRH   *((u32*)(GPIOC_BASE_ADRESS+0x04))
#define   GPIOC_IDR   *((u32*)(GPIOC_BASE_ADRESS+0x08))
#define   GPIOC_ODR   *((u32*)(GPIOC_BASE_ADRESS+0x0C))
#define   GPIOC_BSRR  *((u32*)(GPIOC_BASE_ADRESS+0x10))
#define   GPIOC_BRR   *((u32*)(GPIOC_BASE_ADRESS+0x14))
#define   GPIOC_LCKR   *((u32*)(GPIOC_BASE_ADRESS+0x18))


#endif