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
##  is_value.c

File Description:
##  Determine if the list of token given is a is_value
##  value: identifier|litteral|calcul|call
\**************************************************************/

#include "parser.h"     // parser functions
#include "kamion.h"     // compiler_t type
#include "error.h"      // error handling
#include <stddef.h>     // size_t type

/* Function to check if the list of token is a value
----------------------------------------------------------------
 * take a list of tokens and determine if it's a valid value
 * valid value is determine by: identifier|litteral|calcul|call
----------------------------------------------------------------
##  data -> main data structure
##  tokens -> list of the tokens of a file
##  start -> starting index of the supposed value
##  end -> ending index of the supposed value
----------------------------------------------------------------
##  return -> return if the list of tokens is a valid value
----------------------------------------------------------------
*/
bool is_value(compiler_t *data, array_t *tokens, size_t start, size_t end)
{
    // Check for potential null pointer
    if (!data || !tokens)
        return err_prog(PTR_ERR, false, ERR_INFO);
 
    /*
     * get list of type (Number, Identifier, Call, Prio, op1, op2)
     * for each type recall is_value for each Prio and each argument of call
    */
    return true;
}
