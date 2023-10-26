/*****************************************************************************
* @file:    OS_config.h
* @author:  Copyright (c) 2023 Gomaa Mohammed.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Wed, 25 Oct 2023 11:21:12 +0200
* @brief:   OS Module Configurations.
*************************************************************************/
#ifndef   _OS_CONFIG_H
#define   _OS_CONFIG_H 

/* ==================================================================== */
/* ======================== OS Configurations ========================= */
/* ==================================================================== */

// Configure stack size for tasks (number of double words)
#define TASK_STACK_SIZE              (128)

// Configure levels of priorities
#define TASK_PRIORITY_LEVELS         (16)

// Configure syetem clock 
#define SYSTEM_CORE_CLOCK_HZ         (8000000)

// Configure tick time of the os in micro seconds
#define SYS_TICK_RATE_MS             (1000)

// Configure priority inheritance
#define USE_PRIORITY_INHERITANCE     (0)

// Configure priority set
#define USE_PRIORITY_SET             (0)











#endif
