/*****************************************************************************
* @file:    dispatcher.s
* @author:  Copyright (c) 2023 Gomaa Mohammed.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Wed, 25 Oct 2023 11:21:12 +0200
* @brief:   Dispatcher Modeule 
*           This module is responsible for the context switching mechanism
*           of the operating system
******************************************************************************/

// Define the type of syntax | cpu architecture | instruction set type
.syntax unified
.cpu cortex-m3
.thumb

// Define the symbols of system handlers that will be used in the dispatcher
.global SVCall_Handler
.global PendSV_Handler

// Define the section that will be used to store this part of code
.text

// Define the supervisor call handler
.type SVCall_Handler, %function
SVCall_Handler: 
    /***** Handle SVC call based on its number ******/
    tst lr, #4             // Test bit 2 of the link register to find current stack 
    ite eq                 // eq when zero flag is set 
    mrseq r0, msp          // msp when bit 2 is cleared 
    mrsne r0, psp          // msp when bit 2 is set 
    ldr r1,=svcEXEReturn   // Load the address of svcEXEReturn in r1 
    str lr,[r1]            // Store lr in svcEXEReturn 
    bl OS_SVC_Handler_main // Run C part of SVC Handler 
    ldr r1,=svcEXEReturn   // Load the address of svcEXEReturn in r1 
    ldr lr,[r1]            // Load lr with updated svcEXEReturn value 
    bx lr                  // Return */

// Define the pendsv call handler
.type PendSV_Handler, %function
PendSV_Handler:
    /******** Save current context *************/
    mrs r1, psp          // store psp in r1 
    mov r2, lr           // store lr in r2 
    mrs r3, control      // store control in r3 
    stmdb r1!,{r2-r11}   // store multiple registers (r2 to r11).
    bl OS_getRunningTask // get current running task location 
    str r1,[r0]          // Store the stack pointer for the current thread
    /******** Restore next context *************/
    mov r0, #1              // put 1 in r0 
    msr basepri, r0         // disable interrupts with priority 1 and greater 
    bl OS_switchRunningTask // change current running task
    mov r0, #0              // Put 0 in r0 
    msr basepri, r0         // enable interrupts 
    bl OS_getRunningTask    // get current running task location 
    ldr r1,[r0]             // get its value which is the stack pointer 
    ldmia r1!,{r2-r11}      // load multiple registers (r2 to r11).
    mov lr, r2              // load lr with value from r2 
    msr control, r3         // load control with value from r3 
    isb                     // instruction Synchronization Barrier
    msr psp, r1             // set psp to the stack pointer of the new current task */
    bx lr                   // return 
