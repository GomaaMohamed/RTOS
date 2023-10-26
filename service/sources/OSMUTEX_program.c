/*****************************************************************************
* @file:    OSMUTEX_program.c
* @author:  Copyright (c) 2023 Gomaa Mohammed.
* @license: GNU GPL version 3 or later.
*			      This is free software: you are free to change and redistribute it.  
*			      There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Wed, 25 Oct 2023 11:21:12 +0200
* @brief:   Mutex Module.
*******************************************************************************/

/* ==================================================================== */
/* ========================== Include Files =========================== */
/* ==================================================================== */

#include "OS_interface.h"

/* ==================================================================== */
/* ===================== Functions Implementation ===================== */
/* ==================================================================== */

// Function to create mutex
void OS_createMutex(mutex_t * pMutex, u32 InitialValue)
{
    // Check input parameters 
    ASSERT(pMutex != NULL);
    ASSERT((InitialValue == 0) || (InitialValue == 1));

    // Initialize mutex waiting list 
    OSLIST_init(&pMutex->WaitingList);

    // Initialize mutex value 
    pMutex->MutexValue = InitialValue;

    #if(USE_PRIORITY_INHERITANCE == 1)
    {
      // initialize mutex holder */
      pMutex->MutexHolder = NULL;
    }
    #endif
}

// Function to lock mutex
OS_return_t OS_lockMutex(mutex_t * pMutex, s32 WaitTime)
{
    // Check input parameters 
    ASSERT(NULL != pMutex);
    ASSERT(WAIT_INDEFINITELY <= WaitTime);

    // Mutex lock return status 
    OS_return_t ReturnStatus = OS_FAILURE;

    // Pointer to the current running task
    task_t *pRunningTask;

    // Variable to terminate the while loop 
    u32 terminate = 0;

    // Get current running task 
    pRunningTask = OS_getRunningTask();

    // Try to lock the mutex 
    while(1 != terminate)
    {
        // Check mutex value, note in ARMv7-M exceptions automatically clear the
        // Exclusive state in the local monitor, no need to use CLREX instruction 
        if(1 == __LDREXW(&pMutex->MutexValue))
        {
            // Mutex is free, locked it 
            if(0 == __STREXW(0, &pMutex->MutexValue))
            {
                // Required before accessing protected resource 
                __DMB();

                // Mutex is locked 
                ReturnStatus = OS_SUCCESS;

                #if(1 == USE_PRIORITY_INHERITANCE)
                {
                    // Update mutex holder 
                    pMutex->MutexHolder = OS_getRunningTask();
                }
                #endif

                // Mutex lock succeeded, terminate the loop 
                terminate = 1;
            }
            else
            {
                // Mutex can not be locked, do nothing 
            }
        } 
        else
        {
            // Mutex is locked, terminate the loop 
            terminate = 1;
        }
    } 

    // Check waiting flag and return status 
    if((NO_WAIT != WaitTime) && (OS_SUCCESS != ReturnStatus))
    {
        // Remove current task from ready list 
        OSLIST_removeItem(&pRunningTask->GenericListItem);

        // Put current task into the waiting list 
        OSLIST_insertItem(&pMutex->WaitingList, &pRunningTask->EventListItem);

        // Trigger context switch, set PendSV to pending 
        __set_PENDSV();

        // Check waiting time 
        if(NO_WAIT < WaitTime)
        {
           // Waiting time configured, add current to the timer list 
           OS_addRunningTaskToTimerList(WaitTime);
        }
        else
        {
            // Task will wait indefinitely, do nothing 
        }

        #if(1 == USE_PRIORITY_INHERITANCE)
        {
          // Inherit the priority for the mutex holder 
          OS_inheritTaskPriority(pMutex->MutexHolder);
        }
        #endif

        // Return to SVC as indication of context switching 
        ReturnStatus = OS_CONTEXT_SWITCH_TRIGGERED;
    }
    else
    {
        // No blocking required, do nothing 
    }

    // Return 
    return ReturnStatus;
}

// Function to release mutex
void OS_releaseMutex(mutex_t * pMutex)
{
    // Check input parameters 
    ASSERT(NULL != pMutex);

    // Pointer to the unblocked task 
    task_t * pTask;

    // Required before releasing protected resource 
    __DMB();

    // Release the mutex 
    pMutex->MutexValue = 1;

    // Get highest priority waiting task, the one next from the end 
    if(0 < pMutex->WaitingList.NumOfItems)
    {
        pTask = pMutex->WaitingList.ListEnd.pNext->pTask;

        // Check returned thread 
        ASSERT(NULL != pTask);

        // Remove the returned task item from the waiting list
        OSLIST_removeItem(&pTask->EventListItem);

        // Check if the generic item in any list 
        if(NULL != pTask->GenericListItem.pList)
        {
            // Remove the generic item from the current list,
            // as it will be inserted into ready list 
            OSLIST_removeItem(&pTask->GenericListItem);
        }
        else
        {
            // Do nothing, generic item is not in any list 
        }

        // Add the returned task into ready list 
        OS_addTaskToReadyList(pTask);
    }
    else
    {
        // No tasks are waiting, do nothing 
    }

    #if(1 == USE_PRIORITY_INHERITANCE)
    {
        // Disinherit the priority for the current task 
        OS_disinheritTaskPriority();

        // Update mutex holder 
        pMutex->MutexHolder = NULL;
    }
    #endif
}

