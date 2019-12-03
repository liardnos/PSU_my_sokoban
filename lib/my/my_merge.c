/*
** EPITECH PROJECT, 2019
** my_merge
** File description:
** hello
*/

#include <stdlib.h>
#include <stdio.h>
#include "my.h"

void my_concat_list(struct linked_list **begin, struct linked_list *begin2);
void my_sort_list(struct linked_list **begin, int (*cmp)());

void my_merge(struct linked_list **begin1, struct linked_list *begin2,
    int (*cmp)())
{
    my_concat_list(begin1, begin2);
    my_sort_list(begin1, cmp);
}
