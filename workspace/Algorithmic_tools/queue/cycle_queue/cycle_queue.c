#include "cycle_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/**                                                                                                  
 * This function will initialize a cycle queue
 * @queue address of the queue to be used
 * @pbuff queue element buffer pointer
 * @size  number of queue elements
 * @plock queue thread mutex pointer
 *
 */
void cycle_queue_init(cycle_queue_t *queue, 
                        TYPE_T* pbuff, 
                        unsigned int size,
                        pthread_mutex_t *plock)
{
    if(queue == NULL || pbuff == NULL)
        return;
    queue->data = pbuff;
    queue->front = 0;
    queue->rear = 0;
    queue->size = size;
    queue->plock = plock;
}

/**                                                                                                  
 * This function will creat a cycle queue
 * @size  number of queue elements
 * @plock queue thread mutex pointer
 * @return address of the queue to be used
 */
struct cycle_queue * cycle_queue_alloc(unsigned int size, pthread_mutex_t *plock)
{
    struct cycle_queue *pqueue;
    TYPE_T *pdata;

    pqueue = (struct cycle_queue*)malloc(sizeof(struct cycle_queue));
    if(pqueue == NULL){
        return NULL;
    }
    pdata = (TYPE_T*)malloc(sizeof(TYPE_T)*size);
    if(pdata == NULL){
        free(pqueue);
        return NULL;
    }

    cycle_queue_init(pqueue, pdata, size, plock);

    return pqueue;
}

/**                                                                                                  
 * This function will release cycle queue memory
 * @queue address of the queue to be used
 */
void cycle_queue_free(cycle_queue_t *queue)
{
    if(queue == NULL)
        return;
    if(queue->data == NULL)
        return;
    free(queue->data);
    free(queue);
}

/**                                                                                                  
 * This function will check the queue empty status
 * @queue address of the queue to be used
 * @return true non-zero, false zero 
 */
int cycle_queue_is_empty(cycle_queue_t *queue)
{
    return (queue->front == queue->rear);
}

/**                                                                                                  
 * This function will check the queue full status
 * @queue address of the queue to be used
 * @return true non-zero, false zero 
 */
int cycle_queue_is_full(cycle_queue_t *queue)
{
    return (((queue->rear+1) % queue->size) == queue->front);
}

/**                                                                                                  
 * Put element into the queue 
 * @queue address of the queue to be used
 * @value enqueue elements 
 * @return true non-zero, false zero 
 */
int cycle_queue_in(cycle_queue_t *queue, TYPE_T value)
{
    if(cycle_queue_is_full(queue)){
        return 1;
    }

    queue->data[queue->rear] = value;
    queue->rear = (queue->rear+1) % queue->size;

    return 0;
}

/**                                                                                                  
 * Get element from the queue 
 * @queue address of the queue to be used
 * @value enqueue elements 
 * @return true non-zero, false zero 
 */
int cycle_queue_out(cycle_queue_t *queue, TYPE_T *pvalue)
{
    if(cycle_queue_is_empty(queue)){
        return 1;
    }

    *pvalue = queue->data[queue->front];
    queue->front = (queue->front+1) % queue->size;

    return 0;
}

/**                                                                                                  
 * returns the number of used elements in the queue
 * @queue address of the queue to be used
 */
unsigned int cycle_queue_len(cycle_queue_t *queue)
{
    return ((queue->rear - queue->front + queue->size) % queue->size);
}

/**                                                                                                  
 * returns the number of all elements in the queue
 * @queue address of the queue to be used
 */
unsigned int cycle_queue_size(cycle_queue_t *queue)
{
    return (queue->size);
}

/**                                                                                                  
 * returns the number of unused elements in the queue
 * @queue address of the queue to be used
 */
unsigned int cycle_queue_avail(cycle_queue_t *queue)
{
    return (cycle_queue_size(queue) - cycle_queue_len(queue));
}


/**                                                                                                  
 * Put element into the queue safely
 * @queue address of the queue to be used
 * @value enqueue elements 
 * @return true non-zero, false zero 
 */
int cycle_queue_in_locked(cycle_queue_t *queue, TYPE_T value)
{
    int ret;

    if(queue->plock == NULL)
        return -2;
    pthread_mutex_lock(queue->plock);

    ret = cycle_queue_in(queue, value);

    pthread_mutex_unlock(queue->plock);

    return ret;
}

/**                                                                                                  
 * Get element from the queue safely
 * @queue address of the queue to be used
 * @value enqueue elements 
 * @return true non-zero, false zero 
 */
int cycle_queue_out_locked(cycle_queue_t *queue, TYPE_T *pvalue)
{
    int ret;

    if(queue->plock == NULL)
        return -2;
    pthread_mutex_lock(queue->plock);

    ret = cycle_queue_out(queue, pvalue);

    pthread_mutex_unlock(queue->plock);

    return ret;
}
