// Copyright (c) 2015-16, Joe Krachey
// All rights reserved.
//
// Redistribution and use in source or binary form, with or without modification, 
// are permitted provided that the following conditions are met:
//
// 1. Redistributions in source form must reproduce the above copyright 
//    notice, this list of conditions and the following disclaimer in 
//    the documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
	
		void (*add) (List* l, void* val);
		void (*add_at) (List* l, void* val, int i);
		void* (*remove) (List* l);
		void* (*remove_at) (List* l, int i);
		void* (*get_at) (List* l, int i);
};

/******************************************************************************* 
*	Constructor
*******************************************************************************/
Node* node_new(void* val);
List linked_list_new(void);

/******************************************************************************* 
*	Functions
*******************************************************************************/
void linkedlist_add(List* l, void* val);
void linked_list_add_at(List* l, void* val, int i);
void* linked_list_remove(List* l);
void* linked_list_remove_at(List* l, int i);
void* linked_list_get_at(List* l, int i);
void* linked_list_search(List* l, void* val);

#endif
