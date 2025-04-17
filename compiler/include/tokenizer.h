/**************************************************************\

 ██╗  ██╗ █████╗ ██████╗ ████████╗ █████╗ ███╗   ██╗██╗ █████╗ 
 ╚██╗██╔╝██╔══██╗██╔══██╗╚══██╔══╝██╔══██╗████╗  ██║██║██╔══██╗
  ╚███╔╝ ███████║██████╔╝   ██║   ███████║██╔██╗ ██║██║███████║
  ██╔██╗ ██╔══██║██╔══██╗   ██║   ██╔══██║██║╚██╗██║██║██╔══██║
 ██╔╝ ██╗██║  ██║██║  ██║   ██║   ██║  ██║██║ ╚████║██║██║  ██║
 ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝

Edition:
##  17/04/2025 by Tsukini

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

    /*  */
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
array_t *tokenizer(compiler_t *data, hashtable_t *id, char const *file); // Error: NULL

/* identify token */
bool is_key_word(token_t *tok, char *str); // Error: false
bool is_flow_controler(token_t *tok, char *str); // Error: false
bool is_type(token_t *tok, char *str); // Error: false
bool is_operator(token_t *tok, char *str); // Error: false
bool is_delimitor(token_t *tok, char *str); // Error: false
bool is_identifier(token_t *tok, char *str); // Error: false
bool is_literal(token_t *tok, char *str); // Error: false

/* debug */
int tokens_dump(hashtable_t *tokens);

/* exit */
int free_token(void *ptr);

#endif /* TOKENIZER_H */
