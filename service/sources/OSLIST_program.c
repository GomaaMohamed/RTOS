/************************************************************************
* @file:     OSLIST_program.c
* @author:   Copyright (c) 2023 Gomaa Mohammed Gomaa.  All rights reserved.
* @version:  V0.1   
* @date:     Fri, 12 Aug 2023 18:21:12 +0300
* @brief:    List Module.
*************************************************************************/

/* ==================================================================== */
/* ========================== include files =========================== */
/* ==================================================================== */

#include "OS_interface.h"

/* ==================================================================== */
/* ======================= functions definition ======================= */
/* ==================================================================== */

void OSLIST_init(list_t * pList)
{
    // Check input parameters 
    ASSERT(pList != NULL);

    // currently no tasks in the list, so the index pointing to the end 
    pList->pIndex = (listitem_t *) &pList->ListEnd;

    // list is empty, so the end pointing to itself 
    pList->ListEnd.pNext = (listitem_t *) &pList->ListEnd;
    pList->ListEnd.pPrev = (listitem_t *) &pList->ListEnd;

    //set item value for the list end 
    pList->ListEnd.ItemValue = 0xFFFFFFFF;

    // Number of tasks in the list is zero 
    pList->NumOfItems = 0;
}


void OSLIST_insertEndItem(list_t *pList,listitem_t *pNewItem)
{
    // Check input parameters 
    ASSERT(pList != NULL);
    ASSERT(pNewItem != NULL);

    // next of the new item is the next of the current item
    pNewItem->pNext = pList->pIndex->pNext;

    // previous of the new item is the current item
    pNewItem->pPrev = pList->pIndex;

    // change the item pointing to the current itm as previous
    pList->pIndex->pNext->pPrev = pNewItem;

    // current item points to the new item as next
    pList->pIndex->pNext = pNewItem;

    // index points to the new item
    pList->pIndex = pNewItem;

    // assign the new item to a list
    pNewItem->pList = (void *)pList;

    // increment list items
    pList->NumOfItems++;
}

void OSLIST_insertItem(list_t *pList,listitem_t *pNewItem)
{
    // Check input parameters 
    ASSERT(pList != NULL);
    ASSERT(pNewItem != NULL);

    // Temp for the insert index 
    listitem_t * pInsertIndex = (listitem_t *) &pList->ListEnd;

    // Get insert index, find the high item value 
    while((pInsertIndex->pNext != (listitem_t *) &pList->ListEnd)
      && (pInsertIndex->pNext->ItemValue <= pNewItem->ItemValue))
    {
      pInsertIndex = pInsertIndex->pNext;
    }

    // Connect the new item with insert index 
    pNewItem->pNext = pInsertIndex->pNext;
    pNewItem->pPrev = pInsertIndex;
    pInsertIndex->pNext->pPrev = pNewItem;
    pInsertIndex->pNext = pNewItem;

    // Set the list container for the new item 
    pNewItem->pList = (void *) pList;

    // Increment number of items in the list 
    pList->NumOfItems++;
}

void OSLIST_removeItem(listitem_t *pRemovedItem){

    // Check input parameters 
    ASSERT(NULL != pRemovedItem);

    // previous of the next item will be the previous of the removed item
    pRemovedItem->pNext->pPrev = pRemovedItem->pPrev;

    // next of the previous item will be the next of the removed item
    pRemovedItem->pPrev->pNext = pRemovedItem->pNext;

    // temp pointer to a list
    list_t *pList = (list_t *)pRemovedItem->pList;

    // if the index pointing to the removed item
    // make it points to the previous item
    if (pRemovedItem == pList->pIndex)
    {
        pList->pIndex = pRemovedItem->pPrev;
    }
    else{
        // do nothing
    }

    // remove the item from the list
    pRemovedItem->pList = NULL;

    // decrement list items
    pList->NumOfItems--;
}

