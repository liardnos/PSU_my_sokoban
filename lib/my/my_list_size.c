/*
** EPITECH PROJECT, 2019
** my_list_size
** File description:
** hello
*/

#include <stdlib.h>
#include <stdio.h>
#include "my.h"

int my_list_size(struct linked_list const *list)
{
    if (list == NULL)
        return (0);
    int len = 1;

    if (list == 0)
        return (0);
    while (list->next != 0){
        len++;
        list = list->next;
    }
    return (len);
}
