
#include "LinkedList.h"

Node* node_new(void* val){
	Node* node = malloc(sizeof(Node));
			node->val = val;
			node->next = NULL;
	return node;
}

List* linked_list_new(){
	List* list = malloc(sizeof(List));
	
	list->head = NULL;
	list->tail = NULL;
	list->len = 0;
	
	return list;
}

void linked_list_add(List* l, void* val){
	Node* newNode = node_new(val);
	
	if (l->len == 0){
		l->head = newNode;
		l->tail = newNode;
	}
	else{
		l->tail->next = newNode;
		l->tail = newNode;
	}
	
	l->len++;
}

void linked_list_add_at(List* l, void* val, int i){
	Node* curr;
	Node* newNode;

	if (i < 0 || i > l->len){
		return;
	}
	else if (i == l->len){
		linked_list_add(l, val);
		return;
	}
	
	// Get (i - 1)st node
	curr = l->head;
	while(i > 1){
		curr = curr->next;
		i--;
	}
	
	newNode = malloc(sizeof(Node));
	newNode->val = val;
	
	if (i == 0){
		newNode->next = l->head;
		l->head = newNode;
	}
	else {
		newNode->next = curr->next;
		curr->next = newNode;
	}
	
	l->len++;
}

void linked_list_remove(List* l){ 
	int i = 0;
	Node* curr;
	
	if (l->len <= 0){
		return;
	}
	else if (l->len == 1) {
		free(l->head);
		l->head = NULL;
		l->tail = NULL;
		l->len = 0;
		return;
	}
	
	// Get second last node
	// Note: curr is the last node if len is 1
	curr = l->head;
	while(i < l->len - 2){
		curr = curr->next;
		i++;
	}
	
	// Update end of list
	free(curr->next);
	curr->next = NULL;
	l->tail = curr;
	l->len--;
}

void linked_list_remove_at(List* l, int i){
	Node* curr;
	Node* toRemove;

	if (l->len <= 0 || i < 0 || i >= l->len){
		return;
	}
	else if (i == l->len - 1){
		linked_list_remove(l);
		return;
	}
	else if (i == 0){
		toRemove = l->head;
		l->head = l->head->next;
		free(toRemove);
		l->len--;
		return;
	}
	
	// Get (i - 1)th node
	curr = l->head;
	while(i > 1){
		curr = curr->next;
		i--;
	}
	
	// Update list
	toRemove = curr->next;
	curr->next = curr->next->next;
	free(toRemove);
	l->len--;
	
	return;
}

void* linked_list_get_at(List* l, int i){
	Node* curr;
	
	if (l->len <= 0 || i < 0 || i >= l->len){
		return NULL;
	}
	
	curr = l->head;
	while(i > 0){
		curr = curr->next;
		i--;
	}
	return curr->val;
}
