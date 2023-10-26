/*****************************************************************************
* @file:    OSSEMAPHORE_program.c
* @author:  Copyright (c) 2023 Gomaa Mohammed.
* @license: GNU GPL version 3 or later.
*			      This is free software: you are free to change and redistribute it.  
*			      There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Wed, 25 Oct 2023 11:21:12 +0200
* @brief:   Semaphore Module.
*******************************************************************************/

/* ==================================================================== */
/* ========================== Include Files =========================== */
/* ==================================================================== */

#include "OS_interface.h"

/* ==================================================================== */
/* ===================== Functions Implementation ===================== */
/* ==================================================================== */

// Function to create semaphore
void OS_createSemaphore(semaphore_t * pSemaphore, u32 InitialValue)
{
    // Check input parameters 
    ASSERT(NULL != pSemaphore);

    // Initialize semaphore waiting list 
    OSLIST_init(&pSemaphore->WaitingList);

    // Initialize semaphore value 
    pSemaphore->SemaphoreValue = InitialValue;
}

// Function to take semaphore
OS_return_t OS_takeSemaphore(semaphore_t * pSemaphore, s32 WaitTime)
{
    // Check input parameters 
    ASSERT(NULL != pSemaphore);
    ASSERT(WAIT_INDEFINITELY <= WaitTime);

    // Semaphore take return status 
    OS_return_t returnStatus = OS_FAILURE;

    // Pointer to the current running task 
    task_t * pRunningTask;

    // Temp variable to store the semaphore value 
    u32 semaphoreValueTemp = 0;

    // Variable to terminate the while loop 
    u32 terminate = 0;

    // Try to decrement the semaphore 
    while(1 != terminate)
    { 
        // Read the semaphore counter value 
        semaphoreValueTemp = __LDREXW(&pSemaphore->SemaphoreValue);

        // Check semaphore counter value, note in ARMv7-M exceptions automatically
        // Clear the exclusive state in the local monitor,
        // No need to use CLREX instruction 
        if(0 < semaphoreValueTemp)
        { 
            // Semaphore is not fully taken, take one by decrement 
            if(0 == __STREXW((semaphoreValueTemp - 1), &pSemaphore->SemaphoreValue))
            {
                // Required before accessing protected resource 
                __DMB();

                // Semaphore is taken, return OK 
                returnStatus = OS_SUCCESS;

                // Store succeeded, terminate the loop 
                terminate = 1;
            }
            else
            {
                // Problem during decrementing, try again 
            }
        }
        else
        {
            // Semaphore is not available, terminate the loop 
            terminate = 1;
        }
    }

    // Check waiting time and return status 
    if((NO_WAIT != WaitTime) && (OS_SUCCESS != returnStatus))
    {
        // Get current running task
        pRunningTask = OS_getRunningTask();

        // Remove current task from ready list 
        OSLIST_removeItem(&pRunningTask->GenericListItem);

        // Put current task into the waiting list 
        OSLIST_insertItem(&pSemaphore->WaitingList, &pRunningTask->EventListItem);

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

        // Return to SVC as indication of context switch 
        returnStatus = OS_CONTEXT_SWITCH_TRIGGERED;
    }
    else
    {
        // No blocking required, do nothing 
    }

    // Return 
    return returnStatus;
}

// Function to give semaphore
void OS_giveSemaphore(semaphore_t * pSemaphore)
{
    // Check input parameters 
    ASSERT(NULL != pSemaphore);

    // Pointer to the unblocked task
    task_t * pTask;

    // Temp variable used to read the semaphore counter value 
    u32 semaphoreValueTemp = 0;

    // Variable to terminate the while loop 
    u32 terminate = 0;

    // Try incrementing the semaphore counter 
    while(1 != terminate)
    {
        // Get the semaphore value 
        semaphoreValueTemp = __LDREXW(&pSemaphore->SemaphoreValue);

        // Increment temp variable 
        semaphoreValueTemp++;

        // Try to store the incremented semaphore value 
        if(0 == __STREXW(semaphoreValueTemp, &pSemaphore->SemaphoreValue))
        {
            // Store succeeded, terminate the loop 
            terminate = 1;

            // Required before releasing protected resource 
            __DMB();
        }
        else
        {
            // Store failed, try again 
        }
    } 

    // Get highest priority waiting task, the one next from the end 
    if(0 < pSemaphore->WaitingList.NumOfItems)
    {
        pTask = pSemaphore->WaitingList.ListEnd.pNext->pTask;

        // Check returned task
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
        // No threads are waiting, do nothing 
    }
} 

