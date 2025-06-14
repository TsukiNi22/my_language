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

#include "my_string.h"  // strlen & strcmp & stris function
#include "write.h"      // BASE define
#include "tokenizer.h"  // tokenizer functions
#include "token.h"      // token enum
#include "kamion.h"     // compiler_t type
#include "error.h"      // error handling
#include <string.h>     // strchr functions
#include <regex.h>      // regex functions
#include <stdlib.h>     // malloc & strtol & strtod function
#include <errno.h>      // errno global variable
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
    char *endptr = NULL;
    int len = KO;
    int val = KO;

    // Check for potential null pointer
    if (!data || !str || !id)
        return err_prog(PTR_ERR, false, ERR_INFO);
 
    len = my_strlen(str);
    if (len == KO)
        return err_prog(UNDEF_ERR, false, ERR_INFO);

    /*
    for (int i = 0; i < REGEX_NUMBER; i++) {
        if (pcre_exec(data->regex[i], data->study[i], str, len, 0, 0, NULL, 0) >= 0) {
            val = patterns_val[i];
            break;
        }
    }
    */

    if ((len == 1 && (str[0] == '0' || str[0] == '1')) || my_strcmp(str, "true") == OK || my_strcmp(str, "false") == OK) {
        val = LIT_BOOL;
    } else if (len >= 4 && str[0] == '@' && str[1] == '>' && str[len - 2] == '<' && str[len - 1] == '@') {
        val = LIT_COMMENT;
    } else if (str[0] == '0') {
        if (str[1] == 'b') {
            if (my_str_is(str + 2, BASE_BIN))
                val = LIT_BINARY;
        } else if (str[1] == 'x') {
            if (my_str_is(str + 2, BASE_HEX))
                val = LIT_HEXADECIMAL;
        } else {
            if (my_str_is(str + 1, BASE_OCT))
                val = LIT_OCTAL;
        }
    } else if ((str[0] >= '1' && str[0] <= '9') || str[0] == '-' || str[0] == '.') {
        errno = 0;
        strtol(str, &endptr, 10);
        if (errno == 0 && *endptr == '\0')
            val = LIT_DECIMAL;
        else if (strchr(str, '.')) {
            errno = 0;
            strtod(str, &endptr);
            if (errno == 0 && *endptr == '\0')
                val = LIT_FLOAT;
        }
    } else if (str[0] == '\"') {
        if (pcre_exec(data->regex[6], data->study[6], str, len, 0, 0, NULL, 0) >= 0)
            val = LIT_STRING;
    } else if (str[0] == '\'') {
        if (pcre_exec(data->regex[7], data->study[7], str, len, 0, 0, NULL, 0) >= 0)
            val = LIT_CHAR;
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
