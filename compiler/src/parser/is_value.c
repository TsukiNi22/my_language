/**************************************************************\

 ██╗  ██╗ █████╗ ██████╗ ████████╗ █████╗ ███╗   ██╗██╗ █████╗ 
 ╚██╗██╔╝██╔══██╗██╔══██╗╚══██╔══╝██╔══██╗████╗  ██║██║██╔══██╗
  ╚███╔╝ ███████║██████╔╝   ██║   ███████║██╔██╗ ██║██║███████║
  ██╔██╗ ██╔══██║██╔══██╗   ██║   ██╔══██║██║╚██╗██║██║██╔══██║
 ██╔╝ ██╗██║  ██║██║  ██║   ██║   ██║  ██║██║ ╚████║██║██║  ██║
 ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝

Edition:
##  31/05/2025 by Tsukini

File Name:
##  is_value.c

File Description:
##  Determine if the list of token given is a is_value
##  value: identifier|litteral|calcul|call
\**************************************************************/

#include "array.h"      // array functions
#include "parser.h"     // parser functions
#include "kamion.h"     // compiler_t type, free_ptr function
#include "error.h"      // error handling
#include <stdlib.h>     // malloc function
#include <stddef.h>     // size_t type, NULL define

// return a the struct for tokens type, malloced & setup
static tokens_type_t *setup_type(value_type_t type , size_t start, size_t end)
{
    tokens_type_t *toks_type = NULL;

    // malloc & setup the struct
    toks_type = malloc(sizeof(tokens_type_t));
    if (!toks_type)
        return err_prog_n(PTR_ERR, ERR_INFO);
    toks_type->type = type;
    toks_type->start = start;
    toks_type->end = end;
    return toks_type;
}

// return the array of type for the given token list
static array_t *get_array_tokens(array_t *tokens, size_t start, size_t end)
{
    array_t *array = NULL;

    // Check for potential null pointer
    if (!tokens)
        return err_prog_n(PTR_ERR, ERR_INFO);

    array = new_array();
    if (!array)
        return err_prog_n(PTR_ERR, ERR_INFO);
    return array;
}

// Free simple pointer
static int free_ptr(void *ptr)
{
    // Check for potential null pointer
    if (!ptr)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    free(ptr);
    return OK;
}

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
    tokens_type_t *toks_type = NULL;
    array_t *array = NULL;

    // Check for potential null pointer
    if (!data || !tokens)
        return err_prog(PTR_ERR, false, ERR_INFO);
 
    array = get_array_tokens(tokens, start, end);
    if (!array)
        return err_prog(UNDEF_ERR, false, ERR_INFO);

    // recall the is_value for some execption
    for (size_t i = 0; i < array->len; i++) {
        toks_type = array->data[i];
        if (toks_type->type == PRIO && is_value(data, tokens, toks_type->start + 1, toks_type->end - 1) == KO)
            return err_prog(UNDEF_ERR, false, ERR_INFO);
        if (toks_type->type == CALL) {
        }
    }

    /*
     * get list of type (Number, Identifier, Call, Prio, op1, op2)
     * for each type recall is_value for each Prio and each argument of call
    */
    if (delete_array(&array, &free_ptr) == KO)
        return err_prog(UNDEF_ERR, false, ERR_INFO);
    return true;
}
