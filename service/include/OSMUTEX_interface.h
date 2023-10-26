/*****************************************************************************
* @file:    OSMUTEX_interface.h
* @author:  Copyright (c) 2023 Gomaa Mohammed.
* @license: GNU GPL version 3 or later.
*			      This is free software: you are free to change and redistribute it.  
*			      There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Wed, 25 Oct 2023 11:21:12 +0200
* @brief:   Mutex Module.
*******************************************************************************/
#ifndef _OSMUTEX_INTERFACE_H_
#define _OSMUTEX_INTERFACE_H_

/* ==================================================================== */
/* ===================== Mutex Types Definition ======================= */
/* ==================================================================== */

typedef struct
{
  u32 MutexValue;                     // mutex Value
  #if (USE_PRIORITY_INHERITANCE == 1)
  task_t * MutexHolder;               // task currently holding the mutex 
  #endif
  list_t WaitingList;                 // waiting list of the mutex 
} mutex_t;

typedef enum
{
  OS_SUCCESS,
  OS_FAILURE,
  OS_CONTEXT_SWITCH_TRIGGERED
} OS_return_t;

/* ==================================================================== */
/* =================== Public Functions Declaration =================== */
/* ==================================================================== */

/************ Create mutex ************/ 
void OS_createMutex(mutex_t * pMutex, u32 InitialValue);

/************* Lock mutex *************/ 
OS_return_t OS_lockMutex(mutex_t * pMutex, s32 WaitTime);

/************ Unlock mutex ************/
void OS_releaseMutex(mutex_t * pMutex);

#endif 
