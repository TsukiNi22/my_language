/**************************************************************\

 ██╗  ██╗ █████╗ ██████╗ ████████╗ █████╗ ███╗   ██╗██╗ █████╗ 
 ╚██╗██╔╝██╔══██╗██╔══██╗╚══██╔══╝██╔══██╗████╗  ██║██║██╔══██╗
  ╚███╔╝ ███████║██████╔╝   ██║   ███████║██╔██╗ ██║██║███████║
  ██╔██╗ ██╔══██║██╔══██╗   ██║   ██╔══██║██║╚██╗██║██║██╔══██║
 ██╔╝ ██╗██║  ██║██║  ██║   ██║   ██║  ██║██║ ╚████║██║██║  ██║
 ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝

Edition:
##  04/06/2025 by Tsukini

File Name:
##  is_value.c

File Description:
##  Determine if the list of token given is a is_value
##  value: identifier|litteral|calcul|call
\**************************************************************/

#include "array.h"      // array functions
#include "parser.h"     // parser functions
#include "token.h"      // tokens define
#include "tokenizer.h"  // token_t type
#include "kamion.h"     // compiler_t type, free_ptr function
#include "error.h"      // error handling
#include <stdlib.h>     // malloc function
#include <stddef.h>     // size_t type, NULL define
#include <stdbool.h>    // boolean type

// return a the struct for tokens type, malloced & setup
static tokens_type_t *setup_type(value_type_t type, size_t start, size_t end)
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

// return the index of the corresponding parenthesis
static size_t find_the_corresponding_parenthesis(array_t *tokens, size_t start)
{
    token_t *tok = NULL;
    size_t index = 0;
    int count = 0;

    // Check for potential null pointer
    if (!tokens)
        return err_prog(PTR_ERR, 0, ERR_INFO);

    // find the index of the corresponding parenthesis
    count = 1;
    for (index = start + 1; count > 0 && index < tokens->len; index++) {
        tok = tokens->data[index];
        if (tok->type == DELIMITOR && tok->id == DEL_OPEN_PARENTHESIS)
            count++;
        else if (tok->type == DELIMITOR && tok->id == DEL_CLOSE_PARENTHESIS)
            count--;
    }
    if (index >= tokens->len)
        return err_prog(UNDEF_ERR, start, ERR_INFO);
    return index;
}

// return the array of type for the given token list
static array_t *get_array_tokens(compiler_t *data, array_t *tokens, size_t start, size_t end)
{
    array_t *array = NULL;
    token_t *tok = NULL;
    size_t size = 0;
    bool is_function, is_methode = false;
    bool op_2 = false;

    // Check for potential null pointer
    if (!data || !tokens)
        return err_prog_n(PTR_ERR, ERR_INFO);

    // setup the array
    array = new_array();
    if (!array)
        return err_prog_n(UNDEF_ERR, ERR_INFO);

    // set the data in the array
    for (size_t i = start; i <= end; i++) {
        tok = tokens->data[i];
        if (tok->type == LITERAL && add_array(array, setup_type(NUMBER, i, i)) == KO)
            return err_prog_n(UNDEF_ERR, ERR_INFO);
        else if (tok->type == IDENTIFIERS) {
            is_function = false;
            is_methode = false;
            if (i + 1 <= end) {
                tok = tokens->data[i + 1];
                is_function = (tok->type == DELIMITOR && tok->id == DEL_OPEN_PARENTHESIS);
                is_methode = (tok->type == DELIMITOR && tok->id == DEL_ACCESS);
            }
            if (!is_function && !is_methode) {
                if (add_array(array, setup_type(IDENTIFIER, i, i)) == KO)
                    return err_prog_n(UNDEF_ERR, ERR_INFO);
            } else if (is_function && i + 1 <= end) {
                size = find_the_corresponding_parenthesis(tokens, i + 1);
                if (size == 0)
                    return err_prog_n(UNDEF_ERR, ERR_INFO);
                if (size == i + 1) {
                    tok = tokens->data[i + 1];
                    err_c15(data, false, tok->file, tok->y, "Parser", "No closing parenthesis have been found", tok->line, tok->x, tok->x + tok->size, false);
                    return NULL;
                }
                if (add_array(array, setup_type(CALL, i, size)) == KO)
                    return err_prog_n(UNDEF_ERR, ERR_INFO);
            } else if (is_methode && i + 2 <= end) {
                tok = tokens->data[i + 2];
                if (!(tok->type == IDENTIFIERS)) {
                    err_c15(data, false, tok->file, tok->y, "Parser", "Invalid token after an access", tok->line, tok->x, tok->x + tok->size, false);
                    return NULL;
                }
                if (i + 3 <= end)
                    tok = tokens->data[i + 3];
                if (i + 3 > end || !(tok->type == DELIMITOR && tok->id == DEL_OPEN_PARENTHESIS)) {
                    if (add_array(array, setup_type(NUMBER, i, size)) == KO)
                        return err_prog_n(UNDEF_ERR, ERR_INFO);
                    continue;
                }
                size = find_the_corresponding_parenthesis(tokens, i + 3);
                if (size == 0)
                    return err_prog_n(UNDEF_ERR, ERR_INFO);
                if (size == i + 3) {
                    tok = tokens->data[i + 3];
                    err_c15(data, false, tok->file, tok->y, "Parser", "No closing parenthesis have been found", tok->line, tok->x, tok->x + tok->size, false);
                    return NULL;
                }
                if (add_array(array, setup_type(CALL, i, size)) == KO)
                    return err_prog_n(UNDEF_ERR, ERR_INFO);
            } else {
                err_c15(data, false, tok->file, tok->y, "Parser", "Can't determine the use of this, the arithmetic expression is ending too early", tok->line, tok->x, tok->x + tok->size, false);
                return NULL;
            }
        } else if (tok->type == OPERATOR) {
            if (tok->id == OP_EQ) {
                err_c15(data, false, tok->file, tok->y, "Parser", "Can't use an attribution in an arithmetic expression", tok->line, tok->x, tok->x + tok->size, false);
                return NULL;
            }
            op_2 = (tok->id == OP_NOT || tok->id == OP_BOOL || tok->id == OP_ACCESS || tok->id == OP_DEREFERENCING);
            if (!op_2 && add_array(array, setup_type(OP_1, i, i)) == KO)
                return err_prog_n(UNDEF_ERR, ERR_INFO);
            if (op_2 && add_array(array, setup_type(OP_2, i, i)) == KO)
                return err_prog_n(UNDEF_ERR, ERR_INFO);
        } else if (tok->type == DELIMITOR && tok->id == DEL_OPEN_PARENTHESIS) {
            for (size = i; !(tok->type == DELIMITOR && tok->id == DEL_CLOSE_PARENTHESIS) && size <= end; size++)
                tok = tokens->data[size];
            if (size > end) {
                tok = tokens->data[i];
                err_c15(data, false, tok->file, tok->y, "Parser", "No closing parenthesis have been found", tok->line, tok->x, tok->x + tok->size, false);
                return NULL;
            }
            if (add_array(array, setup_type(PRIO, i, size)) == KO)
                return err_prog_n(UNDEF_ERR, ERR_INFO);
        } else {
            err_c15(data, false, tok->file, tok->y, "Parser", "Can't use this in an arithmetic expression", tok->line, tok->x, tok->x + tok->size, false);
            return NULL;
        }
    }
    return array;
}

