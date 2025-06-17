/**************************************************************\

 ██╗  ██╗ █████╗ ██████╗ ████████╗ █████╗ ███╗   ██╗██╗ █████╗ 
 ╚██╗██╔╝██╔══██╗██╔══██╗╚══██╔══╝██╔══██╗████╗  ██║██║██╔══██╗
  ╚███╔╝ ███████║██████╔╝   ██║   ███████║██╔██╗ ██║██║███████║
  ██╔██╗ ██╔══██║██╔══██╗   ██║   ██╔══██║██║╚██╗██║██║██╔══██║
 ██╔╝ ██╗██║  ██║██║  ██║   ██║   ██║  ██║██║ ╚████║██║██║  ██║
 ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝

Edition:
##  17/06/2025 by Tsukini

File Name:
##  parser.c

File Description:
## Parser information and prototype
\**************************************************************/

#ifndef PARSER_H
    #define PARSER_H

    //----------------------------------------------------------------//
    /* INCLUDE */

    /* type */
    #include "array.h"      // array_t type
    #include "kamion.h"     // compiler_t type
    #include <stddef.h>     // size_t type
    #include <stdbool.h>    // boolean type

//----------------------------------------------------------------//
/* TYPEDEF */

/* type_value */
typedef enum value_type_e {
    NUMBER = 0,
    IDENTIFIER,
    OP_1,
    OP_2,
    PRIO,
    CALL,
} value_type_t;

/* array_tokens_type */
typedef struct tokens_type_s {
    /* type */
    value_type_t type;

    /* position */
    size_t start;
    size_t end;
} tokens_type_t;

//----------------------------------------------------------------//
/* PROTOTYPE */

/* parser */
int parser(compiler_t *data, array_t *tokens); // Error: KO

/* detection */
bool is_value(compiler_t *data, array_t *tokens, size_t start, size_t end); // Error: false

#endif /* PARSER_H */
