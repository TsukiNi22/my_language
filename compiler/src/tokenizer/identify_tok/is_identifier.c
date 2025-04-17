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
##  is_identifier.c

File Description:
## Identify identifier
\**************************************************************/

#include "tokenizer.h"  // tokenizer functions
#include "error.h"      // error handling
#include <stdlib.h>     // free function
#include <stddef.h>     // size_t type, NULL define
#include <stdbool.h>    // bool type

/* Identify identifier
----------------------------------------------------------------
 *  Identify the given string to know if it's a identifier
 *  if it's the case then setup the tok
----------------------------------------------------------------
##  tok -> struct of the token
##  str -> string to identify
##  id -> id to set for the token
----------------------------------------------------------------
##  return -> if it's a valid format or not
----------------------------------------------------------------
*/
bool is_identifier(token_t *tok, char *str, int **id)
{
    // Check for potential null pointer
    if (!tok || !str || !id)
        return err_prog(PTR_ERR, false, ERR_INFO);

    if (*id)
        free(*id);
    *id = malloc(sizeof(int));
    if (!*id)
        return err_prog(MALLOC_ERR, false, ERR_INFO);
    *(*id) = -1;
    return true;
}
