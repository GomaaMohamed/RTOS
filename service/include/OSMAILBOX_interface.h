/************************************************************************
* @file:     OSMAILBOX_interface.h
* @author:   Copyright (c) 2023 Gomaa Mohammed Gomaa.  All rights reserved.
* @version:  V0.1   
* @date:     Fri, 12 Aug 2023 18:21:12 +0300
* @brief:    Mailbox Module.
*************************************************************************/
#ifndef __OS_MAILBOX_H_
#define __OS_MAILBOX_H_

/* ==================================================================== */
/* ==================== mailbox types definition ====================== */
/* ==================================================================== */

typedef struct
{
  s8 * pStart;          // Start location 
  s8 * pEnd;            // Last location 
  s8 * pReadIndex;      // Read location 
  s8 * pWriteIndex;     // Write location 
  u32 BufferLength;     // Length of the mailbox buffer 
  u32 MessageSize;      // Mailbox message size in bytes 
  u32 MessagesNum;      // Current number of messages inside the buffer 
  list_t WaitingList;   // Waiting list 
} mailbox_t;

/* ==================================================================== */
/* =================== Public functions declaration =================== */
/* ==================================================================== */

// create mailbox
void OS_createMailbox(mailbox_t * pMailbox, void * pBuffer, u32 BufferLength, u32 MessageSize);

// write to mailbox
OS_return_t OS_writeMailbox(mailbox_t * pMailbox, s32 WaitTime,const void * const pMessage);

// read from mailbox
OS_return_t OS_readMailbox(mailbox_t * pMailbox, s32 WaitTime,void * const pMessage);


#endif 
