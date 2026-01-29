/**************************************************************\

 ██╗  ██╗ █████╗ ██████╗ ████████╗ █████╗ ███╗   ██╗██╗ █████╗ 
 ╚██╗██╔╝██╔══██╗██╔══██╗╚══██╔══╝██╔══██╗████╗  ██║██║██╔══██╗
  ╚███╔╝ ███████║██████╔╝   ██║   ███████║██╔██╗ ██║██║███████║
  ██╔██╗ ██╔══██║██╔══██╗   ██║   ██╔══██║██║╚██╗██║██║██╔══██║
 ██╔╝ ██╗██║  ██║██║  ██║   ██║   ██║  ██║██║ ╚████║██║██║  ██║
 ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝

Edition:
##  28/01/2026 by Tsukini

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

/* op_type */
typedef enum op_type_e {
    _NONE_ = 0b0,
    A_OP_B = 0b1,
    I_OP_A = 0b10,
    __OP_A = 0b100,
    __OP_I = 0b1000,
    I_OP__ = 0b10000,
    OP__EQ = 0b100000,
} op_type_t;

//----------------------------------------------------------------//
/* PROTOTYPE */

/* parser */
int parser(compiler_t *data, array_t *tokens); // Error: KO

/* detection */
bool is_value(compiler_t *data, array_t *tokens, size_t start, size_t end); // Error: false
bool is_type(compiler_t *data, array_t *tokens, size_t start, size_t end); // Error: false

#endif /* PARSER_H */
