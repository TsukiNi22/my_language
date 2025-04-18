/**************************************************************\

 ██╗  ██╗ █████╗ ██████╗ ████████╗ █████╗ ███╗   ██╗██╗ █████╗ 
 ╚██╗██╔╝██╔══██╗██╔══██╗╚══██╔══╝██╔══██╗████╗  ██║██║██╔══██╗
  ╚███╔╝ ███████║██████╔╝   ██║   ███████║██╔██╗ ██║██║███████║
  ██╔██╗ ██╔══██║██╔══██╗   ██║   ██╔══██║██║╚██╗██║██║██╔══██║
 ██╔╝ ██╗██║  ██║██║  ██║   ██║   ██║  ██║██║ ╚████║██║██║  ██║
 ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝

Edition:
##  18/04/2025 by Tsukini

File Name:
##  is_identifier.c

File Description:
## Identify identifier
\**************************************************************/

#include "tokenizer.h"  // tokenizer functions
#include "error.h"      // error handling
#include <regex.h>      // regex functions
#include <stdlib.h>     // malloc function
#include <stddef.h>     // size_t type, NULL define
#include <stdbool.h>    // bool type

/* Identify identifier
----------------------------------------------------------------
 *  Identify the given string to know if it's a identifier
 *  if it's the case then setup the tok
----------------------------------------------------------------
##  str -> string to identify
##  id -> id to set for the token
----------------------------------------------------------------
##  return -> if it's a valid format or not
----------------------------------------------------------------
*/
bool is_identifier(char const *str, int **id)
{
    char const *pattern = "^[A-Za-z_][A-Za-z0-9_]*$";
    regex_t regex = {0};
    int res = 0;

    // Check for potential null pointer
    if (!str || !id)
        return err_prog(PTR_ERR, false, ERR_INFO);

    // Check of the regex
    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB) != OK)
        return err_prog(UNDEF_ERR, false, ERR_INFO);
    res = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);

    // If the regex is false
    if (res != OK)
        return false;

    // Setup the id for a indentifier
    *id = malloc(sizeof(int));
    if (!*id)
        return err_prog(MALLOC_ERR, false, ERR_INFO);
    *(*id) = -1;
    return true;
}
