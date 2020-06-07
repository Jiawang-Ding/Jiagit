#ifndef _PAGE_H
#define _PAGE_H
#include "dlist.h"
struct page_info{
    struct dlist_node list;
    unsigned int page_num;
    unsigned char *disp_entry;
};

typedef struct page_info *page_t;



struct page_info *page_creat(dlist_t *list_head, unsigned int number, unsigned char *entry);

int page_delete(page_t p_page);

int page_delete_all(page_t head);

int page_intert_list(page_t head, page_t page);

page_t page_next_get(page_t cur);

page_t page_prev_get(page_t cur);

page_t page_number_find(page_t head, unsigned int number);

unsigned int page_maxnum_get(page_t head);

#endif
