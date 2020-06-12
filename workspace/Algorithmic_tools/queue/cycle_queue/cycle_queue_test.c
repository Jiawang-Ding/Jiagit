#include "cycle_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#if 1 

pthread_mutex_t queue_mutex;

void print_cube_info(struct cube *cube)
{
    printf("name  :%s\n", cube->name);
    printf("length:%d\n", cube->length);
    printf("high  :%d\n", cube->high);
    printf("width :%d\n", cube->width);
    //printf("\n");
}

struct cube *get_cube_info(time_t timer)
{
    static struct cube cube_info;
    srand(timer);
    sprintf(cube_info.name, "id %d",10000+(rand()%9999));
    cube_info.length = rand() % 100; 
    cube_info.width = rand() % 50; 
    cube_info.high = rand() % 20;
    //print_cube_info(&cube_info);
    return &cube_info;
}

void *producer_pro(void *arg)
{
    int err;
    static int cnt = 10;
    time_t cur_time;
    struct cube *pvalue;
    struct cycle_queue *pqueue = (struct cycle_queue*)arg;

    while(1)
    {
        if(0 == cnt--){
            /* end cont exit */
            pthread_exit(NULL);
        }

        time(&cur_time);
        srand(cur_time);
        int seed = rand() % 11111;
        printf("************************* in ************************\n");
        pvalue = get_cube_info(seed+cur_time);
        err = cycle_queue_in_locked(pqueue, *pvalue, &queue_mutex);
        if(err == 1){
            printf("queue is full\n");
            sleep(2);
        }else{
            print_cube_info(pvalue);
        }
        printf("queue len : %d \n", cycle_queue_len_locked(pqueue, &queue_mutex));
        printf("*********************** in end ***********************\n\n");
        sleep(1);

    }
    return (void*)pqueue;
}

void *consumer_pro(void *arg)
{
    int err;
    struct cube value;
    struct cycle_queue *pqueue = (struct cycle_queue*)arg;
    while(1)
    {
        sleep(1);
        printf("************************ out ************************\n");
        err = cycle_queue_out_locked(pqueue, &value, &queue_mutex);
        if(err == 1){
            printf("queue in empty\n");
            pthread_exit(NULL);
            //sleep(2);
        }else{
            print_cube_info(&value);
        }
        printf("queue len : %d \n", cycle_queue_len_locked(pqueue, &queue_mutex));
        printf("********************** out end **********************\n\n");
    }
    return (void*)pqueue;
}

pthread_t consume_thread(void *arg)
{
    int err;
    pthread_t tid;

    err = pthread_create(&tid, NULL, consumer_pro, arg);
    if(err){
        printf("failed to create consumer thread\n");
        return -1;
    }
    return tid;
}

pthread_t produce_thread(void *arg)
{
    int err;
    pthread_t tid;

    err = pthread_create(&tid, NULL, producer_pro, arg);
    if(err){
        printf("failed to create producer thread\n");
        return -1;
    }
    return tid;
}


int main(void)
{
    int ret;
    struct cycle_queue *pqueue=NULL;
    pthread_t consume_pid, produce_pid;

    ret = pthread_mutex_init(&queue_mutex, NULL);
    if(ret){
        printf("queue mutex init failed\n");
        return -1;
    }

    pqueue = cycle_queue_alloc(6);
    if(pqueue == NULL){
        printf("cycle_queue alloc failed\n");
        return -1;
    }

    printf("multi thread test ...\n");
    produce_pid = produce_thread((void*)pqueue);
    consume_pid = consume_thread((void*)pqueue);

    ret = pthread_join(produce_pid, NULL);
    if(ret){
        printf("produce thread join failed\n");
    }
    ret = pthread_join(consume_pid, NULL);
    if(ret){
        printf("consume thread join failed\n");
    }

    cycle_queue_free(pqueue);
    pthread_mutex_destroy(&queue_mutex);
    printf("cycle queue test end...\n");

    return 0;
}

#else

void init_type(TYPE_T *queue);
void print_type(TYPE_T *queue);

int main(void)
{
    struct cycle_queue *pqueue;
    int i,ret;
    TYPE_T value;

    
    printf("TYPE : %ld\n", sizeof(TYPE_T));

    pqueue = cycle_queue_alloc(6);
    if(pqueue == NULL){
        printf("cycle_queue alloc failed\n");
        return -1;
    }

    printf("cycle_queue length is :%d\n", cycle_queue_len(pqueue));

    for(i = 0; i < 5; i++){

        init_type(&value);
        ret = cycle_queue_in(pqueue, value);
        if(ret){
            printf("cycle_queue in failed\n");
            return -1;
        }
    }

    printf("cycle_queue length is :%d\n", cycle_queue_len(pqueue));
    printf("cycle_queue availed is :%d\n", cycle_queue_avail(pqueue));


    for(i = 0; i < 5; i++){
        ret = cycle_queue_out(pqueue, &value);
        if(ret){
            printf("cycle_queue in failed\n");
            return -1;
        }
        //printf("%d cycle_queue out is :%d\n", i, value);
        print_type(&value);
        printf("\n");
    }

    printf("cycle_queue length is :%d\n", cycle_queue_len(pqueue));
    printf("cycle_queue availed is :%d\n", cycle_queue_avail(pqueue));
    cycle_queue_free(pqueue);
    
    return 0;
}

void init_type(TYPE_T *queue)
{
    printf("please enter name:\n");
    gets(queue->name);

    printf("please enter length,high,width:\n");
    scanf("%d %d %d", &queue->length, &queue->high, &queue->width);
    while(getchar() != '\n'){;}
}

void print_type(TYPE_T *queue)
{
    printf("name  :%s\n", queue->name);
    printf("length:%d\n", queue->length);
    printf("high  :%d\n", queue->high);
    printf("width :%d\n", queue->width);
}
#endif
