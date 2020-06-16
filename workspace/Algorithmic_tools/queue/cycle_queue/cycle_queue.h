#ifndef _CYCLE_QUEUE_H
#define _CYCLE_QUEUE_H
#include <pthread.h>

/**
  * data types are redefined for program portability 
  */
typedef unsigned char         uint8_t;
//typedef char                  int8_t;
typedef unsigned short int    uint16_t;
typedef short int              int16_t;
typedef unsigned int          uint32_t;
typedef int                    int32_t;


struct cube{
    char name[10];
    int32_t length;
    int32_t high;
    int32_t width; 
};
typedef struct cube TYPE_T;



struct cycle_queue{
    TYPE_T *data;
    uint32_t front;
    uint32_t rear;
    uint32_t size;
};
typedef struct cycle_queue cycle_queue_t;

/**                                                                                     
 * This function will initialize a cycle queue
 * @queue address of the queue to be used
 * @pbuff queue element buffer pointer
 * @size  number of queue elements
 *
 */
void cycle_queue_init(cycle_queue_t *queue, TYPE_T *pbuff, uint32_t size);

/**                                                                             
 * This function will creat a cycle queue
 * @size  number of queue elements
 * @return address of the queue to be used
 */
struct cycle_queue * cycle_queue_alloc(uint32_t size);

/**                                                                                             
 * This function will release cycle queue memory
 * @queue address of the queue to be used
 */
void cycle_queue_free(cycle_queue_t *queue);

/**                                                                                         
 * Put element into the queue 
 * @queue address of the queue to be used
 * @value enqueue elements 
 * @return true non-zero, false zero 
 */
int32_t cycle_queue_in(cycle_queue_t *queue, TYPE_T value);

/**                                                                                         
 * Get element from the queue 
 * @queue address of the queue to be used
 * @value enqueue elements 
 * @return true non-zero, false zero 
 */
int32_t cycle_queue_out(cycle_queue_t *queue, TYPE_T *pvalue);

/**                                                                                             
 * This function will check the queue empty status
 * @queue address of the queue to be used
 * @return true non-zero, false zero 
 */
int32_t cycle_queue_is_empty(cycle_queue_t *queue);

/**                                                                                         
 * This function will check the queue full status
 * @queue address of the queue to be used
 * @return true non-zero, false zero 
 */
int32_t cycle_queue_is_full(cycle_queue_t *queue);

/**                                                                                             
 * returns the number of used elements in the queue
 * @queue address of the queue to be used
 */
uint32_t cycle_queue_len(cycle_queue_t *queue);

/**                                                                                         
 * returns the number of all elements in the queue
 * @queue address of the queue to be used
 */
uint32_t cycle_queue_size(cycle_queue_t *queue);

/**                                                                                     
 * returns the number of unused elements in the queue
 * @queue address of the queue to be used
 */
uint32_t cycle_queue_avail(cycle_queue_t *queue);

/**                                                                                         
 * Put element into the queue safely
 * @queue address of the queue to be used
 * @value enqueue elements 
 * @plock queue thread mutex lock pointer
 * @return true non-zero, false zero 
 */
int32_t cycle_queue_in_locked(cycle_queue_t *queue, TYPE_T value, pthread_mutex_t *plock);

/**                                                                                     
 * Get element from the queue safely
 * @queue address of the queue to be used
 * @value enqueue elements 
 * @plock queue thread mutex lock pointer
 * @return true non-zero, false zero 
 */
int32_t cycle_queue_out_locked(cycle_queue_t *queue, TYPE_T *pvalue, pthread_mutex_t *plock);

/**                                                                                             
 * returns the number of used elements in the queue safely
 * @queue address of the queue to be used
 * @plock queue thread mutex lock pointer
 */
uint32_t cycle_queue_len_locked(cycle_queue_t *queue, pthread_mutex_t *plock);

/**                                                                                         
 * returns the number of all elements in the queue safely
 * @queue address of the queue to be used
 * @plock queue thread mutex lock pointer
 */
uint32_t cycle_queue_size_locked(cycle_queue_t *queue, pthread_mutex_t *plock);

/**                                                                                     
 * returns the number of unused elements in the queue safely
 * @queue address of the queue to be used
 * @plock queue thread mutex lock pointer
 */
uint32_t cycle_queue_avail_locked(cycle_queue_t *queue, pthread_mutex_t *plock);


#endif
