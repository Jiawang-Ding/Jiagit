#include "page.h"
#include <stdlib.h>

/* 创建一个节点 */
struct page_info *page_creat(dlist_t *list_head, unsigned int number,
                             unsigned char *entry)
{
    struct page_info *p_page;

    p_page = (struct page_info*)malloc(sizeof(struct page_info));
    if(p_page == NULL){
        return NULL;
    }

    dlist_insert_before(list_head, &p_page->list);
    p_page->page_num = number;
    p_page->disp_entry = entry;

    return p_page;

}

/* 删除一个节点 */
int page_delete(page_t p_page)
{
    if(p_page == NULL){
        return -1;
    }
    dlist_remove(&p_page->list);
    free(p_page);
    return 0;
}

/* 删除所有节点 */
int page_delete_all(page_t head)
{
    int ret;
    struct dlist_node *p_tmp = head->list.next;
    struct dlist_node *p_end = &head->list;

    struct page_info *p_del;

    while(p_tmp != p_end){

        p_del = (struct page_info*)p_tmp;
        p_tmp = dlist_next_get(p_tmp);

        ret = page_delete(p_del);
        if(ret)        
            break;
    }
    return 0;
}

unsigned int page_maxnum_get(page_t head)
{

    return dlist_len(&head->list);
    
}

page_t page_next_get(page_t cur)
{
    page_t next = NULL;

    next = (struct page_info*)dlist_next_get(&cur->list);
    if(next == NULL){
        return NULL;
    }

    return next;
}

page_t page_prev_get(page_t cur)
{
    page_t prev = NULL;

    prev = (struct page_info*)dlist_prev_get(&cur->list);
    if(prev == NULL){
        return NULL;
    }

    return prev;
}


page_t page_number_find(page_t head , unsigned int number)
{
    struct dlist_node *p_tmp = head->list.next;
    struct dlist_node *p_end = &head->list;
    struct page_info *page;

    while(p_tmp != p_end){
        page = (struct page_info*)p_tmp;
        if(page->page_num == number){
            return page;
        }
        p_tmp = p_tmp->next;
    }
    return NULL;
}
