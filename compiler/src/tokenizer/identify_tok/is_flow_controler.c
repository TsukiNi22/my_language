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
##  is_flow_controler.c

File Description:
## Identify key word
\**************************************************************/

#include "tokenizer.h"  // tokenizer functions
#include "error.h"      // error handling
#include <stdlib.h>     // free function
#include <stddef.h>     // size_t type, NULL define
#include <stdbool.h>    // bool type

/* Identify flow controler
----------------------------------------------------------------
 *  Identify the given string to know if it's a flow controler
 *  if it's the case then setup the tok
----------------------------------------------------------------
##  tok -> struct of the token
##  str -> string to identify
----------------------------------------------------------------
##  return -> if it's a valid format or not
----------------------------------------------------------------
*/
bool is_flow_controler(token_t *tok, char *str)
{
    // Check for potential null pointer
    if (!tok || !str)
        return err_prog_n(PTR_ERR, ERR_INFO);

    free(str);
    return true;
}
