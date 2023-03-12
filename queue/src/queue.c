#include <stdio.h>



struct queue_node 
{
    struct queue_node   *next;
    void                *data;
};

struct queue 
{
    struct queue_node   *first;
    struct queue_node   *last;
    int                 count;
};

#include <queue.h>
queue_t *queue_init() 
{
    queue_t *queue = calloc(1, sizeof(queue_t));
    if (NULL == queue) {
        // handle allocation error
        return NULL;
    }
    return queue;
}

void queue_destroy(queue_t *queue) 
{
    queue_node_t *current = queue->first;

    while (NULL != current) 
    {
        queue_node_t *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }

    free(queue);
}

void queue_enqueue(queue_t *queue, void *data) 
{
    queue_node_t *new_node = calloc(1, sizeof(queue_node_t));
    new_node->data = data;

    if (NULL == queue->first) 
    {
        queue->first = new_node;
    } 
    else if (NULL != queue->last)
    {
        queue->last->next = new_node;
    }

    queue->last = new_node;
    queue->count++;
}

void *queue_dequeue(queue_t *queue) 
{
    if (NULL == queue->first) 
    {
        return NULL;
    }

    queue_node_t *node = queue->first;
    void *data = node->data;

    queue->first = node->next;
    queue->count--;

    if (NULL == queue->first) 
    {
        queue->last = NULL;
    }

    free(node);
    return data;
}
