/***************************************/
/* Author  :Gomaa                      */
/* Date    :8 Aug 2020                 */
/* Version :V01                        */
/***************************************/

#ifndef    _RCC_CONFIG_H_
#define    _RCC_CONFIG_H_ 

/*  options:  RCC_HSE_CRYSTAL
              RCC_HSE_RC
			  RCC_HSI
			  RCC_PLL    */
#define     RCC_CLOCK_TYPE    RCC_HSE_CRYSTAL

/*   options:    RCC_PLL_IN_HSI_2
                 RCC_PLL_IN_HSE_2
				 RCC_PLL_IN_HSE

*/
/* Note: only in case of pll*/
#if        RCC_CLOCK_TYPE == RCC_PLL
#define    RCC_PLL_INPUT    RCC_PLL_IN_HSI_2
#endif

/*   options:   
from 0 to 16


*/
/* Note: only in case of pll*/
#if        RCC_CLOCK_TYPE == RCC_PLL
#define    RCC_MUL_VAL   4
#endif







#endif