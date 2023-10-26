/*****************************************************************************
* @file:    NVIC_config.h
* @author:  Copyright (c) 2023 Gomaa Mohammed Gomaa.
* @license: GNU GPL version 3 or later.
*		This is free software: you are free to change and redistribute it.  
*		There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Thu, 5 Oct 2023 17:21:12 +0200
* @brief:   Nested Vectored Interrupt Controller(NVIC) Driver for STM32F103
******************************************************************************/
#ifndef _NVIC_CONFIG_H
#define _NVIC_CONFIG_H

/* ==================================================================== */
/* =================== Configurations Selection ======================= */
/* ==================================================================== */

/* select priority group combination
      Options:
      NVIC_GROUP3      >> 4 bits for group & 0 bit for sub
      NVIC_GROUP4      >> 3 bits for group & 1 bit for sub
      NVIC_GROUP5      >> 2 bits for group & 2 bit for sub
      NVIC_GROUP6      >> 1 bits for group & 3 bit for sub
      NVIC_GROUP7      >> 0 bits for group & 4 bit for sub
*/
#define  PRIORITY_GROUP_COMBINATION  NVIC_GROUP3 


#endif
