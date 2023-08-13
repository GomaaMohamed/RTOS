/************************************************************************
* @file:     OSLIST_interface.h
* @author:   Copyright (c) 2023 Gomaa Mohammed Gomaa.  All rights reserved.
* @version:  V0.1   
* @date:     Fri, 12 Aug 2023 18:21:12 +0300
* @brief:    List Module.
*************************************************************************/
#ifndef _OSLIST_INTERFACE_H_
#define _OSLIST_INTERFACE_H_

/* ==================================================================== */
/* ====================== list types definition ======================= */
/* ==================================================================== */

/********* list item type *********/
struct ListItem_t{
    u32 ItemValue;             // used for sorting in non ready lists
    struct ListItem_t *pNext;  // pointer to the next list item
    struct ListItem_t *pPrev;  // pointer to the previous list item
    void *pTask;               // pointer to the task of the item item
    void *pList;               // pointer to the list item in where the item is located
};
typedef struct ListItem_t listitem_t;

/********** list end type *********/
typedef struct 
{
    u32 ItemValue;      // used for sorting in non ready lists
    listitem_t *pNext;  // pointer to the next list item
    listitem_t *pPrev;  // pointer to the previous list item
}listend_t;

/********** list type ************/
typedef struct{
    u32 NumOfItems;    // number of items in the list
    listitem_t *pIndex; // pointer to the current item
    listend_t ListEnd; // list end
}list_t;

/* ==================================================================== */
/* =================== Public functions declaration =================== */
/* ==================================================================== */

/****************** initialize a list **************************/
void OSLIST_init(list_t * pList);

/****************** insert an item in the list *****************/
void OSLIST_insertEndItem(list_t *pList,listitem_t *pNewItem);

/****************** insert an item in the list *****************/
void OSLIST_insertItem(list_t *pList, listitem_t *pNewItem);

/****************** remove an item from the list ***************/
void OSLIST_removeItem(listitem_t *pRemovedItem);

#endif
