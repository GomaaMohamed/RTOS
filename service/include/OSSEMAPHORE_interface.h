/************************************************************************
* @file:     OSSEMAPHORE_interface.h
* @author:   Copyright (c) 2023 Gomaa Mohammed Gomaa.  All rights reserved.
* @version:  V0.1   
* @date:     Fri, 12 Aug 2023 18:21:12 +0300
* @brief:    Semaphore Module.
*************************************************************************/
#ifndef __OS_SEMAPHORE_H_
#define __OS_SEMAPHORE_H_

/* ==================================================================== */
/* =================== semaphore types definition ===================== */
/* ==================================================================== */

typedef struct
{
  u32 SemaphoreValue;        // Semaphore counter value 
  list_t WaitingList;        // Waiting list of the semaphore 
} semaphore_t;


/* ==================================================================== */
/* =================== Public functions declaration =================== */
/* ==================================================================== */

// create semaphore
void OS_createSemaphore(semaphore_t * pSemaphore, u32 InitialValue);

// take semaphore 
OS_return_t OS_takeSemaphore(semaphore_t * pSemaphore, s32 WaitTime);

// give semaphore
void OS_giveSemaphore(semaphore_t * pSemaphore);

#endif 
