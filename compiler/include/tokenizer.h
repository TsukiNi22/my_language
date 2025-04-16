/**************************************************************\

 ██╗  ██╗ █████╗ ██████╗ ████████╗ █████╗ ███╗   ██╗██╗ █████╗ 
 ╚██╗██╔╝██╔══██╗██╔══██╗╚══██╔══╝██╔══██╗████╗  ██║██║██╔══██╗
  ╚███╔╝ ███████║██████╔╝   ██║   ███████║██╔██╗ ██║██║███████║
  ██╔██╗ ██╔══██║██╔══██╗   ██║   ██╔══██║██║╚██╗██║██║██╔══██║
 ██╔╝ ██╗██║  ██║██║  ██║   ██║   ██║  ██║██║ ╚████║██║██║  ██║
 ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝

Edition:
##  15/04/2025 by Tsukini

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
array_t *tokenizer(compiler_t *data, hashtable_t *id, char const *file); // Error: NULL

#endif /* TOKENIZER_H */
