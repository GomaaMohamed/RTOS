/************************************************************************
* @file:     OSTASK_program.c
* @author:   Copyright (c) 2023 Gomaa Mohammed Gomaa.  All rights reserved.
* @version:  V0.1   
* @date:     Fri, 12 Aug 2023 18:21:12 +0300
* @brief:    Task Module.
*************************************************************************/

/* ==================================================================== */
/* ========================== include files =========================== */
/* ==================================================================== */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "RCC_interface.h"
#include "NVIC_interface.h"
#include "STK_interface.h"
#include "OS_config.h"
#include "OSLIST_interface.h"
#include "OSTASK_interface.h"
#include "OSMUTEX_interface.h"
#include "OSSEMAPHORE_interface.h"
#include "OSMAILBOX_interface.h"
#include "OS_interface.h"

/* ==================================================================== */
/* =========================== task variables ========================= */
/* ==================================================================== */

/*********** define ready list *************/
static list_t ReadyList[TASK_PRIORITY_LEVELS];

/*********** define timer list *************/
static list_t TimerList;

/*********** current top priority **********/
static u32 CurrentTopPriority = TASK_PRIORITY_LEVELS - 1;

/******* pointer to the running task *******/
static task_t * pRunningTask;


/******* currently running task ID ********/
 static u32 RunningTaskID = 0;


/********** number of tasks ***************/
 static u32 NumOfTasks = 0;

/******** milliseconds variable *********/
static volatile u32 SysTickCounter = 0;


#define SCB_ICSR *((volatile u32 *)0xE000ED04)
u32  OS_isSchedulerRunning(void);

/* ==================================================================== */
/* ======================= functions definition ======================= */
/* ==================================================================== */

void OS_createTask(task_t *pTask,stack_t *pStack,u32 Priority,void (*pFunction)(void)){

    // check prameters
    ASSERT(pTask != NULL);
    ASSERT(pStack != NULL);
    ASSERT(pFunction != NULL);
    ASSERT(Priority < TASK_PRIORITY_LEVELS);

    // allocate the stack of the task and make the sp points to the end of TCB
    // TCB size will be 18 words
    pTask->StackPointer = ((u32)pStack + TASK_STACK_SIZE * 8 - 18 * 4);

    // Write task function into return address 
    MEM32_ADDRESS((pTask->StackPointer + (16 << 2))) = (u32)pFunction;

    // Write initial xPSR, program status register, thumb 
    MEM32_ADDRESS((pTask->StackPointer + (17 << 2))) = 0x01000000;

    // write EXC_RETURN, since the execution tasks are using PSP, this will
    // allow SVC to return to the task with PSP 
    MEM32_ADDRESS(pTask->StackPointer) = 0xFFFFFFFD;

    // write initial CONTROL register value UNPRIVILEGED, PSP & no FPU 
    MEM32_ADDRESS((pTask->StackPointer + (1 << 2))) = 0x3;

    // set task priority 
    pTask->Priority = Priority;
    
    #if(USE_PRIORITY_INHERITANCE == 1)
    pTask->OriginalPriority = Priority;
    #endif
    
    // increment number of tasks
   if(pTask->TaskID == 0)
    {
     // New task is created
     pTask->TaskID = ++NumOfTasks;
   }
   else
    {
    // Do nothing, this task was re-created 
    }

    // task is not yet in any list 
    pTask->GenericListItem.pList = NULL;
    pTask->EventListItem.pList = NULL;

    // link this task with its list item 
    pTask->GenericListItem.pTask = (void *) pTask;
    pTask->EventListItem.pTask = (void *) pTask;
    
    // Set the event item value to the priority, this will be used to order the
    // items by priority in synchronization events list, for the generic lists
    // e.g. timer list, items are ordered with the timeout value 
    pTask->EventListItem.ItemValue = Priority;
    pTask->GenericListItem.ItemValue = 0;

    // Add new task to ready list 
    OS_addTaskToReadyList(pTask); 
}

void OS_initLists(void){

    // Initialize all ready lists
    for(u32 priority = 0; priority < TASK_PRIORITY_LEVELS; priority++)
    {
       OSLIST_init(&ReadyList[priority]);
    }
    // Initialize timer list 
    OSLIST_init(&TimerList);
}

task_t* OS_getRunningTask(void){

    return pRunningTask;
}

