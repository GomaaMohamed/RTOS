/*****************************************************************************
* @file:    STD_TYPES.h
* @author:  Copyright (c) 2023 Gomaa Mohammed.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Sun, 1 Oct 2023 14:21:12 +0200
* @brief:   Standard Types Library.
******************************************************************************/

#ifndef  _STD_TYPES_H
#define  _STD_TYPES_H

typedef unsigned char          u8;
typedef unsigned short int     u16;
typedef unsigned long  int     u32;
typedef unsigned long long int u64;


typedef signed char          s8;
typedef signed short int     s16;
typedef signed long  int     s32;
typedef signed long long int s64;

typedef float     f32;
typedef double    f64;

typedef enum
{
    FALSE,
    TRUE
} boolean;

/* NULL PTR */
#define   NULL   (void *)0

#endif