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
    A_OP_B,
    V_OP_A,
    __OP_A,
    __OP_V,
    V_OP__,
    I_X_EQUAL_V,
    I_SPE,
} op_type_t;

//----------------------------------------------------------------//
/* PROTOTYPE */

/* parser */
int parser(compiler_t *data, array_t *tokens); // Error: KO

/* detection */
bool is_value(compiler_t *data, array_t *tokens, size_t start, size_t end); // Error: false
bool is_type(compiler_t *data, array_t *tokens, size_t start, size_t end); // Error: false

#endif /* PARSER_H */
