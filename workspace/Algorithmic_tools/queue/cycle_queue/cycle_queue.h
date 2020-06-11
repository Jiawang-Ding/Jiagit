#ifndef _CYCLE_QUEUE_H
#define _CYCLE_QUEUE_H
#include <pthread.h>

struct cube{
    char name[10];
    int length;
    int high;
    int width; 
};

typedef struct cube TYPE_T;


struct cycle_queue{
    TYPE_T *data;
    unsigned int front;
    unsigned int rear;
    unsigned int size;
    pthread_mutex_t *plock;
};

typedef struct cycle_queue cycle_queue_t;

/**                                                                                     
 * This function will initialize a cycle queue
 * @queue address of the queue to be used
 * @pbuff queue element buffer pointer
 * @size  number of queue elements
 * @plock queue thread mutex pointer
 *
 */
void cycle_queue_init(cycle_queue_t *queue, 
                      TYPE_T *pbuff, 
                      unsigned int size, 
                      pthread_mutex_t *plock);

/**                                                                             
 * This function will creat a cycle queue
 * @size  number of queue elements
 * @plock queue thread mutex pointer
 * @return address of the queue to be used
 */
struct cycle_queue * cycle_queue_alloc(unsigned int size, pthread_mutex_t *plock);

/**                                                                                             
 * This function will release cycle queue memory
 * @queue address of the queue to be used
 *
 */
void cycle_queue_free(cycle_queue_t *queue);

/**                                                                                         
 * Put element into the queue 
 * @queue address of the queue to be used
 * @value enqueue elements 
 * @return true non-zero, false zero 
 */
int cycle_queue_in(cycle_queue_t *queue, TYPE_T value);

/**                                                                                         
 * Put element into the queue safely
 * @queue address of the queue to be used
 * @value enqueue elements 
 * @return true non-zero, false zero 
 */
int cycle_queue_in_locked(cycle_queue_t *queue, TYPE_T value);

/**                                                                                         
 * Get element from the queue 
 * @queue address of the queue to be used
 * @value enqueue elements 
 * @return true non-zero, false zero 
 */
int cycle_queue_out(cycle_queue_t *queue, TYPE_T *pvalue);

/**                                                                                     
 * Get element from the queue safely
 * @queue address of the queue to be used
 * @value enqueue elements 
 * @return true non-zero, false zero 
 */
int cycle_queue_out_locked(cycle_queue_t *queue, TYPE_T *pvalue);

/**                                                                                             
 * This function will check the queue empty status
 * @queue address of the queue to be used
 * @return true non-zero, false zero 
 */
int cycle_queue_is_empty(cycle_queue_t *queue);

/**                                                                                         
 * This function will check the queue full status
 * @queue address of the queue to be used
 * @return true non-zero, false zero 
 */
int cycle_queue_is_full(cycle_queue_t *queue);

/**                                                                                             
 * returns the number of used elements in the queue
 * @queue address of the queue to be used
 */
unsigned int cycle_queue_len(cycle_queue_t *queue);

/**                                                                                         
 * returns the number of all elements in the queue
 * @queue address of the queue to be used
 */
unsigned int cycle_queue_size(cycle_queue_t *queue);

/**                                                                                     
 * returns the number of unused elements in the queue
 * @queue address of the queue to be used
 */
unsigned int cycle_queue_avail(cycle_queue_t *queue);

#endif
