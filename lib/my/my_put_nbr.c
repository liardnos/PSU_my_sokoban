/*
** EPITECH PROJECT, 2019
** my_put_nbr
** File description:
** Print a number in console
*/

void my_putchar(char c);

void my_put_nbr(long int nb)
{
    long int count = 1000000000000;
    int neg = nb < 0 ? nb *=-1, my_putchar('-'), 1 : 0;
    if (nb < 0){
        my_putchar(45);
        nb = -nb;
    }
    while (nb / count == 0 && count > 1){
        count = count / 10;
    }
    while (count != 0){
        my_putchar(48 + nb / count);
        nb -= (nb/count) * count;
        count = count / 10;
    }
}