void OS_switchRunningTask(void){

  // Determine the highest priority ready task
  while (ReadyList[CurrentTopPriority].NumOfItems == 0)
  {
    // Check current top priority not greater than the maximum 
    ASSERT(TASK_PRIORITY_LEVELS > CurrentTopPriority);

    // No tasks with the current top priority,
    // increment current top priority 
    CurrentTopPriority++;
  }

  // Tasks are found, update list index to the next task
  list_t * pReadyList = &ReadyList[CurrentTopPriority];
  pReadyList->pIndex = pReadyList->pIndex->pNext;

  // Check if the new index pointing to the end of the list 
  if(pReadyList->pIndex == (listitem_t *) &pReadyList->ListEnd)
  {
    // Get the next task
    pReadyList->pIndex = pReadyList->pIndex->pNext;
  }
  else
  {
    // Do nothing, index is not pointing to the end 
  }

  // Update current running task 
  pRunningTask = (task_t *) pReadyList->pIndex->pTask;

  // Update current running task 
  RunningTaskID = pRunningTask->TaskID;
   

}

void OS_addTaskToReadyList(task_t *pTask){

    // Check prameters
    ASSERT(pTask != NULL);

    // Add task to ready list
    OSLIST_insertEndItem(&ReadyList[pTask->Priority],&pTask->GenericListItem);

    // Set current top periority
    if(pTask->Priority < CurrentTopPriority)
    {
       CurrentTopPriority = pTask->Priority;
    }

    // check if we need to do context switch or not
    if ((pRunningTask != NULL) && (pTask->Priority < pRunningTask->Priority))
    {
       __set_PENDSV();
    }

}

void OS_refreshTimerList(void){

  // Pointer to the unblocked task 
  task_t * pTask;

  // Check scheduler status 
  if(1 == OS_isSchedulerRunning())
  {
    // Increment SysTick counter 
    ++SysTickCounter;

    // Check SysTick counter overflow 
    if(0 == SysTickCounter)
    {
      // TODO: Handle counter overflow 
      ASSERT(0);
    }
    else
    {
      // No counter overflow, do nothing 
    }

    // Check if timer list has tasks waiting 
    if(0 < TimerList.NumOfItems)
    {
      // Timer list is not empty, check timeout values 
      while(SysTickCounter >= TimerList.ListEnd.pNext->ItemValue)
      {
        // Get first task waiting 
        pTask = TimerList.ListEnd.pNext->pTask;

        // Check returned task 
        ASSERT(NULL != pTask);

        // Task timeout, remove from timer list 
        OSLIST_removeItem(&pTask->GenericListItem);

        // Check if the task waiting for synchronization event 
        if(NULL != pTask->EventListItem.pList)
        {
          // Remove the task from the event list 
          OSLIST_removeItem(&pTask->EventListItem);
        }
        else
        {
          // Do nothing, this task is not in any event lists 
        }

        // Add the returned task into ready list 
        OS_addTaskToReadyList(pTask);
      }
    }
    else
    {
      // Timer list is empty, do nothing 
    }
  }
  else
  {
    // Scheduler is not running, do nothing 
  }
}

void OS_addRunningTaskToTimerList(u32 WaitTime){

   // Check input parameters 
  ASSERT(WaitTime != 0);

  // Temp variable for the wake up tick 
  u32 WakeUpTick = 0;

  // Calculate wake up tick 
  WakeUpTick = SysTickCounter + WaitTime;

  // Check counter overflow 
  if(SysTickCounter > WakeUpTick)
  {
    // TODO: Handle overflow 
    ASSERT(0);
  }
  else
  {
    // No overflow, do nothing 
  }

  // Set generic list item value 
  pRunningTask->GenericListItem.ItemValue = WakeUpTick;

  // Remove from ready list 
  OSLIST_removeItem(&pRunningTask->GenericListItem);

  // Add to timer list 
  OSLIST_insertItem(&TimerList, &pRunningTask->GenericListItem);
  
  // Trigger context switch
  __set_PENDSV();
}

