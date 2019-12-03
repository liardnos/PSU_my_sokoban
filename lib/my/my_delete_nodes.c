/*
** EPITECH PROJECT, 2019
** my_delete_nodes
** File description:
** hello
*/

#include <stdlib.h>
#include <stdio.h>
#include "my.h"

int my_list_size(struct linked_list const *list);

int my_delete_nodes(struct linked_list *begin, void const *data_ref,
    int (*cmp)())
{
    int len = my_list_size(begin);
    if (len == 0)
        return (0);
    struct linked_list *last;
    struct linked_list *to_free;

    for (int i = 0; i < len; i++){
        if ((*cmp)(begin->data, data_ref) == 0){
            last->next = begin->next;
            to_free = begin;
            begin = begin->next;
            free(to_free);
        } else {
        last = begin;
        begin = begin->next;
    }
    }
    return (1);
}
