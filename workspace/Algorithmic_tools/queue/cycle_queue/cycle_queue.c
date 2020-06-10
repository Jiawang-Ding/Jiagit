#include "cycle_queue.h"
#include <stdio.h>
#include <stdlib.h>

struct cycle_queue * cycle_queue_alloc(unsigned int size)
{
    struct cycle_queue *pqueue;
    TYPE *pdata;

    pqueue = (struct cycle_queue*)malloc(sizeof(struct cycle_queue));
    if(pqueue == NULL){
        return NULL;
    }
    pdata = (TYPE*)malloc(sizeof(TYPE)*size);
    if(pdata == NULL){
        free(pqueue);
        return NULL;
    }

    pqueue->front = 0;
    pqueue->rear = 0;
    pqueue->data = pdata;
    pqueue->size = size;

    return pqueue;
}

void cycle_queue_free(cycle_queue_t queue)
{
    if(queue == NULL)
        return;
    if(queue->data == NULL)
        return;
    free(queue->data);
    free(queue);
}

void cycle_queue_init(cycle_queue_t queue, TYPE* pbuff, unsigned int size)
{
    if(queue == NULL || pbuff == NULL)
        return;
    queue->data = pbuff;
    queue->front = 0;
    queue->rear = 0;
    queue->size = size;
}

int cycle_queue_is_empty(cycle_queue_t queue)
{
    return (queue->front == queue->rear);
}

int cycle_queue_is_full(cycle_queue_t queue)
{
    return (((queue->rear+1) % queue->size) == queue->front);
}

int cycle_queue_in(cycle_queue_t queue, TYPE value)
{
    if(cycle_queue_is_full(queue)){
        return -1;
    }

    queue->data[queue->rear] = value;
    queue->rear = (queue->rear+1) % queue->size;

    return 0;
}

int cycle_queue_out(cycle_queue_t queue, TYPE *pvalue)
{
    if(cycle_queue_is_empty(queue))
        return -1;

    *pvalue = queue->data[queue->front];
    queue->front = (queue->front+1) % queue->size;

    return 0;
}

unsigned int cycle_queue_len(cycle_queue_t queue)
{
    return ((queue->rear - queue->front + queue->size) % queue->size);
}

unsigned int cycle_queue_size(cycle_queue_t queue)
{
    return (queue->size);
}

unsigned int cycle_queue_avail(cycle_queue_t queue)
{
    return (cycle_queue_size(queue) - cycle_queue_len(queue));
}


int cycle_queue_in_locked(cycle_queue_t queue, TYPE value, pthread_mutex_t *f_lock)
{
    int ret;
    pthread_mutex_lock(f_lock);

    ret = cycle_queue_in(queue, value);

    pthread_mutex_unlock(f_lock);

    return ret;
}

int cycle_queue_out_locked(cycle_queue_t queue, TYPE *pvalue, pthread_mutex_t *f_lock)
{
    int ret;
    pthread_mutex_lock(f_lock);

    ret = cycle_queue_out(queue, pvalue);

    pthread_mutex_unlock(f_lock);

    return ret;
}
