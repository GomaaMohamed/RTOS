/*****************************************************************************
* @file:    OS_program.c
* @author:  Copyright (c) 2023 Gomaa Mohammed.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Wed, 25 Oct 2023 11:21:12 +0200
* @brief:   Operating system to schedule number of tasks.
*           the Scheduler Algorithm supports preemption and round robin
******************************************************************************/

/* ==================================================================== */
/* ========================== Include Files =========================== */
/* ==================================================================== */

#include "OS_interface.h"

/* ==================================================================== */
/* ============== Rtos Variables  and Private Prototypes ============== */
/* ==================================================================== */

// Variable to hold the scheduler state
static u32 SchedulerRunning = 0;

// EXC_RETURN value used to return from SVC interrupts
u32 svcEXEReturn;

// Idle task prameters and definition
static task_t   IdleTask;
static stack_t  IdleTaskStack;
void IdleTaskFunction(void);
void IdleTaskFunction(void)
{
  while(1)
  {
    // Sleep for a specific time
  }
}

// Private prototypes
void OS_startScheduler(void);
void SysTick_Handler_main(void);
void OS_SVC_Handler_main(u32 * svc_args);

// System control block
#define SCB_CCR *((volatile u32*)0xE000ED14)

/* ==================================================================== */
/* ===================== Functions Implementation ===================== */
/* ==================================================================== */

// Function to initialize operating system
void OS_init(void)
{

    // Disable all interrupts
    __disable_irq();

    // Enable double word stack aligment
    SET_BIT(SCB_CCR,9);

    // Configure system timer
    STK_init();

    // Configure priority group 4
    NVIC_init();

    // Configure priority levels
    NVIC_setPriority(NVIC_SVCall, 0, 0);    // Highest pr
    NVIC_setPriority(NVIC_SysTick, 1, 0);  
    NVIC_setPriority(NVIC_PendSV, 15, 0);   // Lowest pr

    // Enable interrupts of SVC and PendSV

    // Disable all interrupts except SVC
    __enable_irq();
    __set_BASEPRI(1);

    // Initialize list module
    OS_initLists();
    
    // Enable interrupts
    __enable_irq();
}

// Function to start the scheduler
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
    STK_setPeriodicInterval(SYS_TICK_RATE_MS,SysTick_Handler_main);
}

// Function to check if the scheduler is running or not
u32 OS_isSchedulerRunning(void)
{
    return SchedulerRunning;
}

// Supervisor call handler
void OS_SVC_Handler_main(u32 * svc_args)
{
    // Check input parameters 
    ASSERT(NULL != svc_args);

    // Variable to hald the number of SVC
    u8 svc_number;

    // Memory[(Stacked PC)-2] 
    svc_number = ((u8 *) svc_args[6])[-2];

    // Temp variables 
    OS_return_t returnStatus;

    // Check svc number 
    switch(svc_number)
    {
        case 0:
            // SVC 0 to start the scheduler
            OS_startScheduler();
        break;
        case 1:
            // SVC 1 to create a task
            OS_createTask((task_t *) svc_args[0], (stack_t *) svc_args[1], (u32) svc_args[2], (void *) svc_args[3]);
        break;
        case 2:
            // SVC 2 to create a mutex
            OS_createMutex((mutex_t *) svc_args[0], (u32) svc_args[1]);
        break;
        case 3:
            // SVC 3 to lock a mutex
            returnStatus = OS_lockMutex((mutex_t *) svc_args[0], (s32) svc_args[1]);
        break;
        case 4:
            // SVC 4 to realease mutex
            OS_releaseMutex((mutex_t *) svc_args[0]);
        break;
        case 5:
            // SVC 5 to crate semaphore
            OS_createSemaphore((semaphore_t *) svc_args[0], (u32) svc_args[1]);
        break;
        case 6:
            // SVC 6 to take semaphore
            returnStatus = OS_takeSemaphore((semaphore_t *) svc_args[0], (s32) svc_args[1]);
        break;
        case 7:
            // SVC 7 to give semaphore
            OS_giveSemaphore((semaphore_t *) svc_args[0]);
        break;
        case 8:
            // SVC 8 to create mailbox
            OS_createMailbox((mailbox_t *) svc_args[0], (void *) svc_args[1], (u32) svc_args[2], (u32) svc_args[3]);
        break;
        case 9:
            // SVC 9 to write mailbox
            returnStatus = OS_writeMailbox((mailbox_t *) svc_args[0], (s32) svc_args[1], (const void * const) svc_args[2]);
        break;
        case 10:
            // SVC 10 to read mailbox
            returnStatus = OS_readMailbox((mailbox_t *) svc_args[0], (s32) svc_args[1], (void * const) svc_args[2]);
        break;
        case 11:
          OS_addRunningTaskToTimerList((u32) svc_args[0]);
        break;

        case 12:
          OS_destroyTask((task_t *) svc_args[0]);
        break;

        case 13:
            // SVC 13 to set priority
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
            if(returnStatus == OS_CONTEXT_SWITCH_TRIGGERED)
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

// SysTick Handler
void SysTick_Handler_main(void)
{
    // Trigger context switch, set PendSV to pending 
    __set_PENDSV();

    // Update timer list to handle delayes and periods
    OS_refreshTimerList();
}
