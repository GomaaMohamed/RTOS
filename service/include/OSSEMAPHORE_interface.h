/*****************************************************************************
* @file:    OSSEMAPHORE_interface.h
* @author:  Copyright (c) 2023 Gomaa Mohammed.
* @license: GNU GPL version 3 or later.
*			      This is free software: you are free to change and redistribute it.  
*			      There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Wed, 25 Oct 2023 11:21:12 +0200
* @brief:   Semaphore Module.
*******************************************************************************/
#ifndef _OS_SEMAPHORE_H
#define _OS_SEMAPHORE_H

/* ==================================================================== */
/* =================== Semaphore Types Definition ===================== */
/* ==================================================================== */

typedef struct
{
  u32 SemaphoreValue; // Semaphore counter value 
  list_t WaitingList; // Waiting list of the semaphore 
} semaphore_t;

/* ==================================================================== */
/* =================== Public Functions Declaration =================== */
/* ==================================================================== */

/*********** Create semaphore *************/
void OS_createSemaphore(semaphore_t * pSemaphore, u32 InitialValue);

/*********** Take semaphore *************/ 
OS_return_t OS_takeSemaphore(semaphore_t * pSemaphore, s32 WaitTime);

/*********** Give semaphore *************/
void OS_giveSemaphore(semaphore_t * pSemaphore);


#endif 
