/*
** EPITECH PROJECT, 2019
** mainn
** File description:
** my_socoban
*/

#include <stdlib.h>
#include "include/my.h"
#include "h.h"

list_t *linked_list_init(void)
{
    list_t *list = malloc(sizeof(list_t));
    list->data = 0;
    list->next = 0;
    return (list);
}

void linked_list_free_d(list_t *begin)
{
    list_t *last = begin;
    for (begin = begin->next; begin; begin = begin->next){
        free(last);
        last = begin;
    }
    free(last);
}

void *linked_list_pop(list_t *begin, int pos)
{
    begin->data--;
    list_t *del = begin;
    list_t *last = begin;
    void *data;

    for (int i = 0; i < pos; i++, last = last->next);
    del = last->next;
    data = del->data;
    last->next = del->next;
    free(del);
    return (data);
}

void linked_list_apstart(list_t *begin, void *data)
{
    begin->data++;
    list_t *new = malloc(sizeof(list_t));
    new->data = data;
    new->next = begin->next;
    begin->next = new;
}

int my_find(char *str, char c)
{
    for (int i = 0; str[i]; i++)
        if (c == str[i])
            return (1);
    return (0);
}
