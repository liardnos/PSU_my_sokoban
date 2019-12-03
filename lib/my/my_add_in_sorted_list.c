/*
** EPITECH PROJECT, 2019
** my_add_in_sorted_list
** File description:
** hello
*/

#include <stdlib.h>
#include <stdio.h>
#include "my.h"

int my_add_in_sorted_list_2(struct linked_list *point,
    struct linked_list *insert, int (*cmp)())
{
    struct linked_list *last;
    int insert_n = 0;
    for (int i = 0; point->next != 0 && insert_n == 0; i++){
        last = point;
        point = point->next;
        if ((*cmp)(point->data, insert->data) < 0){
            last->next = insert;
            insert->next = point;
            insert_n++;
        }
    }
    return (insert_n);
}

void my_add_in_sorted_list(struct linked_list **begin, void *data, int (*cmp)())
{
    struct linked_list *point = *begin;
    struct linked_list *start = *begin;
    struct linked_list *last;
    struct linked_list *insert = malloc(sizeof(struct linked_list));
    int insert_n = 0;

    insert->data = data;
    if ((*cmp)(point->data, insert->data) < 0){
        start = insert;
        insert->next = point;
    }
    insert_n = my_add_in_sorted_list_2(point, insert, cmp);
    if (insert_n == 0){
        point->next = insert;
        insert->next = 0;
    }
}
