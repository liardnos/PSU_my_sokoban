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

int end_game(map_s_t *map, list_t *list_z)
{
    for (int i = 0; map->win_p[i]; i++)
        map->map[map->win_p[i]] == ' ' ? map->map[map->win_p[i]] = 'O' : 0;
    print_map(map), refresh();
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
    return (2);
}

int main(int ac, char **av)
{
    if (ac != 2) return (84);
    if (av[1][0] == '-' && av[1][1] == 'h' && av[1][2] == 0) my_putstr(help);
    map_s_t *map = init_map(av[1]);
    if (map == 0) return (84);
    int p_nb = 0;
    for (int i = 0; map->map[i]; i++) map->map[i] == 'P' ? p_nb++ : 0;
    if (p_nb != 1) return (84);
    list_t *list_z = linked_list_init();
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    print_map(map);
    return (main_loop(map, list_z));
}
