/*
** EPITECH PROJECT, 2025
** const.c
** File description:
** Global const
*/

#include "sample.h"

char const flags[] = {
    'h'
};

char const *full_flags[] = {
    "--help"
};

int const flags_argc[] = {
    -1   // h
};

int (* const flag_functions[])(main_data_t *, int const, char const *[]) = {
    &flag_null  // h
};
