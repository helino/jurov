#include "stddef.h"
#include "utils.h"
#include "errors.h"
#include "list.h"

int new_list(list **l)
{
    list *tmp = j_malloc(sizeof(list));
    tmp->size = 0;
    tmp->first = NULL;
    tmp->last = NULL;
    *l = tmp;
    return JRV_SUCCESS;
}

int append(list* l, void *data)
{
    list_element *ele = j_malloc(sizeof(list_element));
    ele->data = data;
    ele->previous = l->last;
    if(0 == l->size) {
        l->first = ele;
    }
    l->last = ele;
    l->size += 1;
    return JRV_SUCCESS;
}

int free_list(list* l)
{
    list_element *current = l->last;
    list_element *tmp;

    /* free all the elements */
    while(NULL != current) {
        tmp = current->previous;
        free(current->data);
        free(current);
        current = tmp;
    }

    /* free the list itself */
    free(l);
    return JRV_SUCCESS;
}
