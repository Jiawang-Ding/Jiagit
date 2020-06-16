#include "rfifo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

//uint8_t buffer[128];

struct cube{
    char name[18];
    int length;
    int high;
    int width; 
};

#if 1 

static int cnt = 10;
pthread_mutex_t rfifo_mutex;

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

void *producer_pro1(void *arg)
{
    int ret;
    time_t cur_time;
    struct cube *pvalue;
    struct rfifo *pfifo = (struct rfifo*)arg;

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

        ret = rfifo_in_locked(pfifo, (void*)pvalue, sizeof(struct cube), &rfifo_mutex);
        if(ret != sizeof(struct cube)){
            printf("rfifo is full\n");
            sleep(2);
        }else{
            print_cube_info(pvalue);
        }
        printf("rfifo len : %d \n", rfifo_len_locked(pfifo, &rfifo_mutex));
        printf("*********************** in end ***********************\n\n");
        sleep(1);

    }
    return (void*)pfifo;
}

void *producer_pro2(void *arg)
{
    int ret;
    time_t cur_time;
    struct cube *pvalue;
    struct rfifo *pfifo = (struct rfifo*)arg;

    while(1)
    {

        if(0 == cnt){
            /* end cont exit */
            pthread_exit(NULL);
        }

        time(&cur_time);
        srand(cur_time);
        int seed = rand() % 10;
        printf("************************* in-2 ************************\n");
        pvalue = get_cube_info(seed+cur_time);

        ret = rfifo_in_locked(pfifo, (void*)pvalue, sizeof(struct cube), &rfifo_mutex);
        if(ret != sizeof(struct cube)){
            printf("rfifo is full 2222\n");
            sleep(2);
        }else{
            print_cube_info(pvalue);
        }
        printf("rfifo len : %d \n", rfifo_len_locked(pfifo, &rfifo_mutex));
        printf("*********************** in-2 end ***********************\n\n");
        sleep(1);

    }
    return (void*)pfifo;
}
void *consumer_pro(void *arg)
{
    int ret;
    struct cube value;
    struct rfifo *pfifo = (struct rfifo*)arg;
    while(1)
    {
        sleep(1);
        printf("************************ out ************************\n");
        ret = rfifo_out_locked(pfifo, (void*)&value, sizeof(struct cube), &rfifo_mutex);
        if(ret != sizeof(struct cube)){
            printf("rfifo is empty\n");
            pthread_exit(NULL);
            sleep(2);
        }else{
            print_cube_info(&value);
        }
        printf("rfifo len : %d \n", rfifo_len_locked(pfifo, &rfifo_mutex));
        printf("********************** out end **********************\n\n");
    }
    return (void*)pfifo;
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

pthread_t produce_thread1(void *arg)
{
    int err;
    pthread_t tid;

    err = pthread_create(&tid, NULL, producer_pro1, arg);
    if(err){
        printf("failed to create producer thread\n");
        return -1;
    }
    return tid;
}

pthread_t produce_thread2(void *arg)
{
    int err;
    pthread_t tid;

    err = pthread_create(&tid, NULL, producer_pro2, arg);
    if(err){
        printf("failed to create producer thread\n");
        return -1;
    }
    return tid;
}

int main(void)
{
    int ret;
    struct rfifo *pfifo;
    pthread_t consume_pid, produce_pid1, produce_pid2;

    printf("TYPE : %ld\n", sizeof(struct cube));

    ret = pthread_mutex_init(&rfifo_mutex, NULL);
    if(ret){
        printf("rfifo mutex init failed\n");
        return -1;
    }

    pfifo = rfifo_alloc(8*sizeof(struct cube));
    if(pfifo == NULL){
        printf("rfifo alloc failed\n");
        return -1;
    }

    printf("multi thread test ...\n");
    produce_pid1 = produce_thread1((void*)pfifo);
    produce_pid2 = produce_thread2((void*)pfifo);
    consume_pid = consume_thread((void*)pfifo);

    ret = pthread_join(produce_pid1, NULL);
    if(ret){
        printf("produce thread join failed\n");
    }
    ret = pthread_join(produce_pid2, NULL);
    if(ret){
        printf("produce thread join failed\n");
    }
    ret = pthread_join(consume_pid, NULL);
    if(ret){
        printf("consume thread join failed\n");
    }

    rfifo_free(pfifo);
    pthread_mutex_destroy(&rfifo_mutex);
    printf("rfifo test end...\n");

    return 0;
}

#else

void init_type(struct cube *rfifo);
void print_type(struct cube *rfifo);

int main(void)
{
    struct rfifo *pfifo;
    int i,ret;
    struct cube value;

    
    printf("TYPE : %ld\n", sizeof(struct cube));

    pfifo = rfifo_alloc(128);
    if(pfifo == NULL){
        printf("rfifo alloc failed\n");
        return -1;
    }

    printf("rfifo length is :%d\n", rfifo_len(pfifo));

    for(i = 0; i < 5; i++){

        init_type(&value);
        ret = rfifo_in(pfifo, (void*)&value, sizeof(struct cube));
        if(ret != sizeof(struct cube)){
            printf("rfifo is full,wsize:%d\n", ret);
            return -1;
        }
    }

    printf("rfifo length is :%d\n", rfifo_len(pfifo));
    printf("rfifo availed is :%d\n", rfifo_avail(pfifo));


    for(i = 0; i < 5; i++){
        ret = rfifo_out(pfifo, (void*)&value, sizeof(struct cube));
        if(ret != sizeof(struct cube)){
            printf("rfifo in empty,rszie:%d\n", ret);
            return -1;
        }
        //printf("%d rfifo out is :%d\n", i, value);
        print_type(&value);
        printf("\n");
    }

    printf("rfifo length is :%d\n", rfifo_len(pfifo));
    printf("rfifo availed is :%d\n", rfifo_avail(pfifo));
    rfifo_free(pfifo);
    
    return 0;
}

void init_type(struct cube *rfifo)
{
    printf("please enter name:\n");
    gets(rfifo->name);

    printf("please enter length,high,width:\n");
    scanf("%d %d %d", &rfifo->length, &rfifo->high, &rfifo->width);
    while(getchar() != '\n'){;}
}

void print_type(struct cube *rfifo)
{
    printf("name  :%s\n", rfifo->name);
    printf("length:%d\n", rfifo->length);
    printf("high  :%d\n", rfifo->high);
    printf("width :%d\n", rfifo->width);
}
#endif
