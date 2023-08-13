/************************************************************************
* @file:     OSMUTEX_interface.h
* @author:   Copyright (c) 2023 Gomaa Mohammed Gomaa.  All rights reserved.
* @version:  V0.1   
* @date:     Fri, 12 Aug 2023 18:21:12 +0300
* @brief:    Mutex Module.
*************************************************************************/
#ifndef _OSMUTEX_INTERFACE_H_
#define _OSMUTEX_INTERFACE_H_

/* ==================================================================== */
/* ===================== mutex types definition ======================= */
/* ==================================================================== */

typedef struct
{
  u32 MutexValue;                     // mutex Value
  #if (USE_PRIORITY_INHERITANCE == 1)
  task_t * MutexHolder;               // task currently holding the mutex 
  #endif
  list_t WaitingList;        // waiting list of the mutex 
} mutex_t;

typedef enum
{
  OS_SUCCESS,
  OS_FAILURE,
  OS_CONTEXT_SWITCH_TRIGGERED
} OS_return_t;


/* ==================================================================== */
/* =================== Public functions declaration =================== */
/* ==================================================================== */

// create mutex
void OS_createMutex(mutex_t * pMutex, u32 InitialValue);

// lock mutex
OS_return_t OS_lockMutex(mutex_t * pMutex, s32 WaitTime);

// unlock mutex
void OS_releaseMutex(mutex_t * pMutex);

#endif 
