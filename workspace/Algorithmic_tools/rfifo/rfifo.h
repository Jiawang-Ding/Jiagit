#ifndef _RFIFO_H
#define _RFIFO_H
#include <pthread.h>

/**
  * data types are redefined for program portability 
  */
typedef unsigned char         uint8_t;
//typedef char                  int8_t;
typedef unsigned short int    uint16_t;
typedef short int             int16_t;
typedef unsigned int          uint32_t;
typedef int                   int32_t;

struct rfifo
{
    void         *buffer;   
    uint32_t     size;       
    uint32_t     in;        
    uint32_t     out;      
};

typedef struct rfifo rfifo_t;

/**                                                                                     
 * This function will statically initialize a fifo 
 * @fifo address of the fifo to be used
 * @buffer fifo buffer pointer
 * @size  number of fifo buffer 
 * @return true non-zero, false zero 
 */
int32_t rfifo_init(struct rfifo *fifo, void *buffer, uint32_t size);

/**                                                                             
 * This function will dynamically creat a fifo 
 * @size  number of fifo buffer 
 * @return address of the fifo to be used
 */
struct rfifo* rfifo_alloc(uint32_t size);

/**                                                                                             
 * This function will release fifo memory
 * @fifo address of the fifo to be used
 */
void rfifo_free(struct rfifo *fifo);

/**                                                                                             
 * returns true if the fifo is empty
 * @fifo address of the fifo to be used
 */
int32_t rfifo_is_empty(const rfifo_t *fifo);

/**                                                                                             
 * returns true if the fifo is full 
 * @fifo address of the fifo to be used
 */
int32_t rfifo_is_full(const rfifo_t *fifo);

/**                                                                                             
 * returns the number of used elements in the fifo
 * @fifo address of the fifo to be used
 */
uint32_t rfifo_len(const rfifo_t *fifo);

/**                                                                                         
 * returns the size of the fifo
 * @fifo address of the fifo to be used
 */
uint32_t rfifo_size(const rfifo_t *fifo);

/**                                                                                     
 * returns the number of unused elements in the fifo
 * @fifo address of the fifo to be used
 */
uint32_t rfifo_avail(const rfifo_t *fifo);

/**                                                                                         
 * get element from the fifo 
 * @fifo address of the fifo to be used
 * @buffer out fifo buffer address
 * @return the actual byte size 
 */
uint32_t rfifo_out(rfifo_t *fifo, void *buffer, uint32_t esize);

/**                                                                                         
 * put element into the fifo 
 * @fifo address of the fifo to be used
 * @buffer in fifo buffer address 
 * @return the actual byte size 
 */
uint32_t rfifo_in(rfifo_t *fifo, void *buffer, uint32_t esize);

/**                                                                                             
 * returns true if the fifo is empty
 * @fifo address of the fifo to be used
 * @plock fifo thread mutex lock pointer
 *
 */
int32_t rfifo_is_empty_locked(const rfifo_t *fifo, pthread_mutex_t *plock);

/**                                                                                             
 * returns true if the fifo is full 
 * @fifo address of the fifo to be used
 * @plock fifo thread mutex lock pointer
 */
int32_t rfifo_is_full_locked(const rfifo_t *fifo, pthread_mutex_t *plock);

/**                                                                                             
 * returns the number of used elements in the fifo safely
 * @fifo address of the fifo to be used
 * @plock fifo thread mutex lock pointer
 */
uint32_t rfifo_len_locked(const rfifo_t *fifo, pthread_mutex_t *plock);

/**                                                                                         
 * returns the size of the fifo safely
 * @fifo address of the fifo to be used
 * @plock fifo thread mutex lock pointer
 */
uint32_t rfifo_size_locked(const rfifo_t *fifo, pthread_mutex_t *plock);

/**                                                                                     
 * returns the number of unused elements in the fifo safely
 * @fifo address of the fifo to be used
 * @plock fifo thread mutex lock pointer
 */
uint32_t rfifo_avail_locked(const rfifo_t *fifo, pthread_mutex_t *plock);

/**                                                                                         
 * get element from the fifo safely
 * @fifo address of the fifo to be used
 * @buffer out fifo buffer address
 * @plock fifo thread mutex lock pointer
 * @return the actual byte size 
 */
uint32_t rfifo_out_locked(rfifo_t *fifo, void *buffer, uint32_t esize, pthread_mutex_t *plock);

/**                                                                                         
 * put element into the fifo safely
 * @fifo address of the fifo to be used
 * @buffer in fifo buffer address 
 * @plock fifo thread mutex lock pointer
 * @return the actual byte size 
 */
uint32_t rfifo_in_locked(rfifo_t *fifo, void *buffer, uint32_t esize, pthread_mutex_t *plock);

#endif
