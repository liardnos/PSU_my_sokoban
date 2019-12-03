/*
** EPITECH PROJECT, 2019
** my_concat_list
** File description:
** hello
*/

#include <stdlib.h>
#include <stdio.h>
#include "my.h"

int my_list_size(struct linked_list const *list);

int my_concat_list(struct linked_list **begin, struct linked_list *begin2)
{
    if (my_list_size(*begin) == 0)
        *begin = begin2;
    if (my_list_size(begin2) == 0)
        return (0);
    struct linked_list *begin1 = *begin;
    for (int i = 0; begin1->next != 0; i++){
        begin1 = begin1->next;
    }
    begin1->next = begin2;
    return (1);
}
