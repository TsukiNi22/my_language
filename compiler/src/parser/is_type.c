/**************************************************************\

 ██╗  ██╗ █████╗ ██████╗ ████████╗ █████╗ ███╗   ██╗██╗ █████╗ 
 ╚██╗██╔╝██╔══██╗██╔══██╗╚══██╔══╝██╔══██╗████╗  ██║██║██╔══██╗
  ╚███╔╝ ███████║██████╔╝   ██║   ███████║██╔██╗ ██║██║███████║
  ██╔██╗ ██╔══██║██╔══██╗   ██║   ██╔══██║██║╚██╗██║██║██╔══██║
 ██╔╝ ██╗██║  ██║██║  ██║   ██║   ██║  ██║██║ ╚████║██║██║  ██║
 ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝

Edition:
##  06/12/2025 by Tsukini

File Name:
##  is_type.c

File Description:
##  Determine if the list of token given is a valid type
\**************************************************************/

#include "array.h"      // array functions
#include "token.h"      // tokens define
#include "parser.h"     // is_value function
#include "tokenizer.h"  // token_t type
#include "kamion.h"     // compiler_t type
#include "error.h"      // error handling
#include <stddef.h>     // size_t type, NULL define
#include <stdbool.h>    // boolean type

// Return the size of the tokens between start & end
static size_t get_tok_size(array_t *tokens, size_t start, size_t end)
{
    token_t *tok = NULL;
    size_t y, x = 0;
    size_t i = 0;

    // Check for potential null pointer
    if (!tokens)
        return err_prog(PTR_ERR, 0, ERR_INFO);

    tok = tokens->data[start];
    x = tok->x;
    y = tok->y;
    for (i = start; ((token_t *) tokens->data[i])->y == y && i <= end; i++);
    tok = tokens->data[i - 1];
    return (tok->x - x) + tok->size;
}

static bool is_valid_resisable(compiler_t *data, array_t *tokens, size_t start, size_t end)
{
    token_t *tok = NULL;

    // Check for potential null pointer
    if (!data || !tokens)
        return err_prog(PTR_ERR, false, ERR_INFO);

    /*
     *****************
     * resize syntax *
     *****************
     : value    | DEL_SEP_2 VALUE
    */

    // Check the delimitor ':'
    tok = tokens->data[start];
    if (tok->type != DELIMITOR && tok->id != DEL_SEP_2)
        return false;

    // Check the value after the delimitor ':'
    if (!is_value(data, tokens, start + 1, end))
        return false;

    return true;
}

