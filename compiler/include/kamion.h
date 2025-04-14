/*
** EPITECH PROJECT, 2025
** kamion.h
** File description:
** Kamion header
*/

#ifndef KAMION_H
    #define KAMION_H

    //----------------------------------------------------------------//
    /* INCLUDE */

    /* type */
    #include "hashtable.h" // hashtable_t
    #include "array.h" // array_t
    #include <stdbool.h> // boolean

//----------------------------------------------------------------//
/* TYPEDEF */

/* data */
typedef struct compiler_s {
    /* global_info */
    char const *exe_name;

    /* option */

    /* token id */
    hashtable_t *id;

    /* file information */
    array_t *files;
    hashtable_t *tokens;

    /* ouput */
    bool help;
    bool err_sys;
} compiler_t;

//----------------------------------------------------------------//
/* PROTOTYPE */

/* kamion */
int kamion(int const argc, char const *argv[], compiler_t *data); // Error: KO

/* init_data */
int init_data(compiler_t *data); // Error: KO
int init_global(compiler_t *data); // Error: KO

/* init_flag */
int init_flag(compiler_t *data, int const argc, char const *argv[]); // Error: KO
int flag_help(void); // Error: KO
int flag_null(compiler_t *data, int const argc, char const *argv[]); // Error: KO

/* exit */
int free_data(compiler_t *data); // Error: KO

//----------------------------------------------------------------//
/* GLOBAL_CONST */

/* flag */
extern char const flags[];
extern char const *full_flags[];
extern int const flags_argc[];
extern int (* const flag_functions[])(compiler_t *, int const, char const *[]);

#endif /* KAMION_H */
