/**************************************************************\

 ██╗  ██╗ █████╗ ██████╗ ████████╗ █████╗ ███╗   ██╗██╗ █████╗ 
 ╚██╗██╔╝██╔══██╗██╔══██╗╚══██╔══╝██╔══██╗████╗  ██║██║██╔══██╗
  ╚███╔╝ ███████║██████╔╝   ██║   ███████║██╔██╗ ██║██║███████║
  ██╔██╗ ██╔══██║██╔══██╗   ██║   ██╔══██║██║╚██╗██║██║██╔══██║
 ██╔╝ ██╗██║  ██║██║  ██║   ██║   ██║  ██║██║ ╚████║██║██║  ██║
 ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝

Edition:
##  04/06/2025 by Tsukini

File Name:
##  tokenizer.h

File Description:
## Header of the tokenizer part
\**************************************************************/

#ifndef TOKENIZER_H
    #define TOKENIZER_H

    //----------------------------------------------------------------//
    /* INCLUDE */

    /* type */
    #include "hashtable.h" // hashtable_t
    #include "array.h" // array_t
    #include "kamion.h" // compiler_t
    #include <stddef.h> // size_t
    #include <stdbool.h> // bool

//----------------------------------------------------------------//
/* TYPEDEF */

/* token */
typedef struct token_s {
    /* tokn type information */
    int type;
    int id;

    /* global information */
    char *file;
    char *line;

    /* position information */
    size_t x;
    size_t y;
    size_t size;

    /* literal | identifier */
    char *value;
} token_t;

//----------------------------------------------------------------//
/* PROTOTYPE */

/* tokenizer */
array_t *tokenizer(compiler_t *data, hashtable_t *ids, char const *file); // Error: NULL

/* identify token */
bool is_identifier(char const *str, int **id); // Error: false
bool is_literal(char const *str, int **id); // Error: false

/* debug */
int tokens_dump(hashtable_t *tokens);

/* exit */
int free_token(void *ptr);

#endif /* TOKENIZER_H */
