/*
** EPITECH PROJECT, 2019
** my_params_to_list
** File description:
** hello
*/

#include <stdlib.h>
#include "my.h"

struct linked_list *my_params_to_list(int ac, char * const *av)
{
    if (ac < 1)
    return (NULL);
    struct linked_list *point = malloc(sizeof(struct linked_list));
    struct linked_list *point_o = point;

    point_o->data = av[0];
    for (int i = 1; i < ac; i++){
        point->next = malloc(sizeof(struct linked_list));
        point = point->next;
        point->data = av[i];
    }
    point->next = 0;
    return (point_o);
}
