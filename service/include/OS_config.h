/************************************************************************
* @file:     OS_config.h
* @author:   Copyright (c) 2023 Gomaa Mohammed Gomaa.  All rights reserved.
* @version:  V0.1   
* @date:     Fri, 12 Aug 2023 18:21:12 +0300
* @brief:    OS Module.
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
