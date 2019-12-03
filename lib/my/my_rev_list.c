/*
** EPITECH PROJECT, 2019
** my_rev_list
** File description:
** hello
*/

#include <stdlib.h>
#include <stdio.h>
#include "my.h"

int my_list_size(struct linked_list *);

int my_rev_list(struct linked_list **begin)
{
    struct linked_list *point = *begin;
    int len = my_list_size(point);
    if (len == 0)
        return (0);
    struct linked_list **tempo = malloc(8*len);

    tempo[0] = point;
    for (int i = 1; i < len; i++){
        point = point->next;
        tempo[i] = point;
    }

    *begin = tempo[len-1];
    for (int i = len-1; i > 0; i--){
        tempo[i]->next = tempo[i-1];
    }
    tempo[0]->next = 0;
    return (1);
}
