/*****************************************************************************
* @file:    OSTASK_interface.h
* @author:  Copyright (c) 2023 Gomaa Mohammed.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Wed, 25 Oct 2023 11:21:12 +0200
* @brief:   Task Module.
*******************************************************************************/
#ifndef _OSTASK_INTERFACE_H_
#define _OSTASK_INTERFACE_H_

/* ==================================================================== */
/* ====================== task types definition ======================= */
/* ==================================================================== */

// task type
typedef struct Task_t{
    u32 StackPointer;              // stack pointer of the task
    u32 Priority;                  // task priority
    u32 TaskID;                    // Used for trace
    listitem_t GenericListItem;    // list item of the task
    listitem_t EventListItem;      // list item of the task
    #if (1 == USE_PRIORITY_INHERITANCE)
    u32 OriginalPriority;          // task original priority 
    #endif
}task_t;

// stack type
typedef struct 
{
    u64 Stack[TASK_STACK_SIZE];
}stack_t;

/* ==================================================================== */
/* =================== Public functions declaration =================== */
/* ==================================================================== */

// create task
void OS_createTask(task_t *pTask,stack_t *pStack,u32 Priority,void (*pFunction)(void));


// initialize all lists of OS
void OS_initLists(void);

// get runnibg task
task_t* OS_getRunningTask(void);

// switch running task
void OS_switchRunningTask(void);

// add task to readu list
void OS_addTaskToReadyList(task_t *pTask);

// update timer list
void OS_refreshTimerList(void);

// transfer running task to waiting state
void OS_addRunningTaskToTimerList(u32 WaitTime);

// terminate a task
void OS_destroyTask(task_t *pTask);

// inherit priority
void OS_inheritPriority(task_t * pTask);

// deinherit priority
void OS_disinheritPriority(void);

// set task priority
void OS_setPriority(u32 NewPriority);

#endif
