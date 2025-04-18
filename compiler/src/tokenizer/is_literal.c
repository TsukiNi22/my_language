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
##  is_literal.c

File Description:
## Identify literal
\**************************************************************/

#include "tokenizer.h"  // tokenizer functions
#include "token.h"      // token enum
#include "error.h"      // error handling
#include <regex.h>      // regex functions
#include <stdlib.h>     // malloc function
#include <stddef.h>     // size_t type, NULL define
#include <stdbool.h>    // bool type

static bool is_regex(char const *pattern, char const *str)
{
    regex_t regex = {0};
    int res = 0;

    // Check for potential null pointer
    if (!pattern || !str)
        return err_prog(PTR_ERR, false, ERR_INFO);

    // Check of the regex
    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB) != OK)
        return err_prog(UNDEF_ERR, false, ERR_INFO);
    res = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);

    // If the regex is false
    if (res != OK)
        return false;
    return true;
}

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
bool is_literal(char const *str, int **id)
{
    int val = KO;

    // Check for potential null pointer
    if (!str || !id)
        return err_prog(PTR_ERR, false, ERR_INFO);
 
    if (is_regex("^(0|1|true|false)$", str)) // bool
        val = LIT_BOOL;
    else if (is_regex("^0b[01]*$", str)) // bin
        val = LIT_BINARY;
    else if (is_regex("^0[0-7]*$", str)) // oct
        val = LIT_OCTAL;
    else if (is_regex("^0x[0-9a-fA-F]*$", str)) // hex
        val = LIT_HEXADECIMAL;
    else if (is_regex("^-?[0-9]+$", str)) // int
        val = LIT_DECIMAL;
    else if (is_regex("^-?([0-9]+\\.[0-9]*|\\.[0-9]+)$", str)) // float
        val = LIT_FLOAT;
    else if (is_regex("^\"([^\"\\\\]|\\\\.)*\"$", str)) // string
        val = LIT_STRING;
    else if (is_regex("^'(\\.|[^'\\\\])'$", str)) // char
        val = LIT_CHAR;
    else if (is_regex("^@>.*<@$", str)) // char
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
