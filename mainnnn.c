/*
** EPITECH PROJECT, 2019
** mainnnn
** File description:
** my_socoban
*/

#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "include/my.h"
#include "h.h"
#include <ncurses.h>
#include <sys/stat.h>
#include <unistd.h>

int main_loop(map_s_t *map, list_t *list_z)
{
    int ch;
    while ((ch = getch())){
        if (ch != 122)
            linked_list_apstart(list_z, my_strdup(map->map));
        ch == 260 ? mov_p(map, -1) : 0;
        ch == 261 ? mov_p(map, 1) : 0;
        ch == 259 ? mov_p(map, -map->width) : 0;
        ch == 258 ? mov_p(map, map->width) : 0;
        ch == 32 ? map->map = my_strdup(map->map_o) : 0;
        if (ch == 122 && list_z->data > (void *)0){
            free(map->map);
            map->map = linked_list_pop(list_z, 0);
        }
        int a = end_game(map, list_z);
        if (a != 2) return (a);
    }
}

map_s_t *init_map(char *filename)
{
    map_s_t *map = malloc(sizeof(map_s_t));
    struct stat file_stat;

    map->mov = "PX";
    map->floor = " O";
    map->height = 0;
    stat(filename, &file_stat);
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (0);
    map->map = malloc(file_stat.st_size+1);
    memset(map->map, 0, file_stat.st_size+1);
    read(fd, map->map, file_stat.st_size);
    map->map[file_stat.st_size] = 0;
    for (int i = 0; map->map[i]; i++)
        if (map->map[i] == '\n')
            map->height++;
    int max_len = 0;
    int len = 0;
    for (int i = 0; map->map[i]; i++, len++){
        map->map[i] == '\n' ? len = 0 : 0;
        max_len < len ? max_len = len :  0;
    }
    max_len++;
    map->width = max_len;
    for (int i = 0; map->map[i]; i++, len++){
        if (map->map[i] == '\n' && len < max_len){
            char *tempo = str_add(map->map, " ", i);
            free(map->map);
            map->map = tempo;
        } else if (map->map[i] == '\n'){
            len = 0;
        }
    }
    init_win_p(map);
    map->map_o = my_strdup(map->map);
    int o_nb = 0;
    int x_nb = 0;
    for (int i = 0; map->map[i]; i++){
        map->map[i] == 'O' ? o_nb++ : 0;
        map->map[i] == 'X' ? x_nb++ : 0;
        if (!my_find("XO #P\n", map->map[i])) return (0);
    }
    if (o_nb == 0) return (0);
    if (o_nb != x_nb) return (0);
    return (map);
}
