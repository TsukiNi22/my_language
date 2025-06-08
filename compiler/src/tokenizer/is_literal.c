/**************************************************************\

 ██╗  ██╗ █████╗ ██████╗ ████████╗ █████╗ ███╗   ██╗██╗ █████╗ 
 ╚██╗██╔╝██╔══██╗██╔══██╗╚══██╔══╝██╔══██╗████╗  ██║██║██╔══██╗
  ╚███╔╝ ███████║██████╔╝   ██║   ███████║██╔██╗ ██║██║███████║
  ██╔██╗ ██╔══██║██╔══██╗   ██║   ██╔══██║██║╚██╗██║██║██╔══██║
 ██╔╝ ██╗██║  ██║██║  ██║   ██║   ██║  ██║██║ ╚████║██║██║  ██║
 ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝

Edition:
##  08/06/2025 by Tsukini

File Name:
##  is_literal.c

File Description:
## Identify literal
\**************************************************************/

#include "tokenizer.h"  // tokenizer functions
#include "token.h"      // token enum
#include "kamion.h"     // compiler_t type
#include "error.h"      // error handling
#include <regex.h>      // regex functions
#include <stdlib.h>     // malloc function
#include <stddef.h>     // size_t type, NULL define
#include <stdbool.h>    // bool type

/* Identify literal
----------------------------------------------------------------
 *  Identify the given string to know if it's a literal
 *  if it's the case then setup the tok
----------------------------------------------------------------
##  str -> string to identif
##  id -> id to set for the token
----------------------------------------------------------------
##  return -> if it's a valid format or not
----------------------------------------------------------------
*/
bool is_literal(compiler_t *data, char const *str, int **id)
{
    int val = KO;

    // Check for potential null pointer
    if (!data || !str || !id)
        return err_prog(PTR_ERR, false, ERR_INFO);
 
    if (regexec(&(data->regex[0]), str, 0, NULL, 0) == OK) // bool
        val = LIT_BOOL;
    else if (regexec(&(data->regex[1]), str, 0, NULL, 0) == OK) // bin
        val = LIT_BINARY;
    else if (regexec(&(data->regex[2]), str, 0, NULL, 0) == OK) // oct
        val = LIT_OCTAL;
    else if (regexec(&(data->regex[3]), str, 0, NULL, 0) == OK) // hex
        val = LIT_HEXADECIMAL;
    else if (regexec(&(data->regex[4]), str, 0, NULL, 0) == OK) // int
        val = LIT_DECIMAL;
    else if (regexec(&(data->regex[5]), str, 0, NULL, 0) == OK) // float
        val = LIT_FLOAT;
    else if (regexec(&(data->regex[6]), str, 0, NULL, 0) == OK) // string
        val = LIT_STRING;
    else if (regexec(&(data->regex[7]), str, 0, NULL, 0) == OK) // char
        val = LIT_CHAR;
    else if (regexec(&(data->regex[8]), str, 0, NULL, 0) == OK) // comment
        val = LIT_COMMENT;

    // No pattern found
    if (val == KO)
        return false;
    
    // Setup the id for a literal
    *id = malloc(sizeof(int));
    if (!*id)
        return err_prog(MALLOC_ERR, false, ERR_INFO);
    *(*id) = val;
    return true;
}