// Setup the start '(' & end ')' of the given call
static int get_start_end(array_t *tokens, size_t *start_ptr, size_t *end_ptr, size_t start, size_t end)
{
    token_t *tok = NULL;

    // Check for potential null pointer
    if (!tokens || !start_ptr || !end_ptr)
        return err_prog(PTR_ERR, KO, ERR_INFO);

    // setup the first '('
    *start_ptr = start + 1;
    tok = tokens->data[start + 1];
    if (tok->type == DELIMITOR && tok->id == DEL_ACCESS)
        *start_ptr = start + 3;
    
    // setup the second ')'
    *end_ptr = end;
    
    return OK;
}

// Call is_value for each argument of the call
static int for_each_call_argument(compiler_t *data, array_t *tokens, size_t start, size_t end)
{
    token_t *tok = NULL;
    size_t last_arg = start;
    int count = 0;

    // Check for potential null pointer
    if (!data || !tokens)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    count = 0;
    for (size_t i = start; i <= end; i++) {
        tok = tokens->data[i];
        if (tok->type == DELIMITOR && tok->id == DEL_OPEN_PARENTHESIS)
            count++;
        else if (tok->type == DELIMITOR && tok->id == DEL_CLOSE_PARENTHESIS)
            count--;
        if (count == 0 && tok->type == DELIMITOR && tok->id == DEL_SEP_1) {
            if (!is_value(data, tokens, last_arg, i - 1))
                return err_prog(UNDEF_ERR, KO, ERR_INFO);
            last_arg = i + 1;
        }
    }
    if (!is_value(data, tokens, last_arg, end))
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    return OK;
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
    size_t start_prio, end_prio = 0;

    // Check for potential null pointer
    if (!data || !tokens)
        return err_prog(PTR_ERR, false, ERR_INFO);
 
    array = get_array_tokens(data, tokens, start, end);
    if (!array)
        return err_prog(UNDEF_ERR, false, ERR_INFO);

    // recall the is_value for some execption
    for (size_t i = 0; i < array->len; i++) {
        toks_type = array->data[i];
        if (toks_type->type == PRIO && !is_value(data, tokens, toks_type->start + 1, toks_type->end - 1))
            return err_prog(UNDEF_ERR, false, ERR_INFO);
        if (toks_type->type == CALL) {
            if (get_start_end(tokens, &start_prio, &end_prio, toks_type->start, toks_type->end) == KO)
                return err_prog(UNDEF_ERR, false, ERR_INFO);
            if (for_each_call_argument(data, tokens, start_prio + 1, end_prio - 1) == KO)
                return err_prog(UNDEF_ERR, false, ERR_INFO);
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
