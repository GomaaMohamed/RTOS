/****************************************/
/* Author    :Gomaa                     */
/* Date      :29/7/2020                 */
/* Version   :V01                       */
/****************************************/

#ifndef  BIT_MATH_H
#define  BIT_MATH_H

/* Bit Operations*/
#define  SET_BIT(VAR,BIT)   VAR |=(1<<(BIT))
#define  CLR_BIT(VAR,BIT)   VAR &=~(1<<(BIT))
#define  GET_BIT(VAR,BIT)   ((VAR>>BIT)&1)
#define  TOG_BIT(VAR,BIT)   VAR ^=(1<<(BIT))


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
