#ifndef _CYCLE_QUEUE_H
#define _CYCLE_QUEUE_H
#include <pthread.h>

typedef struct{
    char name[10];
    int length;
    int high;
    int width; 
}TYPE;

struct cycle_queue{
    TYPE *data;
    unsigned int front;
    unsigned int rear;
    unsigned int size;
};

typedef struct cycle_queue *cycle_queue_t;

struct cycle_queue * cycle_queue_alloc(unsigned int size);
void cycle_queue_free(cycle_queue_t queue);
void cycle_queue_init(cycle_queue_t queue, TYPE* pbuff, unsigned int size);

int cycle_queue_in(cycle_queue_t queue, TYPE value);
int cycle_queue_in_locked(cycle_queue_t queue, TYPE value, pthread_mutex_t *f_lock);

int cycle_queue_out(cycle_queue_t queue, TYPE *pvalue);
int cycle_queue_out_locked(cycle_queue_t queue, TYPE *pvalue, pthread_mutex_t *f_lock);

int cycle_queue_is_empty(cycle_queue_t queue);
int cycle_queue_is_full(cycle_queue_t queue);

unsigned int cycle_queue_len(cycle_queue_t queue);
unsigned int cycle_queue_size(cycle_queue_t queue);
unsigned int cycle_queue_avail(cycle_queue_t queue);

#endif
