/*
** EPITECH PROJECT, 2019
** mainnn
** File description:
** my_socoban
*/

#include <stdlib.h>
#include <string.h>
#include "include/my.h"
#include "h.h"
#include <ncurses.h>

int my_strlen(char *);

int push_object(map_s_t *map, int coor, int ac)
{
    int coor_o = coor;
    if (my_find(map->mov, map->map[coor+ac])){
        if (my_find(map->floor, map->map[coor+ac*2])){
            map->map[coor+ac*2] = map->map[coor+ac];
            map->map[coor+ac] = 'Q';
            map->map[coor] = ' ';
        }
    }
}

void init_win_p(map_s_t *map)
{
    int nb = 0;
    for (int coor = 0; map->map[coor]; coor++)
        map->map[coor] == 'O' ? nb++ : 0;
    map->win_p = malloc((nb+1) * sizeof(int));
    memset(map->win_p, 0, (nb+1) * sizeof(int));
    nb = 0;
    for (int coor = 0; map->map[coor]; coor++)
        map->map[coor] == 'O' ? map->win_p[nb] = coor, nb++ : 0;
}

char *str_add(char *str1, char *str2, int pos)
{
    char *str3 = malloc(my_strlen(str1)+my_strlen(str2)+1);
    str3[my_strlen(str1)+my_strlen(str2)] = 0;
    int str1_p = 0;
    int str2_p = 0;
    for (;str1_p < pos; str3[str1_p] = str1[str1_p], str1_p++);
    for (;str2[str2_p]; str3[str1_p+str2_p] = str2[str2_p], str2_p++);
    for (;str1[str1_p]; str3[str1_p+str2_p] = str1[str1_p], str1_p++);
    return (str3);
}

void print_map(map_s_t *map)
{
    mvprintw(0, 0, map->map);
}

/*
int push_object(map_s_t *map, int coor, int ac)
{
    int coor_o = coor;
    for (; my_find(map->mov, map->map[coor]); coor += ac)
        if (map->map[coor] == 'P')
            map->map[coor] = 'Q';
    if (!my_find(map->floor, map->map[coor]))
        return (0);
    for (; coor != coor_o; coor -= ac){
        map->map[coor] = map->map[coor-ac];
    }
    map->map[coor+ac] = 'Q';
    map->map[coor] = ' ';
}
*/