void OS_destroyTask(task_t *pTask){

  // Check input parameters 
  ASSERT(pTask != NULL);

  // Check if the generic list item in any list 
  if(pTask->GenericListItem.pList != NULL)
  {
    // Remove the generic list item from the current list 
    OSLIST_removeItem(&pTask->GenericListItem);
  }
  else
  {
    // Do nothing, generic list item is not in any list 
  }

  // Check if the event list item in any list 
  if(pTask->EventListItem.pList != NULL)
  {
    // Remove the event list item from the current list 
    OSLIST_removeItem(&pTask->EventListItem);
  }
  else
  {
    // Do nothing, event list item is not in any list 
  }

  // Check if the removed task is the current task
  if(pTask == pRunningTask)
  {
    // request context switch  
    __set_PENDSV();
  }
  else
  {
    // Do nothing 
  }

}

#if (1 == USE_PRIORITY_INHERITANCE)
void OS_inheritPriority(task_t * pTask){

  // Check input parameters 
  ASSERT(NULL != pTask);

  // Check if the passed task has higher priority that the running task
  if(pTask->Priority > pRunningTask->Priority)
  {
    // Passed task has priority lower than the current task,
    // do priority inheritance 
    // Update event list item value 
    pTask->EventListItem.ItemValue = pRunningTask->Priority;

    // Check if the passed task in the ready list,
    // it will be removed and added again 
    if((void *) &ReadyList[pTask->Priority] == pTask->GenericListItem.pList)
    {
      // Remove from the ready list 
      OSLIST_removeItem(&pTask->GenericListItem);

      // Update task priority 
      pTask->Priority = pRunningTask->Priority;

      // Added to the ready list 
      OS_addTaskToReadyList(pTask);
    }
    else
    {
      // Passed task is not in the ready state, only update the priority 
      pTask->Priority = pRunningTask->Priority;
    }
  }
  else
  {
    // Do nothing, passed task has priority higher than or equal to
    // the current task
  }
}
#endif
#if (1 == USE_PRIORITY_INHERITANCE)
void OS_disinheritPriority(void){

  // Check current priority 
  if(pRunningTask->Priority != pRunningTask->OriginalPriority)
  {
    // Remove from the ready list 
    OSLIST_removeItem(&pRunningTask->GenericListItem);

    // Update task priority 
    pRunningTask->priority = pRunningTask->OriginalPriority;

    // Update event list item value 
    pRunningTask->EventListItem.ItemValue = pRunningTask->OriginalPriority;

    // Added to the ready list 
    OS_addTaskToReadyList(pRunningTask);
  }
  else
  {
    // Do nothing 
  }

}
#endif

#if (1 == USE_PRIORITY_SET)
void OS_setPriority(u32 NewPriority){

  // Check input parameters
  ASSERT(TASK_PRIORITY_LEVELS > NewPriority);

  // Get running task priority 
  u32 RunningTaskPriority;

  // Read priority 
  #if (1 == USE_PRIORITY_INHERITANCE)
  {
    RunningTaskPriority = pRunningTask->OriginalPriority;
  }
  #else
  {
    // No priority inheritance 
    RunningTaskPriority = pRunningTask->Priority;
  }
  #endif

  // Compare new priority with the current priority 
  if(NewPriority != RunningTaskPriority)
  {
    // The new priority is lower 
    if(NewPriority > RunningTaskPriority)
    {
      // Can make other task able to run, trigger context switch,
      // set PendSV to pending 
      __set_PENDSV();
    }
    else
    {
      // When increasing the priority, no need to trigger context
      // switch because the running task is always the highest priority
      // ready task
    }

    // Now change the priority 
    #if (1 == USE_PRIORITY_INHERITANCE)
    {
      // No information if the task inherited the priority 
      if(pRunningTask->OriginalPriority == pRunningTask->Priority)
      {
        // No inheritance 
        pRunningTask->Priority = NewPriority;
      }
      else
      {
        // Do nothing 
      }

      // Change the original priority 
      pRunningTask->OriginalPriority = NewPriority;
    }
    #else
    {
      // No priority inheritance 
      pRunningTask->Priority = NewPriority;
    }
    #endif

    // Set event list item value 
    pRunningTask->EventListItem.ItemValue = NewPriority;

    // Remove the running task from ready list
    OSLIST_removeItem(&pRunningTask->GenericListItem);

    // Added to the ready list 
    OS_addTaskToReadyList(pRunningTask);
  }
  else
  {
    // Do nothing, it has the same priority 
  }

}
#endif

