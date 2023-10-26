/*****************************************************************************
* @file:    OSMAILBOX_interface.h
* @author:  Copyright (c) 2023 Gomaa Mohammed.
* @license: GNU GPL version 3 or later.
*			      This is free software: you are free to change and redistribute it.  
*			      There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Wed, 25 Oct 2023 11:21:12 +0200
* @brief:   Mailbox Module.
*******************************************************************************/
#ifndef _OS_MAILBOX_H
#define _OS_MAILBOX_H

/* ==================================================================== */
/* ==================== Mailbox Types Definition ====================== */
/* ==================================================================== */

typedef struct
{
  s8 * pStart;        // Start location 
  s8 * pEnd;          // Last location 
  s8 * pReadIndex;    // Read location 
  s8 * pWriteIndex;   // Write location 
  u32 BufferLength;   // Length of the mailbox buffer 
  u32 MessageSize;    // Mailbox message size in bytes 
  u32 MessagesNum;    // Current number of messages inside the buffer 
  list_t WaitingList; // Waiting list 
} mailbox_t;

/* ==================================================================== */
/* =================== Public Functions Declaration =================== */
/* ==================================================================== */

/*********** Create mailbox ************/
void OS_createMailbox(mailbox_t * pMailbox, void * pBuffer, u32 BufferLength, u32 MessageSize);

/*********** Write to mailbox **********/
OS_return_t OS_writeMailbox(mailbox_t * pMailbox, s32 WaitTime,const void * const pMessage);

/*********** Read from mailbox *********/
OS_return_t OS_readMailbox(mailbox_t * pMailbox, s32 WaitTime,void * const pMessage);


#endif 
