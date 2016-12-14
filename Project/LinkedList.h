#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/******************************************************************************* 
*	Node Definition
*******************************************************************************/
typedef struct node_t Node;
struct node_t	{
    void* val;
    Node * next;
};

/******************************************************************************* 
*	List Definition
*******************************************************************************/
typedef struct list_t List;
struct list_t	{
    Node* head;
		Node* tail;
    int len;
};

/******************************************************************************* 
*	Constructor
*******************************************************************************/
Node* node_new(void* val);
List* linked_list_new(void);

/******************************************************************************* 
*	Functions
*******************************************************************************/
void linked_list_add(List* l, void* val);
void linked_list_add_at(List* l, void* val, int i);
void linked_list_remove(List* l);
void linked_list_remove_at(List* l, int i);
void* linked_list_get_at(List* l, int i);

#endif
