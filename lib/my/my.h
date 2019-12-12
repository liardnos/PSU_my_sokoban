/*
** EPITECH PROJECT, 2019
** my
** File description:
** Prototype all functions of libmy.a & define macros
*/

#ifdef _my_h_
#define _my_h_

void my_putchar(char c);
int my_isneg(int nb);
int my_put_nbr(int nb);
void my_swap(int *a, int *b);
int my_putstr(char const *str);
int my_strlen(char const *str);
int my_getnbr(char const *str);
void my_sort_int_array(int *tab, int size);
int my_compute_power_rec(int nb, int power);
int my_compute_square_root(int nb);
int my_is_prime(int nb);
int my_find_prime_sup(int nb);
char *my_strcpy(char *dest, char const *src);
char *my_strncpy(char *dest, char const *src);
char my_revstr(char *str);
char *my_strstr(char *str, char const *to_find);
int my_strcmp(char const *s1, char const *s2);
int my_strncmp(char const *s1, char const *s2, int n);
char *my_strupcase(char *str);
char *my_strlowcase(char *str);
char *my_strcapitalize(char *str);
int my_str_isalpha(char const *str);
int my_str_isnum(char const *str);
int my_str_islower(char const *str);
int my_str_isupper(char const *str);
int my_str_isprintable(char const *str);
int my_showstr(char const *str);
char *my_strcat(char *dest, char const *src);
char *my_strncat(char *dest, char const *src, int nb);
int my_char_isnum(char c);
int my_char_isalpha(char c);
int my_show_word_array(char * const *tab);
char **my_str_to_word_array(char const *str);
int my_prime_copy(int nb);
void rewrite_nbr(int nbr, long my_div);
int get_str_len(char *str);
void my_putnbr_base_a(int nbr, char const *base);
char *concat_params_a(int ac, char **av);
int get_len_dest(char *dest);
int get_len_dest_c(char *dest);
int my_strcmp2(char const *c);
char *my_strdup(char const *src);
int get_my_len(char *str);
char *my_putnbr_base(int nbr, char const *base);

//linked list
void my_add_in_sorted_list(struct linked_list **begi, void *data, int (*cmp)());
int my_apply_on_matching_nodes(struct linked_list *begin, int (*f)(void *),
    void const *data_ref, int (*cmp)());
int my_apply_on_nodes(struct linked_list *begin, int (*f)(void *));
void my_concat_list(struct linked_list **begin, struct linked_list *begin2);
int my_delete_nodes(struct linked_list *begin, void const *data_ref,
    int (*cmp)());
struct linked_list *my_find_node(struct linked_list const *begin,
    void const *data_ref, int (*cmp)());
int my_list_size(struct linked_list const *list);
void my_rev_list(struct linked_list **begin);
void my_sort_list(struct linked_list **begin, int (*cmp)());

#endif

struct list{
    void *data;
    struct list *next;
};
typedef struct list list_t;

typedef struct map_s{
    char *map;
    char *map_o;
    int height;
    int width;
    char *mov;
    char *floor;
    int *win_p;
} map_s_t;


typedef struct linked_list
{
    void *data;
    struct linked_list *next;
} linked_list_t;
