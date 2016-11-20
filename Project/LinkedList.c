
#include "LinkedList.h"

Node* node_new(void* val){
	Node* node = malloc(sizeof(Node));
			node->val = val;
			node->next = NULL;
	return node;
}

List linked_list_new(){
	List* list = malloc(sizeof(List));
	
	list->head = NULL;
	list->tail = NULL;
	list->len = 0;
	
	list->add = linkedlist_add;
	list->add_at = linked_list_add_at;
	list->remove = linked_list_remove;
	list->remove_at = linked_list_remove_at;
	list->get_at = linked_list_get_at;
	
	return *list;
}

void linkedlist_add(List* l, void* val){
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
		l->add(l, val);
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

void* linked_list_remove(List* l){
	int i = 0;
	Node* curr;
	void* val;
	
	if (l->len <= 0){
		return NULL;
	}
	
	// Get second last node
	curr = l->head;
	while(i < l->len - 2){
		curr = curr->next;
		i++;
	}
	
	// Get last node
	val = curr->next->val;
	
	// Update end of list
	curr->next = NULL;
	l->tail = curr;
	l->len--;
	
	return val;
}

void* linked_list_remove_at(List* l, int i){
	Node* curr;
	void* val;

	if (l->len <= 0 || i < 0 || i >= l->len){
		return NULL;
	}
	else if (i == l->len - 1){
		return l->remove(l);
	}
	
	// Get (i - 1)th node
	curr = l->head;
	while(i > 1){
		curr = curr->next;
		i--;
	}
	
	// Extract val at i from list
	val = curr->next->val;
	
	// Update list
	curr->next = curr->next->next;
	l->len--;
	
	return val;
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
