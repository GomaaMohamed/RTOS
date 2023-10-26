/*****************************************************************************
* @file:    OS_interface.h
* @author:  Copyright (c) 2023 Gomaa Mohammed.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Wed, 25 Oct 2023 11:21:12 +0200
* @brief:   Operating system to schedule number of tasks.
*           the Scheduler supports the following features: 
*                - priority based preemption
*                - Round robin for the ready tasks that equal in priority
*                - Priority inheritance(we can configure it in OS_config.h)
*                - Mutex
*                - Counting semaphore
*                - Mailbox
*************************************************************************/
#ifndef _OS_INTERFACE_H
#define _OS_INTERFACE_H

/* ==================================================================== */
/* ========================== Include Files =========================== */
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

/* ==================================================================== */
/* ======================= Public Data Types ========================== */
/* ==================================================================== */

/** Task data type to declare a task follow this declaration
 *  ex: task_t task1;
 */
struct task_t;

/** Stack data type to declare a stack for a specific task follow this declaration
 *  ex: stack_t task1stack;
 */
struct stack_t;

/** Mutex data type to declare a mutex follow this declaration
 *  ex: mutex_t mutex1;
 */
struct mutex_t;

/** Counting semaphore data type to declare a counting semaphore follow this declaration
 *  ex: semaphore_t semaphore1;
 */
struct semaphore_t;

/** Mailbox data type to declare a mailbox follow this declaration
 *  ex: mailbox_t mailbox1;
 */
struct mailbox_t;

/* ==================================================================== */
/* ======================== Public Macros ============================= */
/* ==================================================================== */

/** NO_WAIT macro 
 */
#define NO_WAIT                 ((s32)  0)

/** WAIT_INDEFINITELY macro 
 */
#define WAIT_INDEFINITELY       ((s32) -1)


/* ==================================================================== */
/* ==================== Public Function Prototypes ==================== */
/* ==================================================================== */

/**
 * @brief---------------------> Initialize operating system 
 * @param---------------------> None
 * @return--------------------> None
 * @preconditions-------------> None
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Called once
 * @examples------------------> 
 *          ex:   OS_init();
 */
void OS_init(void);

/**
 * @brief---------------------> Start the scheduler of the operating system
 * @parameter-----------------> None
 * @return--------------------> None
 * @preconditions-------------> Operating system is initialized OS_init();
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Called once
 * @examples------------------>
 *          ex:   OS_init(); // precondition
 *                OS_SVC_startScheduler();
 */
void OS_SVC_startScheduler(void);

/**
 * @brief---------------------> Create a task
 * @parameter1----------------> (pTask) pointer to a task instance
 * @parameter2----------------> (pStack) pointer to a stack instance
 * @parameter3----------------> (Priority) task priority
 * @parameter4----------------> (pFunction) pointer to a task task function
 * @return--------------------> None
 * @preconditions-------------> Operating system is initialized OS_init();
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 * @examples------------------>  
 *          ex:   OS_init();                // precondition
 *                task_t  task1;            // task declaration
 *                stack_t stack_of_task1;   // stack of task1
 *                void task1_function(void) // task1 function
 *                {
 *                     while(1)
 *                     {
 *                           // task code
 *                     }
 *                }
 *                OS_SVC_createTask(&task1,stack_of_task1,1,task1_function);
 */
void OS_SVC_createTask(task_t *pTask,stack_t *pStack,u32 Priority,void (*pFunction)(void));

/**
 * @brief---------------------> Used to make a delay
 * @parameter1----------------> (WaitTime) delay time in form of sechduler ticks
 * @return--------------------> None
 * @preconditions-------------> Operating system is initialized OS_init();
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Non-reentrant
 * @examples------------------>  
 *          ex:   OS_init();                // precondition
 *                task_t  task1;            // task declaration
 *                stack_t stack_of_task1;   // stack of task1
 *                void task1_function(void) // task1 function
 *                {
 *                     while(1)
 *                     {
 *                           OS_SVC_delayTask(30);
 *                     }
 *                }
 *                OS_SVC_createTask(&task1,stack_of_task1,1,task1_function);
 */
void OS_SVC_delayTask(u32 WaitTime);

/**
 * @brief---------------------> Used to delete a task
 * @parameter1----------------> (pTask) pointer to the task to be deleted
 * @return--------------------> None
 * @preconditions-------------> Operating system is initialized OS_init();
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 * @examples------------------>  
 *          ex:   OS_init();                // precondition
 *                task_t  task1;            // task declaration
 *                stack_t stack_of_task1;   // stack of task1
 *                void task1_function(void) // task1 function
 *                {
 *                     while(1)
 *                     {
 *                           OS_SVC_delayTask(30);
 *                     }
 *                }
 *                OS_SVC_destroyTask(&task1_function);
 */
void OS_SVC_destroyTask(task_t *pTask);

