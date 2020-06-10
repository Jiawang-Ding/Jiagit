#include "fifo.h"
#include <stdio.h>
#include <stdlib.h>

struct fifo * fifo_alloc(unsigned int size)
{
    struct fifo *pfifo;
    TYPE *pdata;

    pfifo = (struct fifo*)malloc(sizeof(struct fifo));
    if(pfifo == NULL){
        return NULL;
    }
    pdata = (TYPE*)malloc(sizeof(TYPE)*size);
    if(pdata == NULL){
        free(pfifo);
        return NULL;
    }

    pfifo->front = 0;
    pfifo->rear = 0;
    pfifo->data = pdata;
    pfifo->size = size;

    return pfifo;
}

void fifo_free(fifo_t fifo)
{
    free(fifo->data);
    free(fifo);
}

void fifo_init(fifo_t fifo, TYPE* pbuff, unsigned int size)
{
    if(fifo == NULL || pbuff == NULL)
        return;
    fifo->data = pbuff;
    fifo->front = 0;
    fifo->rear = 0;
    fifo->size = size;
}

int fifo_is_empty(fifo_t fifo)
{
    return (fifo->front == fifo->rear);
}

int fifo_is_full(fifo_t fifo)
{
    return (((fifo->rear+1) % fifo->size) == fifo->front);
}

int fifo_in(fifo_t fifo, TYPE value)
{
    if(fifo_is_full(fifo)){
        return -1;
    }

    fifo->data[fifo->rear] = value;
    fifo->rear = (fifo->rear+1) % fifo->size;

    return 0;
}

int fifo_out(fifo_t fifo, TYPE *pvalue)
{
    if(fifo_is_empty(fifo))
        return -1;

    *pvalue = fifo->data[fifo->front];
    fifo->front = (fifo->front+1) % fifo->size;

    return 0;
}

int fifo_len_get(fifo_t fifo)
{
    return ((fifo->rear - fifo->front + fifo->size) % fifo->size);
}


