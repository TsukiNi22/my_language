/*
** EPITECH PROJECT, 2025
** kamion.h
** File description:
** Kamion header
*/

#ifndef TOKENIZER_H
    #define TOKENIZER_H

    //----------------------------------------------------------------//
    /* INCLUDE */

    /* type */
    #include "hashtable.h" // hashtable_t
    #include "array.h" // array_t
    #include <stddef.h> // size_t

//----------------------------------------------------------------//
/* TYPEDEF */

/* token */
typedef struct token_s {
    /* tokn type information */
    char *type;
    char *id;

    /* position information */
    char const *file;
    size_t x;
    size_t y;

    /* literal | identifier */
    char *value;
} token_t;

//----------------------------------------------------------------//
/* PROTOTYPE */

/* tokenizer */
array_t *tokenizer(hashtable_t *id, char const *file); // Error: NULL

#endif /* TOKENIZER_H */
