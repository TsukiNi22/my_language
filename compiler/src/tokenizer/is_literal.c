/**************************************************************\

 ██╗  ██╗ █████╗ ██████╗ ████████╗ █████╗ ███╗   ██╗██╗ █████╗ 
 ╚██╗██╔╝██╔══██╗██╔══██╗╚══██╔══╝██╔══██╗████╗  ██║██║██╔══██╗
  ╚███╔╝ ███████║██████╔╝   ██║   ███████║██╔██╗ ██║██║███████║
  ██╔██╗ ██╔══██║██╔══██╗   ██║   ██╔══██║██║╚██╗██║██║██╔══██║
 ██╔╝ ██╗██║  ██║██║  ██║   ██║   ██║  ██║██║ ╚████║██║██║  ██║
 ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝

Edition:
##  14/06/2025 by Tsukini

File Name:
##  is_literal.c

File Description:
## Identify literal
\**************************************************************/

#include "my_string.h"  // strlen function
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
    int len = KO;
    int val = KO;

    // Check for potential null pointer
    if (!data || !str || !id)
        return err_prog(PTR_ERR, false, ERR_INFO);
 
    len = my_strlen(str);
    if (len == KO)
        return err_prog(UNDEF_ERR, false, ERR_INFO);
    for (int i = 0; i < REGEX_NUMBER; i++) {
        if (pcre_exec(data->regex[i], data->study[i], str, len, 0, 0, NULL, 0) >= 0) {
            val = patterns_val[i];
            break;
        }
    }

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
