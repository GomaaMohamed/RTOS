/*********************************************************************************/
/* Author    : Gomaa Mohammed                                                      */
/* Version   : V01                                                               */
/* Date      : 19 August 2020                                                     */
/*********************************************************************************/

#ifndef _NVIC_CONFIG_H_
#define _NVIC_CONFIG_H_

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
