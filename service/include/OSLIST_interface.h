/*****************************************************************************
* @file:    OSLIST_interface.h
* @author:  Copyright (c) 2023 Gomaa Mohammed.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Wed, 25 Oct 2023 11:21:12 +0200
* @brief:   List Module.
*******************************************************************************/
#ifndef _OSLIST_INTERFACE_H
#define _OSLIST_INTERFACE_H

/* ==================================================================== */
/* ====================== List Types Definition ======================= */
/* ==================================================================== */

/********* List Item data type *********/
struct ListItem_t
{
    u32 ItemValue;            // Used for sorting in non ready lists
    struct ListItem_t *pNext; // Pointer to the next list item
    struct ListItem_t *pPrev; // Pointer to the previous list item
    void *pTask;              // Pointer to the task of the item item
    void *pList;              // Pointer to the list item in where the item is located
};
typedef struct ListItem_t listitem_t;

/********** List End data type *********/
typedef struct 
{
    u32 ItemValue;     // used for sorting in non ready lists
    listitem_t *pNext; // pointer to the next list item
    listitem_t *pPrev; // pointer to the previous list item
}listend_t;

/********** List data type ************/
typedef struct
{
    u32 NumOfItems;     // number of items in the list
    listitem_t *pIndex; // pointer to the current item
    listend_t ListEnd;  // list end
}list_t;

/* ==================================================================== */
/* =================== Public Functions Declaration =================== */
/* ==================================================================== */

/****************** Initialize a list **************************/
void OSLIST_init(list_t * pList);

/****************** Insert an item in the list *****************/
void OSLIST_insertEndItem(list_t *pList,listitem_t *pNewItem);

/****************** Insert an item in the list *****************/
void OSLIST_insertItem(list_t *pList, listitem_t *pNewItem);

/****************** Remove an item from the list ***************/
void OSLIST_removeItem(listitem_t *pRemovedItem);

#endif
