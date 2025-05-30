/**************************************************************\

 ██╗  ██╗ █████╗ ██████╗ ████████╗ █████╗ ███╗   ██╗██╗ █████╗ 
 ╚██╗██╔╝██╔══██╗██╔══██╗╚══██╔══╝██╔══██╗████╗  ██║██║██╔══██╗
  ╚███╔╝ ███████║██████╔╝   ██║   ███████║██╔██╗ ██║██║███████║
  ██╔██╗ ██╔══██║██╔══██╗   ██║   ██╔══██║██║╚██╗██║██║██╔══██║
 ██╔╝ ██╗██║  ██║██║  ██║   ██║   ██║  ██║██║ ╚████║██║██║  ██║
 ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝

Edition:
##  30/05/2025 by Tsukini

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
    #include "kamion.h"     // compiler_t type
    #include <stddef.h>    // boolean
    #include <stdbool.h>    // boolean

//----------------------------------------------------------------//
/* TYPEDEF */

/* tree type value */
typedef enum value_type_e {
    NUMBER = 0,
    IDENTIFIER,
    CALL,
    PRIO,
    OP1,
    OP2
} value_type_t;

//----------------------------------------------------------------//
/* PROTOTYPE */

/* detection */
bool is_value(compiler_t *data, array_t *tokens, size_t start, size_t end); // Error: false

#endif /* PARSER_H */
