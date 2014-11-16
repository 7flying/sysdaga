#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

/* Structure for linked list elements. */
typedef struct ListElement_ {
	void				*data;
	struct ListElement_	*next;
} ListElement;

/* Structure for linked list. */
typedef struct List_ {
	int				size;
	int				(*match) (const void *key1, const void *key2);
	void			(*destroy) (void *data);
	ListElement 	*head;
	ListElement 	*tail;
} List;

/* Interface */
/* Initializes a linked list. */
void list_init(List *list, void (*destroy)(void *data));
/* Destroys a linked list. */
void list_destroy(List *list);
/* Inserts data next to the element.*/
int list_insert_next(List *list, ListElement *element, const void *data);
/* Removes from the linked list the element after the specified element. */
int list_remove_next(List *list, ListElement *element, void **data);

/* Gets the linked list size. */
#define list_size(list) ((list)->size)
/* Gets the head element of the linked list.*/
#define list_head(list) ((list)->head)
/* Gets the tail element of the linked list. */
#define list_tail(list)	((list)->tail)
/* Checks if the element if the head of the list. */
#define list_is_head(list, element) ((element) == (list)->head ? 1 : 0)
/* Checks if the element if the tail of the list. */
#define list_is_tail(list, element) ((element) == (list)->NULL ? 1 : 0)
/* Gets the data from a list element. */
#define list_data(element) ((element)->data)
/* Gets the next element pointed by a list element. */
#define list_next(element)	((element)->next)

#endif
