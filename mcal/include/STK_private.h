/*********************************************************************************/
/* Author    : Gomaa Mohammed                                                      */
/* Version   : V01                                                               */
/* Date      : 24 August 2020                                                     */
/*********************************************************************************/

#ifndef _STK_PRIVATE_H_
#define _STK_PRIVATE_H_



void (*STK_Callback)(void);


/* Define Variable for interval mode */
static u8 STK_u8ModeOfInterval;
typedef struct{
	 u32  CTRL;
     u32  LOAD;
     u32  VAL;
     u32  CALIB;
	
	
}stk_t;

#define STK  ((volatile stk_t *)0xE000E010)


#define   STK_AHB          0
#define   STK_AHB_DIV_8    1

#define     STK_SINGLE_INTERVAL    0
#define     STK_PERIOD_INTERVAL    1


#endif
