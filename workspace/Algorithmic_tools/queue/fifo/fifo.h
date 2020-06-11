#ifndef _FIFO_H
#define _FIFO_H


typedef struct{
    char name[10];
    int length;
    int high;
    int width; 
}TYPE;

struct fifo{
    TYPE *data;
    unsigned int front;
    unsigned int rear;
    unsigned int size;
};

typedef struct fifo *fifo_t;

struct fifo * fifo_alloc(unsigned int size);
void fifo_free(fifo_t fifo);
void fifo_init(fifo_t fifo, TYPE* pbuff, unsigned int size);
int fifo_in(fifo_t fifo, TYPE value);
int fifo_out(fifo_t fifo, TYPE *pvalue);
int fifo_is_empty(fifo_t fifo);
int fifo_is_full(fifo_t fifo);
int fifo_len_get(fifo_t fifo);

#endif
