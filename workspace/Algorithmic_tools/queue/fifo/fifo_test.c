#include "fifo.h"
#include <stdio.h>

void init_type(TYPE* fifo);
void print_type(TYPE* fifo);

int main(void)
{
    struct fifo *pfifo;
    int i,ret;
    int fifo_len;
    TYPE value;

    
    printf("TYPE : %ld\n", sizeof(TYPE));

    pfifo = fifo_alloc(6);
    if(pfifo == NULL){
        printf("fifo alloc failed\n");
        return -1;
    }

    for(i = 0; i < 5; i++){

        init_type(&value);
        ret = fifo_in(pfifo, value);
        if(ret){
            printf("fifo in failed\n");
            return -1;
        }
    }

    fifo_len = fifo_len_get(pfifo);
    printf("fifo length is :%d\n", fifo_len);


    for(i = 0; i < 5; i++){
        ret = fifo_out(pfifo, &value);
        if(ret){
            printf("fifo in failed\n");
            return -1;
        }
        //printf("%d fifo out is :%d\n", i, value);
        print_type(&value);
        printf("\n");
    }
    
    
    fifo_len = fifo_len_get(pfifo);
    printf("fifo length is :%d\n", fifo_len);

    return 0;
}

void init_type(TYPE* fifo)
{
    printf("please enter name:\n");
    gets(fifo->name);
    printf("please enter length,high,width:\n");
    scanf("%d %d %d", &fifo->length, &fifo->high, &fifo->width);

}

void print_type(TYPE* fifo)
{
    printf("name  :%s\n", fifo->name);
    printf("length:%d\n", fifo->length);
    printf("high  :%d\n", fifo->high);
    printf("width :%d\n", fifo->width);
}
