/*
** EPITECH PROJECT, 2019
** main
** File description:
** my_socoban
*/

#include <ncurses.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "include/my.h"
#include "h.h"
#include "h.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int my_strlen(char *);
char *my_strdup(char *);
void my_putstr(const char *);

const char *help =
"USAGE\n"
"   ./my_sokoban map\n"
"DESCRIPTION\n"
"   map  file representing the warehouse map, containing ‘#’ for walls, "
"‘P’ for the player, ‘X’ for boxes and ‘O’ for storage locations.\n";

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

void mov_p(map_s_t *map, int ac)
{
    for (int coor = 0; map->map[coor]; coor++){
        char mo = map->map[coor];

        char md = (mo != 35 && mo != '\n' && mo != 32 ? map->map[coor+ac] : 35);
        if (mo == ' ' || mo == '#'){

        } else if (mo == 'P' && my_find(map->floor, md)){
            map->map[coor] = ' ';
            map->map[coor+ac] = 'Q';
        } else if (mo == 'P' && my_find(map->mov, md)){
            push_object(map, coor, ac);
        }
    }
    for (int coor = 0; coor < map->height*map->width; coor++)
        map->map[coor] == 'Q' ? map->map[coor] = 'P' : 0;
}

int did_you_lose(map_s_t *map)
{
    char *fl = "#";
    char *m = map->map;
    int x = 0;
    int o = 0;
    for (int i = 0; map->win_p[i]; i++)
        o++;

    for (int coor = 0; map->map[coor]; coor++)
        map->map[coor] == 'X' ? x++ : 0;

    for (int coor = 0; map->map[coor]; coor++){
        if (m[coor] == 'X')
            if ((my_find(fl, m[coor+1]) || my_find(fl, m[coor-1])) && (my_find(
                fl, m[coor-map->width]) || my_find(fl, m[coor+map->width])))
                x--;
    }
    if ( x == 0)
        return (1);
    return (0);
}

void map_free(map_s_t *map)
{
    free(map->map);
    free(map->map_o);
    free(map->win_p);
    free(map);
}

int main(int ac, char **av)
{
    if (ac != 2)
        return (84);
    if (av[1][0] == '-' && av[1][1] == 'h' && av[1][2] == 0){
        my_putstr(help);
    }
    map_s_t *map = init_map(av[1]);
    if (map == 0)
        return (84);
    int p_nb = 0;
    for (int i = 0; map->map[i]; i++){
        map->map[i] == 'P' ? p_nb++ : 0;
    }
    if (p_nb != 1) return (84);
    list_t *list_z = linked_list_init();
    if (map == 0)
        return (84);
    int ch;
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    print_map(map);
    while ((ch = getch())){
        if (ch != 122)
            linked_list_apstart(list_z, my_strdup(map->map));

        switch(ch)
        {
            case 260:
                mov_p(map, -1);
                break;
            case 261:
                mov_p(map, 1);
                break;
            case 259:
                mov_p(map, -map->width);
                break;
            case 258:
                mov_p(map, map->width);
                break;
            case 32:
                map->map = my_strdup(map->map_o);
                break;
            case 122:
                if (list_z->data > (void *)0){
                    free(map->map);
                    map->map = linked_list_pop(list_z, 0);
                }
                break;
        }
        for (int i = 0; map->win_p[i]; i++)
            map->map[map->win_p[i]] == ' ' ? map->map[map->win_p[i]] = 'O' : 0;
        print_map(map);
        refresh();
        int o = 0;
        for (int i = 0; map->win_p[i]; i++)
            if (map->map[map->win_p[i]] == 79 || map->map[map->win_p[i]] == 'P')
                o++;
        if (o == 0){
            linked_list_free_d(list_z);
            map_free(map);
            endwin();

            return (0);
        }
        if (did_you_lose(map) == 1){
            map_free(map);
            linked_list_free_d(list_z);
            endwin();
            return (1);
        }
    }
}
