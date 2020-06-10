#include "cycle_queue.h"
#include <stdio.h>

void init_type(TYPE* cycle_queue);
void print_type(TYPE* cycle_queue);

int main(void)
{
    struct cycle_queue *pcycle_queue;
    int i,ret;
    int cycle_queue_len;
    TYPE value;

    
    printf("TYPE : %ld\n", sizeof(TYPE));

    pcycle_queue = cycle_queue_alloc(6);
    if(pcycle_queue == NULL){
        printf("cycle_queue alloc failed\n");
        return -1;
    }

    for(i = 0; i < 5; i++){

        init_type(&value);
        ret = cycle_queue_in(pcycle_queue, value);
        if(ret){
            printf("cycle_queue in failed\n");
            return -1;
        }
    }

    cycle_queue_len = cycle_queue_len_get(pcycle_queue);
    printf("cycle_queue length is :%d\n", cycle_queue_len);


    for(i = 0; i < 5; i++){
        ret = cycle_queue_out(pcycle_queue, &value);
        if(ret){
            printf("cycle_queue in failed\n");
            return -1;
        }
        //printf("%d cycle_queue out is :%d\n", i, value);
        print_type(&value);
        printf("\n");
    }
    
    
    cycle_queue_len = cycle_queue_len_get(pcycle_queue);
    printf("cycle_queue length is :%d\n", cycle_queue_len);

    return 0;
}

void init_type(TYPE* cycle_queue)
{
    printf("please enter name:\n");
    gets(cycle_queue->name);

    printf("please enter length,high,width:\n");
    scanf("%d %d %d", &cycle_queue->length, &cycle_queue->high, &cycle_queue->width);
    while(getchar() != '\n'){;}
}

void print_type(TYPE* cycle_queue)
{
    printf("name  :%s\n", cycle_queue->name);
    printf("length:%d\n", cycle_queue->length);
    printf("high  :%d\n", cycle_queue->high);
    printf("width :%d\n", cycle_queue->width);
}
