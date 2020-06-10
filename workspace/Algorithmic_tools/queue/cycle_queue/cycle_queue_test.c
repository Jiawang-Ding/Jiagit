#include "cycle_queue.h"
#include <stdio.h>

void init_type(TYPE* queue);
void print_type(TYPE* queue);

int main(void)
{
    struct cycle_queue *pqueue;
    int i,ret;
    TYPE value;

    
    printf("TYPE : %ld\n", sizeof(TYPE));

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
    
    return 0;
}

void init_type(TYPE* queue)
{
    printf("please enter name:\n");
    gets(queue->name);

    printf("please enter length,high,width:\n");
    scanf("%d %d %d", &queue->length, &queue->high, &queue->width);
    while(getchar() != '\n'){;}
}

void print_type(TYPE* queue)
{
    printf("name  :%s\n", queue->name);
    printf("length:%d\n", queue->length);
    printf("high  :%d\n", queue->high);
    printf("width :%d\n", queue->width);
}
