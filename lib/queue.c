#include <stdlib.h>

#include "list.h"
#include "queue.h"

int queue_insert(Queue *queue, const void *data)
{
	return list_insert_next(queue, list_tail(queue), data);
}

int queue_get(Queue *queue, const void **data)
{
	return list_remove_next(queue, NULL, data);
}