/**
 * @brief---------------------> Used to change the priority of the running task
 * @parameter1----------------> (NewPriority) task priority
 * @return--------------------> None
 * @preconditions-------------> Operating system is initialized OS_init();
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Reentrant
 * @examples------------------>  
 *          ex:   OS_init();                // precondition
 *                task_t  task1;            // task declaration
 *                stack_t stack_of_task1;   // stack of task1
 *                void task1_function(void) // task1 function
 *                {
 *                     while(1)
 *                     {
 *                           OS_SVC_setPriority(10);
 *                           OS_SVC_delayTask(30);
 *                     }
 *                }
 *                
 */
void OS_SVC_setPriority(u32 NewPriority);

/**
 * @brief---------------------> Used to create a mutex
 * @parameter1----------------> (pMutex) pointer to the mutex to be created
 * @parameter2----------------> (InitialValue) initial value of the mutex
 * @return--------------------> None
 * @preconditions-------------> Operating system is initialized OS_init();
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Non-reentrant
 * @examples------------------>
 *          ex:   OS_init();                // precondition
 *                task_t  task1;            // task declaration
 *                stack_t stack_of_task1;   // stack of task1
 *                mutex_t mutex;            // mutex object
 *                OS_SVC_createMutex(&mutex, 1);
 *                void task1_function(void) // task1 function
 *                {
 *                     while(1)
 *                     {
 *                           OS_SVC_setPriority(10);
 *                           OS_SVC_delayTask(30);
 *                     }
 *                }
 *
 */
void OS_SVC_createMutex(mutex_t * pMutex, u32 InitialValue);

/**
 * @brief---------------------> Used to aquire a mutex
 * @parameter1----------------> (pMutex) pointer to the mutex to be aquired
 * @parameter2----------------> (WaitTime) the time that the task will be wait for aquiring the mutex again
 * @return--------------------> None
 * @preconditions-------------> Operating system is initialized OS_init();
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Non-reentrant
 * @examples------------------>
 *          ex:   OS_init();                // precondition
 *                task_t  task1;            // task declaration
 *                stack_t stack_of_task1;   // stack of task1
 *                mutex_t mutex;            // mutex object
 *                OS_SVC_createMutex(&mutex, 1);
 *                void task1_function(void) // task1 function
 *                {
 *                     while(1)
 *                     {     
 *                           OS_SVC_lockMutex(&mutex, 30);
 *                           OS_SVC_setPriority(10);
 *                           OS_SVC_delayTask(30);
 *                     }
 *                }
 *
 */
void OS_SVC_lockMutex(mutex_t * pMutex, s32 WaitTime);

/**
 * @brief---------------------> Used to release a mutex
 * @parameter1----------------> (pMutex) pointer to the mutex to be released
 * @return--------------------> None
 * @preconditions-------------> Operating system is initialized OS_init();
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Non-reentrant
 * @examples------------------>
 *          ex:   OS_init();                // precondition
 *                task_t  task1;            // task declaration
 *                stack_t stack_of_task1;   // stack of task1
 *                mutex_t mutex;            // mutex object
 *                OS_SVC_createMutex(&mutex, 1);
 *                void task1_function(void) // task1 function
 *                {
 *                     while(1)
 *                     {     
 *                           OS_SVC_lockMutex(&mutex, 30);
 *                           OS_SVC_setPriority(10);
 *                           OS_SVC_delayTask(30);
 *                           OS_SVC_releaseMutex(&mutex);
 *                     }
 *                }
 *
 */
void OS_SVC_releaseMutex(mutex_t * pMutex);

/**
 * @brief---------------------> Used to create a semaphore
 * @parameter1----------------> (pSemaphore) pointer to the semaphore to be created
 * @parameter2----------------> (InitialValue) initial value of the semaphore
 * @return--------------------> None
 * @preconditions-------------> Operating system is initialized OS_init();
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Non-reentrant
 * @examples------------------>
 *          ex:   OS_init();                // precondition
 *                task_t  task1;            // task declaration
 *                stack_t stack_of_task1;   // stack of task1
 *                semaphore_t semaphore;    // semaphore object
 *                OS_SVC_createSemaphore(&semaphore, 1);
 *                void task1_function(void) // task1 function
 *                {
 *                     while(1)
 *                     {
 *                           OS_SVC_setPriority(10);
 *                           OS_SVC_delayTask(30);
 *                     }
 *                }
 *
 */
void OS_SVC_createSemaphore(semaphore_t * pSemaphore, u32 InitialValue);

/**
 * @brief---------------------> Used to take a semaphore
 * @parameter1----------------> (pSemaphore) pointer to the semaphore to be taken
 * @parameter2----------------> (WaitTime) the time that the task will be wait for taking the semaphore again
 * @return--------------------> None
 * @preconditions-------------> Operating system is initialized OS_init();
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Non-reentrant
 * @examples------------------>
 *          ex:   OS_init();                // precondition
 *                task_t  task1;            // task declaration
 *                stack_t stack_of_task1;   // stack of task1
 *                semaphore_t semaphore;    // semaphore object
 *                OS_SVC_createSemaphore(&semaphore, 1);
 *                void task1_function(void) // task1 function
 *                {
 *                     while(1)
 *                     {     
 *                           OS_SVC_takeSemaphore(&semaphore, 30);
 *                           OS_SVC_setPriority(10);
 *                           OS_SVC_delayTask(30);
 *                     }
 *                }
 *
 */
