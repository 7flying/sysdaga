#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include "list.h"

/* Define the queue as a linked list */
typedef List Queue;

/* Interface */
/* Initialises a queue */
#define queue_init list_init
/* Destroys a queue */
#define queue_destroy list_destroy
/* Inserts an element at the tail of the queue*/
int queue_insert(Queue *queue, const void *data);
/* Removes and returns the element at the head of the queue */
int queue_get(Queue *queue, void **data);
/* Returns but not deletes the element at the head of a queue */
#define queue_peek(queue) ((queue)->head == NULL ? NULL : (queue)->head->data)
/* Returns the size of a queue */
#define queue_size list_size
#endif
