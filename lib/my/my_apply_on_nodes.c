/*
** EPITECH PROJECT, 2019
** my_apply_on_nodes
** File description:
** hello
*/

#include <stdlib.h>
#include <stdio.h>
#include "my.h"

int my_list_size(struct linked_list *);

int my_apply_on_nodes(struct linked_list *begin, int (*f)(void *))
{
    int len = my_list_size(begin);

    for (int i = 0; i < len; i++){
        (*f)(begin->data);
        begin = begin->next;
    }
    return (1);
}