void OS_SVC_takeSemaphore(semaphore_t * pSemaphore, s32 WaitTime);

/**
 * @brief---------------------> Used to give the taken semaphore
 * @parameter1----------------> (pSemaphore) pointer to the semaphore to be given
 * @return--------------------> None
 * @preconditions-------------> Operating system is initialized OS_init();
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Non-reentrant
 * @examples------------------>
 *          ex:   OS_init();                // precondition
 *                task_t  task1;            // task declaration
 *                stack_t stack_of_task1;   // stack of task1
 *                semaphore_t semaphore;    // mutex object
 *                OS_SVC_createSemaphore(&semaphore, 1);
 *                void task1_function(void) // task1 function
 *                {
 *                     while(1)
 *                     {     
 *                           OS_SVC_takeSemaphore(&mutex, 30);
 *                           OS_SVC_setPriority(10);
 *                           OS_SVC_delayTask(30);
 *                           OS_SVC_giveSemaphore(&mutex);
 *                     }
 *                }
 *
 */
void OS_SVC_giveSemaphore(semaphore_t * pSemaphore);

/**
 * @brief---------------------> Used to create a mailbox
 * @parameter1----------------> (pMailbox) pointer to the mail to be created
 * @parameter2----------------> (pBuffer) pointer to the buffer of the mailbox
 * @parameter3----------------> (BufferLength) length of the buffer
 * @parameter4----------------> (MessageSize) message size of the buffer
 * @return--------------------> None
 * @preconditions-------------> Operating system is initialized OS_init();
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Non-reentrant
 * @examples------------------>
 *          ex:   OS_init();                // precondition
 *                task_t  task1;            // task declaration
 *                stack_t stack_of_task1;   // stack of task1
 *                mailbox_t mailbox;        // mailbox object
 *                u32 Buffer[10];           // buffer
 *                OS_SVC_createMailbox(&mailbox,&Buffer,40, 4);
 *                void task1_function(void) // task1 function
 *                {
 *                     while(1)
 *                     {
 *                           OS_SVC_setPriority(10);
 *                           OS_SVC_delayTask(30);
 *                     }
 *                }
 *
 */
void OS_SVC_createMailbox(mailbox_t * pMailbox, void * pBuffer, u32 BufferLength, u32 MessageSize);

/**
 * @brief---------------------> Used to write to a mailbox
 * @parameter1----------------> (pMailbox) pointer to the mailbox 
 * @parameter2----------------> (WaitTime) the time that the task will be wait for writing to a mailbox again
 * @parameter3----------------> (pMessage) message to be written
 * @return--------------------> None
 * @preconditions-------------> Operating system is initialized OS_init();
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Non-reentrant
 * @examples------------------>
 *          ex:   OS_init();                // precondition
 *                task_t  task1;            // task declaration
 *                stack_t stack_of_task1;   // stack of task1
 *                mailbox_t mailbox;        // mailbox object
 *                u32 Buffer[10];           // buffer
 *                OS_SVC_createMailbox(&mailbox,&Buffer,40, 4);
 *                void task1_function(void) // task1 function
 *                {
 *                     while(1)
 *                     {
 *                           OS_SVC_writeMailbox(&mailbox,30,&messag);
 *                           OS_SVC_setPriority(10);
 *                           OS_SVC_delayTask(30);
 *                     }
 *                }
 *
 */
void OS_SVC_writeMailbox(mailbox_t * pMailbox, s32 WaitTime,const void * const pMessage);

/**
 * @brief---------------------> Used to read from a mailbox
 * @parameter1----------------> (pMailbox) pointer to the mailbox 
 * @parameter2----------------> (WaitTime) the time that the task will be wait for reading from a mailbox again
 * @parameter3----------------> (Message) message to be read
 * @return--------------------> None
 * @preconditions-------------> Operating system is initialized OS_init();
 * @postconditions------------> None
 * @synchronous/asynchronous--> Synchronous
 * @reentrant/non-reentrant---> Non-reentrant
 * @examples------------------>
 *          ex:   OS_init();                // precondition
 *                task_t  task1;            // task declaration
 *                stack_t stack_of_task1;   // stack of task1
 *                mailbox_t mailbox;        // mailbox object
 *                u32 Buffer[10];           // buffer
 *                OS_SVC_createMailbox(&mailbox,&Buffer,40, 4);
 *                void task1_function(void) // task1 function
 *                {
 *                     while(1)
 *                     {
 *                           OS_SVC_readMailbox(&mailbox,30,&messag);
 *                           OS_SVC_setPriority(10);
 *                           OS_SVC_delayTask(30);
 *                     }
 *                }
 *
 */
void OS_SVC_readMailbox(mailbox_t * pMailbox, s32 WaitTime,void * const pMessage);



#endif
