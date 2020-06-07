#include "page.h"
#include "dlist.h"
#include <stdio.h>
#include <stdlib.h>

struct dlist_node list_page;

int int_node_process(void *p_arg, dlist_t *p_node)
{
    struct page_info *p_inode = (struct page_info*)p_node;
    printf("node value:%d, 0x%x\n",p_inode->page_num, p_inode->disp_entry);
    return 0;
}
int main(void)
{
    int ret,i;
    struct page_info *p_tmp = NULL;
    
    struct page_info *p_del = NULL;

    dlist_init(&list_page);

    for(i=0; i<10; i++){
        p_tmp = page_creat(&list_page, i, (unsigned char*)p_tmp);
        if(p_tmp == NULL){
            printf("page_info creat node failed\n");
            return -1;
        }

        if(i==3){
            p_del = p_tmp;
        }
    }

    printf("page max number: %d\n", page_maxnum_get(p_tmp));
    

    /*list for each test*/
    dlist_t *tmp;
    dlist_for_each(tmp, &list_page)
    {
        page_t page = (page_t)tmp;
        printf("page_nums:%d page_entry:%x\n", 
                page->page_num, page->disp_entry);
    }

    
    /* list jump test */
    p_tmp = page_next_get(p_del);
    printf("prev :%d\n",p_tmp->page_num);
    p_tmp = page_prev_get(p_del);
    printf("next :%d\n",p_tmp->page_num);


    /* list node find test */
    p_tmp = page_number_find((page_t)&list_page, 6);
    if(p_tmp)
    printf("find : id:%d,%x\n",p_tmp->page_num, p_tmp->disp_entry);


    /* list node delete test */
    printf("delete a page_info node!\n");
    ret = page_delete(p_del);
    if(ret){
        printf("delete a page_info node filed!\n");
        return -1;
    }


    /* list foreach test */
    printf("delete a page_info node!\n");
    ret = dlist_foreach(&list_page, int_node_process , NULL);
    if(ret){
        printf("dlist for each error!\n");
        return -1;
    }


    /* list delete test */
    printf("start free page_info node!\n");
    page_delete_all((page_t)&list_page);
    printf("end free page_info node!\n");
    
    return 0;
}
