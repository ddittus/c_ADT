#ifndef QUEUE_H
#define QUEUE_H

#include "error_handler.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct queue_node queue_node_t;
typedef struct queue queue_t;


queue_t *queue_init();
void queue_destroy(queue_t *queue);
void queue_enqueue(queue_t *queue, void* data);
void* queue_dequeue(queue_t *queue);
int queue_count(queue_t *queue);

#ifdef __cplusplus
}

#endif

#endif