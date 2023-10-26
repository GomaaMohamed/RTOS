/*****************************************************************************
* @file:    BIT_MATH.h
* @author:  Copyright (c) 2023 Gomaa Mohammed.
* @license: GNU GPL version 3 or later.
*			      This is free software: you are free to change and redistribute it.  
*			      There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Sun, 1 Oct 2023 14:21:12 +0200
* @brief:   Bit Manipulation Library.
******************************************************************************/

#ifndef  _BIT_MATH_H
#define  _BIT_MATH_H

/* Bit Operations */
#define  SET_BIT(VAR,BIT)   VAR |=(1<<(BIT))
#define  CLR_BIT(VAR,BIT)   VAR &=~(1<<(BIT))
#define  GET_BIT(VAR,BIT)   ((VAR>>BIT)&1)
#define  TOG_BIT(VAR,BIT)   VAR ^=(1<<(BIT))

/* Mask Operations */
#define SET_MASK(VAR,VAL)       (VAR)|=(VAL)
#define CLR_MASK(VAR,VAL)       (VAR)&=~(VAL)

/* Byte Operations 
  BYTE Options: 0
                1
                2
				        3
*/
#define  SET_BYTE(VAR,BYTE)   VAR |= ((0xFF)<<((BYTE)*8))
#define  CLR_BYTE(VAR,BYTE)   VAR &=~((0xFF)<<((BYTE)*8))
#define  TOG_BYTE(VAR,BYTE)   VAR ^= ((0xFF)<<((BYTE)*8))

// check parameters
#define ASSERT(x) if(x == 0){asm("CPSID i");while(1); }

// Memory Access
#define MEM32_ADDRESS(ADDRESS) (*((volatile unsigned long *)(ADDRESS)))



#endif
