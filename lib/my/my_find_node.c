/*
** EPITECH PROJECT, 2019
** my_find_node
** File description:
** hello
*/

#include <stdlib.h>
#include <stdio.h>
#include "my.h"

int my_list_size(struct linked_list const *list);

struct linked_list *my_find_node(struct linked_list *begin,
    void const *data_ref, int (*cmp)())
{
    int len = my_list_size(begin);
    if (len == 0)
        return (0);
    for (int i = 0; i < len; i++){
        if ((*cmp)(begin->data, data_ref) == 0)
            return (begin);
        begin = begin->next;
    }
    return (0);
}
