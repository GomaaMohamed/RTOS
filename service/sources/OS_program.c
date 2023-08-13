/************************************************************************
* @file:     OS_interface.h
* @author:   Copyright (c) 2023 Gomaa Mohammed Gomaa.  All rights reserved.
* @version:  V0.1   
* @date:     Fri, 12 Aug 2023 18:21:12 +0300
* @brief:    Operating system to schedule number of tasks.
*            the Scheduler Algorithm supports preemption and round robin
*************************************************************************/

/* ==================================================================== */
/* ========================== include files =========================== */
/* ==================================================================== */

#include "OS_interface.h"


#define SCB_CCR *((volatile u32*)0xE000ED14)
/* ==================================================================== */
/* =========================== rtos variables ========================= */
/* ==================================================================== */

// Variable to hold the scheduler state
static u32 SchedulerRunning = 0;

// EXC_RETURN value used to return from SVC interrupts
u32 svcEXEReturn;

// Idle task prameters
static task_t   IdleTask;
static stack_t  IdleTaskStack;
void IdleTaskFunction(void);

void IdleTaskFunction(void){
  while(1){
    // Sleep for a specific time
  }
}

/* ==================================================================== */
/* ======================= functions definition ======================= */
/* ==================================================================== */

void OS_startScheduler(void);
void SysTick_Handler_main(void);
void OS_SVC_Handler_main(u32 * svc_args);

void OS_init(void){

    // disable all interrupts
    __disable_irq();

    // enable double word stack aligment
    SET_BIT(SCB_CCR,9);

    // configure system timer
    STK_voidInit();

    // configure priority group 4
    NVIC_voidInit();

    // configure ptiority levels
    NVIC_voidSetPriority(SVCall, 0, 0);    // highest pr
    NVIC_voidSetPriority(SysTick, 1, 0);  
    NVIC_voidSetPriority(PendSV, 15, 0);   // lowest pr

    // enable interrupts of SVC and PendSV

    // disable all interrupts except SVC
    __enable_irq();
    __set_BASEPRI(1);

    // initialize task module
    OS_initLists();
    
    // enable interrupts
    __enable_irq();
}

void OS_startScheduler(void)
{
  // Create idle task
  OS_createTask(&IdleTask,&IdleTaskStack,(TASK_PRIORITY_LEVELS - 1),IdleTaskFunction);

  // Pointer to the current running task 
  task_t * pRunningTask;

  // Update the running task 
  OS_switchRunningTask();

  // Get running task 
  pRunningTask = OS_getRunningTask();

  // Set SVC interrupt return to the first task 
  svcEXEReturn = MEM32_ADDRESS(pRunningTask->StackPointer);

  // Return to task with PSP 
  __set_PSP((u32)(pRunningTask->StackPointer + 10 * 4));

  // Switch to use Process Stack, unprivileged state 
  __set_CONTROL(MEM32_ADDRESS((pRunningTask->StackPointer + (1 << 2))));

  // Execute ISB after changing CONTROL 
  __ISB();

  // Flag scheduler is running 
  SchedulerRunning = 1;

  // Enable all interrupts 
  //__set_BASEPRI(0);
  __enable_irq();

  // start systick
  STK_voidSetIntervalPeriodic(SYS_TICK_RATE_MS,SysTick_Handler_main);
}

u32 OS_isSchedulerRunning(void)
{
  return SchedulerRunning;
}

void OS_SVC_Handler_main(u32 * svc_args)
{
  // Check input parameters 
  ASSERT(NULL != svc_args);

  u8 svc_number;

  // Memory[(Stacked PC)-2] 
  svc_number = ((u8 *) svc_args[6])[-2];

  // Temp variables 
  OS_return_t returnStatus;

  // Check svc number 
  switch(svc_number)
  {
    case 0:
      OS_startScheduler();
    break;

    case 1:
      OS_createTask(
          (task_t *) svc_args[0],
          (stack_t *) svc_args[1],
          (u32) svc_args[2],
          (void *) svc_args[3]);
    break;

    case 2:
      OS_createMutex((mutex_t *) svc_args[0], (u32) svc_args[1]);
    break;

    case 3:
      returnStatus = OS_lockMutex((mutex_t *) svc_args[0],
          (s32) svc_args[1]);
    break;

    case 4:
      OS_releaseMutex((mutex_t *) svc_args[0]);
    break;

    case 5:
     OS_createSemaphore((semaphore_t *) svc_args[0],
         (u32) svc_args[1]);
    break;

    case 6:
     returnStatus = OS_takeSemaphore((semaphore_t *) svc_args[0],
         (s32) svc_args[1]);
    break;

    case 7:
      OS_giveSemaphore((semaphore_t *) svc_args[0]);
    break;

    case 8:
     OS_createMailbox((mailbox_t *) svc_args[0], (void *) svc_args[1],
         (u32) svc_args[2], (u32) svc_args[3]);
    break;

    case 9:
     returnStatus = OS_writeMailbox((mailbox_t *) svc_args[0],
         (s32) svc_args[1], (const void * const) svc_args[2]);
    break;

    case 10:
     returnStatus = OS_readMailbox((mailbox_t *) svc_args[0],
         (s32) svc_args[1], (void * const) svc_args[2]);
    break;

    case 11:
      OS_addRunningTaskToTimerList((u32) svc_args[0]);
    break;

    case 12:
      OS_destroyTask((task_t *) svc_args[0]);
    break;

    case 13:
      #if (1 == USE_PRIORITY_SET)
        OS_setPriority((u32) svc_args[0]);
      #endif
    break;

    default:
      // Not supported svc call 
      ASSERT(0);
    break;
  }

  // Check svc number for return status 
  switch(svc_number)
  {

    case 3:
    case 6:
    case 9:
    case 10:
      // Check return status 
      if(OS_CONTEXT_SWITCH_TRIGGERED == returnStatus)
      {
        // Context switch was triggered, update program counter,
        // when the context is restored the task will try again 
        svc_args[6] = svc_args[6] - 2;

        // Set waiting time to no wait if it was specified 
        if(NO_WAIT < (s32) svc_args[1])
        {
          // Reset waiting time 
          svc_args[1] = NO_WAIT;
        }
        else
        {
          // Do nothing, no wait time specified 
        }
      }
      else
      {
        // No context switch was triggered, pass return value 
        svc_args[0] = returnStatus;
      }
    break;

    default:
      // Handled before 
    break;
  }
}


void SysTick_Handler_main(void)
{
  // Trigger context switch, set PendSV to pending 
  __set_PENDSV();

  // update timer list 
  OS_refreshTimerList();
}
