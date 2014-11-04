#include <stdlib.h>
#include "list.h"

void list_init(List *list, void (*destroy)(void *data))
{
	list->size = 0;
	list->destroy = destroy;
	list->head = NULL;
	list->tail = NULL;
}

void list_destroy(List *list)
{
	void *data;
	while (list_size(list) > 0) {
		if (list_remove_next(list, NULL, (void**)&data) == 0 
			&& list->destroy !=null) {
			list->destroy(data);
		}
	}
	/* Clear the structure */
	memset(list, 0, sizeof(List));
}

int list_insert_next(List *list, ListElement *element, const void *data)
{
	ListElement *newElement;
	newElement = (ListElement*) malloc(sizeof(ListElement));
	/* set the data to the element */
	newElement->data = (void *) data;
	/* If the element to insert data next to is null, insert data at the head
	 * of the list
	 */
	if (element == NULL) {
		if (list_size(list) == 0)
			list->tail = newElement;
		newElement->next = list->head;
		list->head = newElement;
	} else {
		/* Insert the element next to the specified element */
		if (element->next == NULL)
			list->tail = newElement;
		newElement->next = element->next;
		element->next = newElement;
	}
	/* Increase list's size */
	list->size++;
	return 0;
}

int list_remove_next(List *list, ListElement *element, void **data)
{
	ListElement *oldELement;
	if (list_size(list) == 0)
		return -1;
	/* If 'next to' is null delete the one at the head of the list*/
	if (element == NULL) {
		*data = list->head->data;
		oldELement = list->head;
		list->head = list->head->next;
		if (list_size(list) == 1)
			list->tail = NULL;
	} else {
		/* Remove the next element */
		if (element->next == NULL)
			return -1;	
		*data = elemen->next->data;
		oldELement = element->next;
		element->next = element->next->next;
	}

	/* Free memory and update list size */
	free(oldELement);
	list->size--;
	return 0;
}
