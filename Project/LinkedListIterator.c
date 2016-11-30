
#include "LinkedListIterator.h"

ListIterator* linked_list_iterator_new(List* list) {
	ListIterator* itr = malloc(sizeof(ListIterator));
	itr->curr = list->head;
	itr->len = list->len;
	itr->index = -1;
	return itr;
}

void linked_list_iterator_free(ListIterator* itr) {
	free(itr);
}

bool linked_list_iterator_has_next(ListIterator* itr) {
	if (itr->curr) { // If iterator has been supplied a list
		return (itr->index < itr->len - 1);
	}
	return false;
}

void* linked_list_iterator_next(ListIterator* itr) {
	if (itr->curr && itr->index < itr->len - 1) {
		void* val = itr->curr->val;
		itr->curr = itr->curr->next;
		itr->index++;
		return val;
	}
	return NULL;
}
