/*****************************************************************************
* @file:    OSLIST_program.c
* @author:  Copyright (c) 2023 Gomaa Mohammed.
* @license: GNU GPL version 3 or later.
*			This is free software: you are free to change and redistribute it.  
*			There is NO WARRANTY, to the extent permitted by law.
* @version: V0.2   
* @date:    Wed, 25 Oct 2023 11:21:12 +0200
* @brief:   List Module.
*******************************************************************************/

/* ==================================================================== */
/* ========================== Include Files =========================== */
/* ==================================================================== */

#include "OS_interface.h"

/* ==================================================================== */
/* ===================== Functions Implementation ===================== */
/* ==================================================================== */

// Function to initialize an os list
void OSLIST_init(list_t * pList)
{
    // Check input parameters 
    ASSERT(pList != NULL);

    // Currently no tasks in the list, so the index pointing to the end 
    pList->pIndex = (listitem_t *) &pList->ListEnd;

    // List is empty, so the end pointing to itself 
    pList->ListEnd.pNext = (listitem_t *) &pList->ListEnd;
    pList->ListEnd.pPrev = (listitem_t *) &pList->ListEnd;
    
    // Set item value for the list end 
    pList->ListEnd.ItemValue = 0xFFFFFFFF;

    // Number of tasks in the list is zero 
    pList->NumOfItems = 0;
}

// Function to insert a node at the end of the list
void OSLIST_insertEndItem(list_t *pList,listitem_t *pNewItem)
{
    // Check input parameters 
    ASSERT(pList != NULL);
    ASSERT(pNewItem != NULL);

    // Next of the new item is the next of the current item
    pNewItem->pNext = pList->pIndex->pNext;

    // Previous of the new item is the current item
    pNewItem->pPrev = pList->pIndex;

    // Change the item pointing to the current itm as previous
    pList->pIndex->pNext->pPrev = pNewItem;

    // Current item points to the new item as next
    pList->pIndex->pNext = pNewItem;

    // Index points to the new item
    pList->pIndex = pNewItem;

    // Assign the new item to a list
    pNewItem->pList = (void *)pList;

    // Increment list items
    pList->NumOfItems++;
}

// Function to insert a node in the list
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

// Function to remove a node from the list
void OSLIST_removeItem(listitem_t *pRemovedItem)
{
    // Check input parameters 
    ASSERT(NULL != pRemovedItem);

    // Previous of the next item will be the previous of the removed item
    pRemovedItem->pNext->pPrev = pRemovedItem->pPrev;

    // Next of the previous item will be the next of the removed item
    pRemovedItem->pPrev->pNext = pRemovedItem->pNext;

    // Temp pointer to a list
    list_t *pList = (list_t *)pRemovedItem->pList;

    // If the index pointing to the removed item
    // Make it points to the previous item
    if (pRemovedItem == pList->pIndex)
    {
        pList->pIndex = pRemovedItem->pPrev;
    }
    else
    {
        // do Nothing
    }

    // Remove the item from the list
    pRemovedItem->pList = NULL;

    // Decrement list items
    pList->NumOfItems--;
}

