#include <dlist.h>
#include <stdio.h>
#include <stdlib.h>

/* 链表初始化 */
int dlist_init(struct dlist_node* p_head)
{
    if(p_head == NULL){
        return -1;
    }
    p_head->next = p_head;
    p_head->prev = p_head;

    return 0;
}

/* 创建一个节点 */
dlist_t *dlist_creat_node(void)
{
    struct dlist_node *p_node;

    p_node = (struct dlist_node*)malloc(sizeof(struct dlist_node));
    if(p_node == NULL){
        return NULL;
    }

    p_node->next = NULL;
    p_node->prev = NULL;

    return p_node;
}

/* 删除一个节点 */
int dlist_delete_node(dlist_t *p_node)
{
    if(p_node == NULL){
        return -1;
    }
    p_node->prev->next = p_node->next;
    p_node->next->prev = p_node->prev;

    p_node->next = p_node;
    p_node->prev = p_node;

    free(p_node);
    return 0;
}


/* 链表后插入一个节点 */
int dlist_insert_after(dlist_t *p_pos, dlist_t *p_node)
{
    if(p_pos == NULL || p_node == NULL){
        return -1;
    }

    p_node->prev = p_pos;
    p_node->next = p_pos->next;
    p_pos->next->prev = p_node;
    p_pos->next = p_node;

    return 0;
}

/* 链表前插入一个节点 */
int dlist_insert_before(dlist_t *p_pos, dlist_t *p_node)
{
    if(p_pos == NULL || p_node == NULL){
        return -1;
    }

    p_node->prev = p_pos->prev;
    p_node->next = p_pos;
    p_pos->prev->next = p_node;
    p_pos->prev = p_node;

    return 0;
}

/* 从链表移除一个节点 */
int dlist_remove(dlist_t *p_node)
{
    if(p_node == NULL){
        return -1;
    }

    p_node->prev->next = p_node->next;
    p_node->next->prev = p_node->prev;

    p_node->next = p_node;
    p_node->prev = p_node;

    return 0;
}

/* 检查一个链表是否为空 */
int dlist_isempty(const dlist_t *p_node)
{
    if(p_node == NULL){
        return -1;
    }
    //if(p_node->next == p_node)
    //    return 0;
    //else
    //    return -1;
    return p_node->next == p_node;
}

/* 获取一个链表长度 */
unsigned int dlist_len(const dlist_t *p_node)
{
    unsigned int len = 0;
    dlist_t *p_tmp = p_node->next;

    if(p_node == NULL){
        return -1;
    }

    while(p_tmp != p_node){
        p_tmp = p_tmp->next;
        len++;
    }
    return len;
}

/* 获取某一节点的前一节点 */
dlist_t *dlist_prev_get(dlist_t *p_node)
{
    if(p_node == NULL){
        return NULL;
    }

    return p_node->prev;
}

/* 获取某一节点的后一节点 */
dlist_t *dlist_next_get(dlist_t *p_node)
{
    if(p_node == NULL){
        return NULL;
    }

    return p_node->next;
}



/* 遍历链表 */
int dlist_foreach(dlist_t *p_head, dlist_node_process p_fun_process, void *p_arg)
{

    struct dlist_node *p_tmp = p_head->next;
    int ret;

    if(p_head == NULL || p_fun_process == NULL){
        return -1;
    }

    while(p_tmp != p_head){

        ret = p_fun_process(p_arg, p_tmp);
        if(ret < 0){
            return ret;
        }
        p_tmp = p_tmp->next; 
    }
    return 0;
}


