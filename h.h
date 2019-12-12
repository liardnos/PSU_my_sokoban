/*
** EPITECH PROJECT, 2019
** h
** File description:
** Prototype all functions of libmy.a & define macros
*/

char *str_add(char *, char *, int);
void init_win_p(map_s_t *map);
int my_find(char *, char);
int push_object(map_s_t *map, int coor, int ac);
list_t *linked_list_init(void);
void linked_list_apstart(list_t *begin, void *data);
void print_map(map_s_t *map);
void *linked_list_pop(list_t *begin, int pos);
void linked_list_free_d(list_t *begin);
