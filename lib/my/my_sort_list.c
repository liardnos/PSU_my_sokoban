/*
** EPITECH PROJECT, 2019
** my_sort_list
** File description:
** hello
*/

#include <stdlib.h>
#include <stdio.h>
#include "my.h"

int my_list_size(struct linked_list *);

int my_sort_list(struct linked_list **begin, int (*cmp)())
{
    if (*begin = NULL) return (0);
    int len = my_list_size(*begin);
    struct linked_list *last;
    int mv = 1;

    while (mv > 0){
        struct linked_list *point = *begin;
        mv = 0;
        for (int i = 0; i < len-1; i++){
            last = point;
            point = point->next;
            if ((*cmp)(last->data, point->data) < 0){
                void *temp = last->data;
                last->data = point->data;
                point->data = temp;
                mv++;
            }
        }
    }
    return (1);
}
