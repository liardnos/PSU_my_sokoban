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
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int my_strlen(char *);
char *my_strdup(char *);

typedef struct map_s{
    char *map;
    char *map_o;
    int height;
    int width;
    char *mov; //is pushable
    char *floor;//is an objectif
    int *win_p;
} map_s_t;

int my_find(char *str, char c)
{
    for (int i = 0; str[i]; i++)
        if (c == str[i])
            return (1);
    return (0);
}

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

map_s_t *init_map(char *filename)
{
    map_s_t *map = malloc(sizeof(map_s_t));
    struct stat file_stat;

    map->mov = "PX";
    map->floor = " O";
    map->height = 0;
    stat(filename, &file_stat);
    map->map = malloc(file_stat.st_size+1);
    int fd = open(filename, O_RDONLY);
    read(fd, map->map, file_stat.st_size);
    map->map[file_stat.st_size] = 0;
    for (int i = 0; map->map[i]; i++)
        if (map->map[i] == '\n')
            map->height++;
    map->width = file_stat.st_size/map->height;
    init_win_p(map);
    map->map_o = my_strdup(map->map);
    return (map);
}

void print_map(map_s_t *map)
{
    char c;
    for (int i = 0; i < map->height; i++){
        for (int ii = 0; ii < map->width; ii++){
            c = map->map[ii+i*map->width];
            mvprintw(i, ii, &c);
        }
    }
}

void mov_p(map_s_t *map, int ac)
{
    for (int coor = 0; map->map[coor]; coor++){
        char mo = map->map[coor];

        char md = (mo != '#' && mo != '\n' ? map->map[coor+ac] : '#');
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
    for (int coor = 0; map->map[coor]; coor++){
        map->map[coor] == 'X' ? x++ : 0;
        map->map[coor] == 'O' ? o++ : 0;
    }
    for (int coor = 0; map->map[coor]; coor++){
        if (m[coor] == 'X')
            if ((my_find(fl, m[coor+1]) || my_find(fl, m[coor-1])) && (my_find(fl, m[coor-map->width]) || my_find(fl, m[coor+map->width])))
                x--;
    }
    mvprintw(15 , 0, "%i    ", x);
    if ( x < o)
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
    map_s_t *map = init_map(av[1]);
    int ch;
    setbuf(stdout, 0);
    initscr();
	cbreak();
    noecho();
	keypad(stdscr, TRUE);
    print_map(map);

    while((ch = getch())){
        switch(ch)
        {
            case 260: //left
                mov_p(map, -1);
                break;
            case 261: //right
                mov_p(map, 1);
                break;
            case 259: //up
                mov_p(map, -map->width);
                break;
            case 258: //down
                mov_p(map, map->width);
                break;
            case 32: //down
                map->map = my_strdup(map->map_o);
                break;
        }
        print_map(map);
        refresh();
        for (int i = 0; map->win_p[i]; i++)
            map->map[map->win_p[i]] == ' ' ? map->map[map->win_p[i]] = 'O' : 0;
        int nb = 0;
        for (int coor = 0; map->map[coor]; coor++)
            map->map[coor] == 'O' ? nb++ : 0;
        if (nb == 0){
            map_free(map);
            endwin();
            return (0);
        }
        if (did_you_lose(map) == 1){
            map_free(map);
            endwin();
            return (1);
        }
    }
}

/*
invalide map -> return (84);
O = 79
X = 88
O + X = 167
P = 80
P + X = 159
# = 35
  = 32
*/
