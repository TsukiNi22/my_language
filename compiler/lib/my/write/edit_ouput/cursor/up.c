/*
** EPITECH PROJECT, 2025
** up.c
** File description:
** Change cursor position
*/

#include "define.h"
#include "write.h"
#include "error.h"

int cursor_up(int fd, int n)
{
    int res = OK;

    res += my_putchar(fd, ESC);
    res += my_putchar(fd, '[');
    res += my_putnbr(fd, n);
    res += my_putchar(fd, 'A');
    if (res != OK)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    return OK;
}
