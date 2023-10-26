/*****************************************************************************
* @file:    STK_interface.h
* @author:  Copyright (c) 2023 Gomaa Mohammed Gomaa.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Wed, 4 Oct 2023 13:31:12 +0200
* @brief:   System Timer Counter(SysTick) Driver for STM32F103
******************************************************************************/
#ifndef _STK_INTERFACE_H
#define _STK_INTERFACE_H

/* ==================================================================== */
/* ==================== Public Functions Declaration ================== */
/* ==================================================================== */

/**
 * @brief---------------------> Initialize SysTick module
 * @param---------------------> None
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant      
 */
void STK_init(void);

/**
 * @brief---------------------> Set busy wait delay 
 * @parameter1----------------> (Ticks) number of ticks to be made an delay
 * @return--------------------> None
 * @preconditions-------------> SysTick is initialized
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant         
 */
void STK_setBusyWait(u32 Ticks);

/**
 * @brief---------------------> Set a single event to be called after number of ticks
 * @parameter1----------------> (Ticks) number of ticks
 * @parameter2----------------> (Callback) event as a callback
 * @return--------------------> None
 * @preconditions-------------> SysTick is initialized
 * @postconditions------------> None
 * @synchronous/asynchronous--> Asynchronous
 * @reentrant/non-reentrant---> Reentrant     
 */
void STK_setSingleInterval(u32 Ticks,void (*Callback)(void));

/**
 * @brief---------------------> Set a periodic event to be called after number of ticks 
 * @parameter1----------------> (Ticks) number of ticks
 * @parameter2----------------> (Callback) event as a callback
 * @return--------------------> None
 * @preconditions-------------> SysTick is initialized
 * @postconditions------------> None
 * @synchronous/asynchronous--> Asynchronous
 * @reentrant/non-reentrant---> Reentrant       
 */
void STK_setPeriodicInterval(u32 Ticks,void (*Callback)(void));

/**
 * @brief---------------------> Stop Interval
 * @param---------------------> (Ticks) number of ticks
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant    
 */
void STK_stopInterval(void);

/**
 * @brief---------------------> Get elapsed time as ticks
 * @param---------------------> None
 * @return--------------------> Number of elapsed ticks
 * @preconditions-------------> SysTick is initialized and timer is on
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
u32  STK_getElapsedTime(void);

/**
 * @brief---------------------> Get remaining time as ticks
 * @param---------------------> None
 * @return--------------------> Number of remaining ticks
 * @preconditions-------------> SysTick is initialized and timer is on
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
u32  STK_getRemainingTime(void);

/**
 * @brief---------------------> Enable SysTick interrupt
 * @param---------------------> None
 * @return--------------------> None
 * @preconditions-------------> SysTick is initialized and callback is setted
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
void STK_enableInterrupt(void);

/**
 * @brief---------------------> Disable SysTick interrupt
 * @param---------------------> None
 * @return--------------------> None
 * @preconditions-------------> SysTick is initialized and callback is setted
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
void STK_disableInterrupt(void);

/**
 * @brief---------------------> Set SysTick Callback
 * @param---------------------> None
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 */
void STK_setCallback(void (*Callback)(void));



#endif