/* Function to check if the list of token is a valide type
----------------------------------------------------------------
 * take a list of tokens and determine if it's a valid type
----------------------------------------------------------------
##  data -> main data structure
##  tokens -> list of the tokens of a file
##  start -> starting index of the supposed type
##  end -> ending index of the supposed type
----------------------------------------------------------------
##  return -> return if the list of tokens is a valid type
----------------------------------------------------------------
*/
bool is_type(compiler_t *data, array_t *tokens, size_t start, size_t end)
{
    token_t *tok = NULL;
    bool resisable, unsignable = false;
    size_t size = 0;

    // Check for potential null pointer
    if (!data || !tokens)
        return err_prog(PTR_ERR, false, ERR_INFO);
    
    /*
     ********************
     * type possibility *
     ********************
     * type     | is unisgable  | is manual resisable   | syntax
     * char     | y             | n                     | [T_UNSIGNED] T_CHAR IDENTIFIERS
     * str      | y             | n                     | [T_UNSIGNED] T_STR IDENTIFIERS
     * bool     | n             | n                     | T_BOOL IDENTIFIERS
     * bin      | n             | y                     | T_BIN [DEL_SEP_2 VALUE] IDENTIFIERS
     * oct      | n             | y                     | T_OCT [DEL_SEP_2 VALUE] IDENTIFIERS
     * int      | y             | y                     | [T_UNSIGNED] T_INT [DEL_SEP_2 VALUE] IDENTIFIERS
     * hex      | n             | y                     | T_HEX [DEL_SEP_2 VALUE] IDENTIFIERS
     * float    | y             | y                     | [T_UNSIGNED] T_FLOAT [DEL_SEP_2 VALUE] IDENTIFIERS
     * ptr      | y             | y                     | [T_UNSIGNED] T_PTR [DEL_SEP_2 VALUE] IDENTIFIERS
     * array    | y             | n                     | T_ARRAY TYPE IDENTIFIERS
     * struct   | n             | n                     | T_STRUCT IDENTIFIERS
    */

    // Check if the type end with a good token
    tok = tokens->data[end];
    if (tok->type != IDENTIFIERS)
        return err_c15(data, false, tok->file, tok->y, "Parser", "A variable initialisation must end with a identifier", tok->line, tok->x + 1, tok->x + tok->size, false);

    // Dispatch the check of type for unsigned / no unsigned / array / struct / other
    tok = tokens->data[start];
    if (tok->id == T_UNSIGNED) {
        tok = tokens->data[start + 1];
        if (tok->type != TYPE)
            return err_c15(data, false, tok->file, tok->y, "Parser", "A unsigned must be followed by a type", tok->line, tok->x + 1, tok->x + tok->size, false);
        unsignable = (tok->id == T_CHAR || tok->id == T_STR || tok->id == T_INT || tok->id == T_FLOAT || tok->id == T_PTR);
        resisable = (tok->id >= T_BIN && tok->id <= T_PTR);
        size = get_tok_size(tokens, start + 2, end - 1);
        if (!unsignable)
            return err_c15(data, false, tok->file, tok->y, "Parser", "The only type that can be unsigned are 'char', 'str', 'int', 'float' or 'ptr'", tok->line, tok->x + 1, tok->x + tok->size, false);
        if (end - start > 2) {
            if (resisable && !is_valid_resisable(data, tokens, start + 2, end - 1)) {
                tok = tokens->data[start + 2];
                return err_c15(data, false, tok->file, tok->y, "Parser", "Invalid resize of type, can only be 'type: value identifier'", tok->line, tok->x + 1, tok->x + size, false);
            } else if (!resisable)
                return err_c15(data, false, tok->file, tok->y, "Parser", "This type can only be '[unsigned] type identifier'", tok->line, tok->x + 1, tok->x + size, false);
        }
    } else if (tok->id >= T_CHAR && tok->id <= T_PTR) {
        if (end - start > 1) {
            resisable = (tok->id >= T_BIN && tok->id <= T_PTR);
            size = get_tok_size(tokens, start + 1, end - 1);
            if (resisable && !is_valid_resisable(data, tokens, start + 1, end - 1)) {
                tok = tokens->data[start + 1];
                return err_c15(data, false, tok->file, tok->y, "Parser", "Invalid resize of type, can only be 'type: value identifier'", tok->line, tok->x + 1, tok->x + size, false);
            } else if (!resisable)
                return err_c15(data, false, tok->file, tok->y, "Parser", "This type can only be '[unsigned] type identifier'", tok->line, tok->x + 1, tok->x + size, false);
        }
    } else if (tok->id == T_ARRAY) {
        if (end - start > 1)
            return is_type(data, tokens, start + 1, end);
    } else if (tok->id == T_STRUCT) {
        if (end - start != 1) {
            size = get_tok_size(tokens, start + 1, end - 1);
            return err_c15(data, false, tok->file, tok->y, "Parser", "A struct type can only be 'struct identifier'", tok->line, tok->x + 1, tok->x + size, false);
        }
    } else {
        size = get_tok_size(tokens, start, end);
        return err_c15(data, false, tok->file, tok->y, "Parser", "Can't determine the main purpose of this type", tok->line, tok->x + 1, tok->x + size, false);
    }
    return OK;
}
