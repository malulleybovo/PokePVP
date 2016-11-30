#ifndef __LINKED_LIST_ITERATOR_H__
#define __LINKED_LIST_ITERATOR_H__

#include <stdbool.h>
#include "LinkedList.h"

/******************************************************************************* 
*	List Iterator Definition
*******************************************************************************/
typedef struct list_iterator_t ListIterator;
struct list_iterator_t	{
    int len;
		int index;
		Node* curr;
};

/******************************************************************************* 
*	Constructor
*******************************************************************************/
ListIterator* linked_list_iterator_new(List* list);

/******************************************************************************* 
*	Destructor
*******************************************************************************/
void linked_list_iterator_free(ListIterator* itr);

/******************************************************************************* 
*	Functions
*******************************************************************************/
bool linked_list_iterator_has_next(ListIterator* itr);
void* linked_list_iterator_next(ListIterator* itr);

#endif
