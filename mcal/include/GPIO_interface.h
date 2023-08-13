/*********************************************************************************/
/* Author    : Gomaa Mohammed                                                    */
/* Version   : V01                                                               */
/* Date      : 12 August 2020                                                    */
/*********************************************************************************/

#ifndef _GPIO_INTERFACE_H_
#define _GPIO_INTERFACE_H_

/* Port Id */
#define   GPIOA   0
#define   GPIOB   1
#define   GPIOC   2

/* Half Port Id */
#define   GPIO_FIRST_HALF    0
#define   GPIO_SECOND_HALF   1

 
/* Pin Id */
#define     GPIO_PIN0     0
#define     GPIO_PIN1     1
#define     GPIO_PIN2     2
#define     GPIO_PIN3     3
#define     GPIO_PIN4     4
#define     GPIO_PIN5     5
#define     GPIO_PIN6     6
#define     GPIO_PIN7     7
#define     GPIO_PIN8     8
#define     GPIO_PIN9     9
#define     GPIO_PIN10    10
#define     GPIO_PIN11    11
#define     GPIO_PIN12    12
#define     GPIO_PIN13    13
#define     GPIO_PIN14    14
#define     GPIO_PIN15    15

/* Pin State */
#define     GPIO_HIGH 1
#define     GPIO_LOW  0

/* Pin Output Modes */
#define     GPIO_OUTPUT_10MHZ_PP      0b0001   //0x1
#define     GPIO_OUTPUT_10MHZ_OD      0b0101   //0x5
#define     GPIO_OUTPUT_10MHZ_AFPP    0b1001   //0x9
#define     GPIO_OUTPUT_10MHZ_AFOD    0b1101   //0xD
			
#define     GPIO_OUTPUT_2MHZ_PP      0b0010    //0x2
#define     GPIO_OUTPUT_2MHZ_OD      0b0110    //0x6
#define     GPIO_OUTPUT_2MHZ_AFPP    0b1010    //0xA 
#define     GPIO_OUTPUT_2MHZ_AFOD    0b1110    //0xE
			
#define     GPIO_OUTPUT_50MHZ_PP      0b0011   //0x3
#define     GPIO_OUTPUT_50MHZ_OD      0b0111   //0x7
#define     GPIO_OUTPUT_50MHZ_AFPP    0b1011   //0xB
#define     GPIO_OUTPUT_50MHZ_AFOD    0b1111   //0xF

/* Pin Input Modes */
#define     GPIO_INPUT_ANALOG               0b0000   //0x0
#define     GPIO_INPUT_FLOATING             0b0100   //0x4
#define     GPIO_INPUT_PULL_UP_DOWN         0b1000   //0x8


/* HalfPort Output Modes */
#define     GPIO_OUTPUTHP_10MHZ_PP      0x11111111
#define     GPIO_OUTPUTHP_10MHZ_OD      0x55555555
#define     GPIO_OUTPUTHP_10MHZ_AFPP    0x99999999
#define     GPIO_OUTPUTHP_10MHZ_AFOD    0xDDDDDDDD

#define     GPIO_OUTPUTHP_2MHZ_PP      0x22222222  
#define     GPIO_OUTPUTHP_2MHZ_OD      0x66666666
#define     GPIO_OUTPUTHP_2MHZ_AFPP    0xAAAAAAAA
#define     GPIO_OUTPUTHP_2MHZ_AFOD    0xEEEEEEEE
			
#define     GPIO_OUTPUTHP_50MHZ_PP     0x33333333
#define     GPIO_OUTPUTHP_50MHZ_OD     0x77777777
#define     GPIO_OUTPUTHP_50MHZ_AFPP   0xBBBBBBBB
#define     GPIO_OUTPUTHP_50MHZ_AFOD   0xFFFFFFFF

/* HalfPort Input Modes */
#define     GPIO_INPUTHP_ANALOG              0x00000000
#define     GPIO_INPUTHP_FLOATING            0x44444444
#define     GPIO_INPUTHP_PULL_UP_DOWN        0x88888888

 

/* Pin Operations */
void GPIO_voidSetPinDirection(u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8Mode);

void GPIO_voidSetPinValue(u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8Value);

u8 GPIO_voidGetPinValue(u8 Copy_u8Port,u8 Copy_u8Pin);

void GPIO_voidLockPinMode(u8 Copy_u8Port,u8 Copy_u8Pin);


/* Half Port Operations */
void GPIO_voidSetHalfPortDirection(u8 Copy_u8Port,u8 Copy_u8HalfPort,u32 Copy_u32HalfPortMode);

void GPIO_voidSetHalfPortValue(u8 Copy_u8Port,u8 Copy_u8HalfPort,u16 Copy_u8Value);

u8 GPIO_voidGetHalfPortValue(u8 Copy_u8Port,u8 Copy_u8HalfPort);





#endif
