/*****************************************************************************
* @file:    GPIO_interface.h
* @author:  Copyright (c) 2023 Gomaa Mohammed Gomaa. 
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Sun, 1 Oct 2023 14:21:12 +0200
* @brief:   General Purpose Input Output(GPIO) Driver for STM32F103
******************************************************************************/
#ifndef _GPIO_INTERFACE_H
#define _GPIO_INTERFACE_H

/* ==================================================================== */
/* ======================= public data types ========================== */
/* ==================================================================== */

/* Port Id Data Type */
typedef enum
{
    GPIOA=0,
    GPIOB,
    GPIOC,
    PORT_ID_ERR
} PortId_type;
 
/* Pin Id Data Type */
typedef enum
{
    GPIO_PIN0=0,
    GPIO_PIN1,
    GPIO_PIN2,
    GPIO_PIN3,
    GPIO_PIN4,
    GPIO_PIN5,
    GPIO_PIN6,
    GPIO_PIN7,
    GPIO_PIN8,
    GPIO_PIN9,
    GPIO_PIN10,
    GPIO_PIN11,
    GPIO_PIN12,
    GPIO_PIN13,
    GPIO_PIN14,
    GPIO_PIN15,
    PIN_ID_ERR
} PinId_type;

/* Pin State Data Type */
typedef enum
{
    GPIO_HIGH=1,
    GPIO_LOW=0,
    PIN_STATE_ERR=2
} PinState_type;

/* Pin Mode Data Type */
typedef enum
{
    /*************** Output modes ***************/
    GPIO_OUTPUT_10MHZ_PP=0b0001,   //0x1
    GPIO_OUTPUT_10MHZ_OD=0b0101,   //0x5
    GPIO_OUTPUT_10MHZ_AFPP=0b1001, //0x9
    GPIO_OUTPUT_10MHZ_AFOD=0b1101, //0xD  
    GPIO_OUTPUT_2MHZ_PP=0b0010,    //0x2
    GPIO_OUTPUT_2MHZ_OD=0b0110,    //0x6
    GPIO_OUTPUT_2MHZ_AFPP=0b1010,  //0xA 
    GPIO_OUTPUT_2MHZ_AFOD=0b1110,  //0xE 
    GPIO_OUTPUT_50MHZ_PP=0b0011,   //0x3
    GPIO_OUTPUT_50MHZ_OD=0b0111,   //0x7
    GPIO_OUTPUT_50MHZ_AFPP=0b1011, //0xB
    GPIO_OUTPUT_50MHZ_AFOD=0b1111, //0xF
    /**************** Input modes ********************/
    GPIO_INPUT_ANALOG=0b0000,      //0x0
    GPIO_INPUT_FLOATING=0b0100,    //0x4
    GPIO_INPUT_PULL_UP_DOWN=0b1000,//0x8
    PIN_MODE_ERR=16
} PinMode_type;


/* ==================================================================== */
/* ==================== Public Functions Declaration ================== */
/* ==================================================================== */

/**
 * @brief---------------------> Configure pin mode
 * @parameter1----------------> (PortId) port that contains the pin
 * @parameter2----------------> (PinId) pin to set its mode 
 * @parameter3----------------> (PinMode) mode to be setted for a pin
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant      
 */
void GPIO_setPinDirection(PortId_type PortId,PinId_type PinId,PinMode_type PinMode);

/**
 * @brief---------------------> Set pin state
 * @parameter1----------------> (PortId) port that contains the pin
 * @parameter2----------------> (PinId) pin to set its state
 * @parameter3----------------> (PinState) State to be assigned to pin
 * @return--------------------> None
 * @preconditions-------------> Pin is initialized
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant      
 */
void GPIO_setPinValue(PortId_type PortId,PinId_type PinId,PinState_type PinState);

/**
 * @brief---------------------> Toggle pin state
 * @parameter1----------------> (PortId) port that contains the pin
 * @parameter2----------------> (PinId) pin to toggle its state
 * @return--------------------> None
 * @preconditions-------------> Pin is initialized
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant    
 */
void GPIO_togglePinValue(PortId_type PortId, PinId_type PinId);

/**
 * @brief---------------------> Get pin state
 * @parameter1----------------> (PortId) port that contains the pin
 * @parameter2----------------> (PinId) pin to get its state
 * @return--------------------> Pin state
 * @preconditions-------------> Pin is initialized
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant      
 */
PinState_type GPIO_getPinValue(PortId_type PortId,PinId_type PinId);

/**
 * @brief---------------------> Lock pin mode to prevent changing mode 
 * @parameter1----------------> (PortId) port that contains the pin
 * @parameter2----------------> (PinId) pin to lock its mode
 * @return--------------------> None
 * @preconditions-------------> Pin is initialized
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant 
 */
void GPIO_lockPinMode(PortId_type PortId,PinId_type PinId);



#endif
