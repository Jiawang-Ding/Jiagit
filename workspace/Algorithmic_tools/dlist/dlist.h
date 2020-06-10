#ifndef _DLIST_H
#define _DLIST_H
#include <stdio.h>

struct dlist_node{

    struct dlist_node *next;
    struct dlist_node *prev;

};
typedef struct dlist_node dlist_t;

#define dlist_for_each(pos, head) for(pos = (head)->next; pos != (head); pos = pos->next)

//链表遍历时的回调函数类型
typedef int(*dlist_node_process)(void *p_arg, dlist_t *p_node);

/* 链表初始化 */
int dlist_init(dlist_t *p_head);

/* 创建一个节点 */
dlist_t *dlist_creat_node(void);

/* 删除一个节点 */
int dlist_delete_node(dlist_t *p_node);

/* 链表后插入一个节点 */
int dlist_insert_after(dlist_t *p_pos, dlist_t *p_node);

/* 链表前插入一个节点 */
int dlist_insert_before(dlist_t *p_pos, dlist_t *p_node);

/* 从链表移除一个节点 */
int dlist_remove(dlist_t *p_node);

/* 检查一个链表是否为空 */
int dlist_isempty(const dlist_t *p_node);

/* 获取一个链表长度 */
unsigned int dlist_len(const dlist_t *p_node);

/* 获取某一节点的前一节点 */
dlist_t *dlist_prev_get(dlist_t *p_node);

/* 获取某一节点的后一节点 */
dlist_t *dlist_next_get(dlist_t *p_node);

/* 遍历链表 */
int dlist_foreach(dlist_t *p_head, dlist_node_process p_fun_process, void *p_arg);

#endif
