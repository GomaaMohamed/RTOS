/*****************************************************************************
* @file:    OSMAILBOX_program.c
* @author:  Copyright (c) 2023 Gomaa Mohammed.
* @license: GNU GPL version 3 or later.
*			      This is free software: you are free to change and redistribute it.  
*			      There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Wed, 25 Oct 2023 11:21:12 +0200
* @brief:   Mailbox Module.
*******************************************************************************/

/* ==================================================================== */
/* ========================== Include Files =========================== */
/* ==================================================================== */

#include "OS_interface.h"

/* ==================================================================== */
/* ===================== Functions Implementation ===================== */
/* ==================================================================== */

// Private functions prototypes
static void checkWaitingTasks(mailbox_t * pMailbox);
static void blockCurrentTask(mailbox_t * pMailbox);

// Function to copy number of bytes
void mymemcpy(const void * const *dest, const void * const *src, u8 n)
{ 
    // Typecast src and dest addresses to (char *) 
    u8 *csrc = (u8 *)src; 
    u8 *cdest = (u8 *)dest; 

    // Copy contents of src[] to dest[] 
    for (u32 i=0; i<n; i++)
    { 
        cdest[i] = csrc[i]; 
    }
} 

// Function to check waiting tasks on mailbox
static void checkWaitingTasks(mailbox_t * pMailbox)
{
    // Check input parameters 
    ASSERT(NULL != pMailbox);

    // Pointer to the unblocked task 
    task_t * pTask;

    // Check if tasks are waiting for the data 
    if(0 < pMailbox->WaitingList.NumOfItems)
    {
        // Get first one 
        pTask = pMailbox->WaitingList.ListEnd.pNext->pTask;

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
        // List is empty 
    }
}

// Function to block a task from mailbox
static void blockCurrentTask(mailbox_t * pMailbox)
{
    // Pointer to the current running thread 
    task_t * pRunningTask;

    // Get current running task
    pRunningTask = OS_getRunningTask();

    // Remove current task from ready list 
    OSLIST_removeItem(&pRunningTask->GenericListItem);

    // Put current task into the waiting list 
    OSLIST_insertItem(&pMailbox->WaitingList, &pRunningTask->EventListItem);

    // Trigger context switch, set PendSV to pending
    __set_PENDSV();
}

// Function to create a mailbox
void OS_createMailbox(mailbox_t * pMailbox, void * pBuffer, u32 BufferLength, u32 MessageSize)
{
    // Check input parameters 
    ASSERT(NULL != pMailbox);
    ASSERT(NULL != pBuffer);
    ASSERT(0 != BufferLength);
    ASSERT((1 == MessageSize) || (2 == MessageSize) || (4 == MessageSize));

    // Set mailbox buffer start and end 
    pMailbox->pStart = (s8 *) pBuffer;
    pMailbox->pEnd = pMailbox->pStart + (BufferLength * MessageSize);

    // Initialize read and write indices 
    pMailbox->pReadIndex = pMailbox->pStart;
    pMailbox->pWriteIndex = pMailbox->pStart;

    // Set buffer length and message size 
    pMailbox->BufferLength = BufferLength;
    pMailbox->MessageSize = MessageSize;

    // Initialize current number of messages 
    pMailbox->MessagesNum = 0;

    // Initialize mailbox waiting list 
    OSLIST_init(&pMailbox->WaitingList);
}

// Function to write in a mailbox
OS_return_t OS_writeMailbox(mailbox_t * pMailbox, s32 WaitTime,const void * const pMessage)
{
    // Check input parameters 
    ASSERT(NULL != pMailbox);
    ASSERT(WAIT_INDEFINITELY <= WaitTime);
    ASSERT(NULL != pMessage);

    // Return status 
    OS_return_t returnStatus = OS_FAILURE;

    // Check if there is a free place to write 
    if(pMailbox->BufferLength > pMailbox->MessagesNum)
    {
        // Buffer is not full, copy data 
        mymemcpy((void *) pMailbox->pWriteIndex, pMessage, pMailbox->MessageSize);

        // Increment write index to point to the next message 
        pMailbox->pWriteIndex += pMailbox->MessageSize;

        // Check if the buffer is written until the end 
        if(pMailbox->pWriteIndex >= pMailbox->pEnd)
        {
          // Start over 
          pMailbox->pWriteIndex = pMailbox->pStart;
        }
        else
        {
            // Do nothing, end is still not reached 
        }

        // Increment current number of messages in the buffer 
        pMailbox->MessagesNum++;

        // Check waiting tasks 
        checkWaitingTasks(pMailbox);

        // New message is added to the buffer, return OK 
        returnStatus = OS_SUCCESS;
    }
    else
    {
      // Do nothing, Buffer is full 
    }

    // Check waiting time and return status 
    if((NO_WAIT != WaitTime) && (OS_SUCCESS != returnStatus))
    {
        // Block current task
        blockCurrentTask(pMailbox);

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

// Function to read mailbox
OS_return_t OS_readMailbox(mailbox_t * pMailbox, s32 WaitTime,void * const pMessage)
{
    // Check input parameters 
    ASSERT(NULL != pMailbox);
    ASSERT(WAIT_INDEFINITELY <= WaitTime);
    ASSERT(NULL != pMessage);

    // Return status 
    OS_return_t returnStatus = OS_FAILURE;

    // Check if there are messages in the buffer 
    if(0 < pMailbox->MessagesNum)
    {
        // Buffer is not empty, copy data 
        mymemcpy(pMessage, (void *) pMailbox->pReadIndex, pMailbox->MessageSize);

        // Increment Read index to point to the next message 
        pMailbox->pReadIndex += pMailbox->MessageSize;

        // Check if the buffer is read until the end 
        if(pMailbox->pReadIndex >= pMailbox->pEnd)
        {
            // Start over 
            pMailbox->pReadIndex = pMailbox->pStart;
        }
        else
        {
            // Do nothing, end is still not reached 
        }

        // Decrement current number of messages in the buffer 
        pMailbox->MessagesNum--;

        // Check waiting threads 
        checkWaitingTasks(pMailbox);

        // New message is removed from the buffer, return OK 
        returnStatus = OS_SUCCESS;
    } 
    else
    {
       // Do nothing, Buffer is empty 
    }

    // Check waiting time and return status 
    if((NO_WAIT != WaitTime) && (OS_SUCCESS != returnStatus))
    {
        // Block current task 
        blockCurrentTask(pMailbox);

        // Check waiting time 
        if(NO_WAIT < WaitTime)
        {
            // Waiting time configured, add current to the timer list 
            OS_addRunningTaskToTimerList(WaitTime);
        }
        else
        {
            // Thread will wait indefinitely, do nothing 
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

