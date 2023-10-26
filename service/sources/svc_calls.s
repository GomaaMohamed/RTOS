/*****************************************************************************
* @file:    svc_calls.s
* @author:  Copyright (c) 2023 Gomaa Mohammed.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Wed, 25 Oct 2023 11:21:12 +0200
* @brief:   Supervisor Call Modeule 
*           This module is responsible for handling the supervisor calls
*           that implement the system calls of the operating system
******************************************************************************/

// Define the type of syntax | cpu architecture | instruction set type
.syntax unified
.cpu cortex-m3
.thumb

// Define the symbols system calls
.global OS_SVC_startScheduler
.global OS_SVC_createTask

.global OS_SVC_createMutex
.global OS_SVC_lockMutex
.global OS_SVC_releaseMutex

.global OS_SVC_createSemaphore
.global OS_SVC_takeSemaphore
.global OS_SVC_giveSemaphore

.global OS_SVC_createMailbox
.global OS_SVC_writeMailbox
.global OS_SVC_readMailbox

.global OS_SVC_delayTask
.global OS_SVC_destroyTask

.global OS_SVC_setTaskPriority

// Define the section that will be used to store this part of code
.text

// Define the supervisor call functions
.type OS_SVC_startScheduler, %function
OS_SVC_startScheduler:
    svc 0
    bx lr

.type OS_SVC_createTask, %function
OS_SVC_createTask:
    svc 1
    bx lr

.type OS_SVC_createMutex, %function
OS_SVC_createMutex:
    svc 2
    bx lr

.type OS_SVC_lockMutex, %function
OS_SVC_lockMutex:
    svc 3
    bx lr

.type OS_SVC_releaseMutex, %function
OS_SVC_releaseMutex:
    svc 4
    bx lr

.type OS_SVC_createSemaphore, %function
OS_SVC_createSemaphore:
    svc 5
    bx lr

.type OS_SVC_takeSemaphore, %function
OS_SVC_takeSemaphore:
    svc 6
    bx lr

.type OS_SVC_giveSemaphore, %function
OS_SVC_giveSemaphore:
    svc 7
    bx lr

.type OS_SVC_createMailbox, %function
OS_SVC_createMailbox:
    svc 8
    bx lr

.type OS_SVC_writeMailbox, %function
OS_SVC_writeMailbox:
    svc 9
    bx lr

.type OS_SVC_readMailbox, %function
OS_SVC_readMailbox:
    svc 10
    bx lr

.type OS_SVC_delayTask, %function
OS_SVC_delayTask:
    svc 11
    bx lr

.type OS_SVC_destroyTask, %function
OS_SVC_destroyTask:
    svc 12
    bx lr

.type OS_SVC_setTaskPriority, %function
OS_SVC_setTaskPriority:
    svc 13
    bx lr
