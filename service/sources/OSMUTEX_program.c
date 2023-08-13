/************************************************************************
* @file:     OSMUTEX_program.c
* @author:   Copyright (c) 2023 Gomaa Mohammed Gomaa.  All rights reserved.
* @version:  V0.1   
* @date:     Fri, 12 Aug 2023 18:21:12 +0300
* @brief:    Mutex Module.
*************************************************************************/

/* ==================================================================== */
/* ========================== include files =========================== */
/* ==================================================================== */

#include "OS_interface.h"

/* ==================================================================== */
/* ======================= functions definition ======================= */
/* ==================================================================== */

void OS_createMutex(mutex_t * pMutex, u32 InitialValue)
{
  // check input parameters 
  ASSERT(pMutex != NULL);
  ASSERT((InitialValue == 0) || (InitialValue == 1));

  // initialize mutex waiting list 
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


OS_return_t OS_lockMutex(mutex_t * pMutex, s32 WaitTime)
{
  // check input parameters 
  ASSERT(NULL != pMutex);
  ASSERT(WAIT_INDEFINITELY <= WaitTime);

  // mutex lock return status 
  OS_return_t ReturnStatus = OS_FAILURE;

  // pointer to the current running task
  task_t *pRunningTask;

  // variable to terminate the while loop 
  u32 terminate = 0;

  // get current running task 
  pRunningTask = OS_getRunningTask();

  // try to lock the mutex 
  while(1 != terminate)
  {
    // check mutex value, note in ARMv7-M exceptions automatically clear the
    // exclusive state in the local monitor, no need to use CLREX instruction 
    if(1 == __LDREXW(&pMutex->MutexValue))
    {
      // mutex is free, locked it 
      if(0 == __STREXW(0, &pMutex->MutexValue))
      {
        // required before accessing protected resource 
        __DMB();

        // mutex is locked 
        ReturnStatus = OS_SUCCESS;

        #if(1 == USE_PRIORITY_INHERITANCE)
        {
          // update mutex holder 
          pMutex->MutexHolder = OS_getRunningTask();
        }
        #endif

        // mutex lock succeeded, terminate the loop 
        terminate = 1;
      }
      else
      {
        // mutex can not be locked, do nothing 
      }
    }
    else
    {
      // Mutex is locked, terminate the loop 
      terminate = 1;
    }
  }

  // check waiting flag and return status 
  if((NO_WAIT != WaitTime) && (OS_SUCCESS != ReturnStatus))
  {
    // remove current task from ready list 
    OSLIST_removeItem(&pRunningTask->GenericListItem);

    // put current task into the waiting list 
    OSLIST_insertItem(&pMutex->WaitingList, &pRunningTask->EventListItem);

    // trigger context switch, set PendSV to pending 
    __set_PENDSV();

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

void OS_releaseMutex(mutex_t * pMutex)
{
  // check input parameters 
  ASSERT(NULL != pMutex);

  // pointer to the unblocked thread 
  task_t * pTask;

  // required before releasing protected resource 
  __DMB();

  // Release the mutex 
  pMutex->MutexValue = 1;

  // get highest priority waiting task, the one next from the end 
  if(0 < pMutex->WaitingList.NumOfItems)
  {
    pTask = pMutex->WaitingList.ListEnd.pNext->pTask;

    // check returned thread 
    ASSERT(NULL != pTask);

    // remove the returned task item from the waiting list
    OSLIST_removeItem(&pTask->EventListItem);

    // check if the generic item in any list 
    if(NULL != pTask->GenericListItem.pList)
    {
      // Remove the generic item from the current list,
      // as it will be inserted into ready list 
      OSLIST_removeItem(&pTask->GenericListItem);
    }
    else
    {
      // do nothing, generic item is not in any list 
    }

    // add the returned task into ready list 
    OS_addTaskToReadyList(pTask);
  }
  else
  {
    // no tasks are waiting, do nothing 
  }

  #if(1 == USE_PRIORITY_INHERITANCE)
  {
    // disinherit the priority for the current task 
    OS_sisinheritTaskPriority();

    // update mutex holder 
    pMutex->MutexHolder = NULL;
  }
  #endif
}

