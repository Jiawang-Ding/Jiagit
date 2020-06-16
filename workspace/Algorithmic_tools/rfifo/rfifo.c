/**
 * @brief 仿照linux kfifo写的rfifo
 * @author jiawang-ding  
 * @date 2020-06-16
 **/

#include <rfifo.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define is_power_of_2(x) ((x) != 0 && (((x) & ((x) - 1)) == 0))
#define min(a, b) (((a) < (b)) ? (a) : (b))

int32_t rfifo_init(struct rfifo *fifo, void *buffer, uint32_t size)
{
    if(fifo == NULL || buffer == NULL){
        return -1;
    }
    memset(fifo, 0, sizeof(struct rfifo));
    fifo->buffer = buffer;
    fifo->size = size;
    fifo->in = 0;
    fifo->out = 0;

    return 0;
}

struct rfifo* rfifo_alloc(uint32_t size)
{
    struct rfifo *fifo = NULL;
    void *buffer = NULL;

    if(!is_power_of_2(size)){
        //fprintf(stderr,"size must be power of 2.\n");
        return fifo;
    }

    fifo = (struct rfifo *)malloc(sizeof(struct rfifo));
    if (fifo == NULL){
        //fprintf(stderr,"Failed to malloc memory,errno:%u,reason:%s",errno, strerror(errno));
        return fifo;
    }

    buffer = (void*)malloc(sizeof(uint8_t)*size);
    if(buffer == NULL){
        return buffer;
    }

    rfifo_init(fifo, buffer, size);
    return fifo;
}

void rfifo_free(struct rfifo *fifo)
{
    if(fifo){
        if(fifo->buffer){
            free(fifo->buffer);
            fifo->buffer = NULL;
        }
        free(fifo);
        fifo = NULL;
    }
}

int32_t rfifo_is_empty(const rfifo_t *fifo)
{
    return (fifo->in == fifo->out);
}

int32_t rfifo_is_full(const rfifo_t *fifo)
{
    return (fifo->size == (fifo->in-fifo->out));
}

uint32_t rfifo_len(const rfifo_t *fifo)
{
    return (fifo->in - fifo->out);
}

uint32_t rfifo_size(const rfifo_t *fifo)
{
    return (fifo->size);
}

uint32_t rfifo_avail(const rfifo_t *fifo)
{
    return (fifo->size - fifo->in + fifo->out);
}

uint32_t rfifo_out(rfifo_t *fifo, void *buffer, uint32_t esize)
{
    uint32_t len = 0;
    
    esize  = min(esize, fifo->in - fifo->out);
    /* first get the data from fifo->out until the end of the buffer */
    len = min(esize, fifo->size - (fifo->out & (fifo->size - 1)));
    memcpy(buffer, fifo->buffer + (fifo->out & (fifo->size - 1)), len);
    /* then get the rest (if any) from the beginning of the buffer */
    memcpy(buffer + len, fifo->buffer, esize - len);
    fifo->out += esize;

    /* if the FIFO is empty, set the indices to 0 */    
    if (fifo->in == fifo->out)
        fifo->in = fifo->out = 0;
    
    return esize;
}

uint32_t rfifo_in(rfifo_t *fifo, void *buffer, uint32_t esize)
{
    uint32_t len = 0;

    esize = min(esize, fifo->size - fifo->in + fifo->out);
    /* first put the data starting from fifo->in to buffer end */
    len  = min(esize, fifo->size - (fifo->in & (fifo->size - 1)));
    memcpy(fifo->buffer + (fifo->in & (fifo->size - 1)), buffer, len);
    /* then put the rest (if any) at the beginning of the buffer */
    memcpy(fifo->buffer, buffer + len, esize - len);
    fifo->in += esize;

    return esize;
}


int32_t rfifo_is_empty_locked(const rfifo_t *fifo, pthread_mutex_t *plock)
{
    int32_t ret = 0;

    pthread_mutex_lock(plock);
    ret = rfifo_is_empty(fifo);
    pthread_mutex_unlock(plock);

    return ret;
}

int32_t rfifo_is_full_locked(const rfifo_t *fifo, pthread_mutex_t *plock)
{
    int32_t ret = 0;

    pthread_mutex_lock(plock);
    ret = rfifo_is_full(fifo);
    pthread_mutex_unlock(plock);

    return ret;
}

uint32_t rfifo_len_locked(const rfifo_t *fifo, pthread_mutex_t *plock)
{
    uint32_t len = 0;
    
    pthread_mutex_lock(plock);
    len = rfifo_len(fifo);
    pthread_mutex_unlock(plock);

    return len;
}

uint32_t rfifo_size_locked(const rfifo_t *fifo, pthread_mutex_t *plock)
{
    uint32_t len = 0;
    
    pthread_mutex_lock(plock);
    len = rfifo_size(fifo);
    pthread_mutex_unlock(plock);

    return len;
}
    
uint32_t rfifo_avail_locked(const rfifo_t *fifo, pthread_mutex_t *plock)
{
    uint32_t len = 0;
    
    pthread_mutex_lock(plock);
    len = rfifo_avail(fifo);
    pthread_mutex_unlock(plock);

    return len;
}

uint32_t rfifo_out_locked(rfifo_t *fifo, void *buffer, uint32_t esize, pthread_mutex_t *plock)
{
    uint32_t ret;

    pthread_mutex_lock(plock);
    ret = rfifo_out(fifo, buffer, esize);
    pthread_mutex_unlock(plock);

    return ret;
}

uint32_t rfifo_in_locked(rfifo_t *fifo, void *buffer, uint32_t esize, pthread_mutex_t *plock)
{
    uint32_t ret;

    pthread_mutex_lock(plock);
    ret = rfifo_in(fifo, buffer, esize);
    pthread_mutex_unlock(plock);

    return ret;
}
    
