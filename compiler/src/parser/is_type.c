/**************************************************************\

 ██╗  ██╗ █████╗ ██████╗ ████████╗ █████╗ ███╗   ██╗██╗ █████╗ 
 ╚██╗██╔╝██╔══██╗██╔══██╗╚══██╔══╝██╔══██╗████╗  ██║██║██╔══██╗
  ╚███╔╝ ███████║██████╔╝   ██║   ███████║██╔██╗ ██║██║███████║
  ██╔██╗ ██╔══██║██╔══██╗   ██║   ██╔══██║██║╚██╗██║██║██╔══██║
 ██╔╝ ██╗██║  ██║██║  ██║   ██║   ██║  ██║██║ ╚████║██║██║  ██║
 ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝

Edition:
##  29/01/2026 by Tsukini

File Name:
##  is_type.c

File Description:
##  Determine if the list of token given is a valid type
\**************************************************************/

#include "array.h"      // array functions
#include "token.h"      // tokens define
#include "parser.h"     // is_value function
#include "tokenizer.h"  // token_t type
#include "kamion.h"     // compiler_t type, get_toks_size functions
#include "error.h"      // error handling
#include <stddef.h>     // size_t type, NULL define
#include <stdbool.h>    // boolean type

static bool is_valid_resizable(compiler_t *data, array_t *tokens, size_t start, size_t end)
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
    bool resizable, unsignable = false;
    size_t size = 0;

    // Check for potential null pointer
    if (!data || !tokens)
        return err_prog(PTR_ERR, false, ERR_INFO);
    
    /*
     ********************
     * type possibility *
     ********************
     * type     | is unisgable  | is manual resizable   | syntax
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

    // unsigned dispatch
    if (tok->id == T_UNSIGNED) {
        tok = tokens->data[start + 1];
        
        // Check the existance of the type between the unsigned & identifier
        if (tok->type != TYPE)
            return err_c15(data, false, tok->file, tok->y, "Parser", "A unsigned must be followed by a type", tok->line, tok->x + 1, tok->x + tok->size, false);

        unsignable = (tok->id == T_CHAR || tok->id == T_STR || tok->id == T_INT || tok->id == T_FLOAT || tok->id == T_PTR);
        resizable = (tok->id >= T_BIN && tok->id <= T_PTR);
        size = get_toks_size(tokens, start + 3, end - 1);
        if (!unsignable)
            return err_c15(data, false, tok->file, tok->y, "Parser", "The only type that can be unsigned are 'char', 'str', 'int', 'float' or 'ptr'", tok->line, tok->x + 1, tok->x + tok->size, false);
        if (end - start > 2) {
            if (resizable && !is_valid_resizable(data, tokens, start + 2, end - 1)) {
                tok = tokens->data[start + 3];
                return err_c15(data, false, tok->file, tok->y, "Parser", "Invalid resize of type, can only be 'type: value identifier'", tok->line, tok->x + 1, tok->x + size, false);
            } else if (!resizable)
                return err_c15(data, false, tok->file, tok->y, "Parser", "This type can only be '[unsigned] type identifier'", tok->line, tok->x + 1, tok->x + size, false);
        }
    }

    // normal type dispatch (char, str, bool, bin, oct, int, hex, float, ptr)
    else if (tok->id >= T_CHAR && tok->id <= T_PTR) {
        
        // If a resize value have been given between the type & the identifier
        if (end - start > 1) {
            resizable = (tok->id >= T_BIN && tok->id <= T_PTR);
            size = get_toks_size(tokens, start + 2, end - 1);
            if (resizable && !is_valid_resizable(data, tokens, start + 1, end - 1)) {
                tok = tokens->data[start + 2];
                return err_c15(data, false, tok->file, tok->y, "Parser", "Invalid resize of type, can only be 'type: value identifier'", tok->line, tok->x + 1, tok->x + size, false);
            } else if (!resizable)
                return err_c15(data, false, tok->file, tok->y, "Parser", "This type can only be '[unsigned] type identifier'", tok->line, tok->x + 1, tok->x + size, false);
        }
    }

    // array dispatch
    else if (tok->id == T_ARRAY) {
        
        // If the type is given between the array & the identifier
        if (end - start > 1)
            return is_type(data, tokens, start + 1, end);
    }

    // struct dispatch
    else if (tok->id == T_STRUCT) {

        // If thing are between the struct & the identifier
        if (end - start != 1) {
            size = get_toks_size(tokens, start + 1, end - 1);
            return err_c15(data, false, tok->file, tok->y, "Parser", "A struct type can only be 'struct identifier'", tok->line, tok->x + 1, tok->x + size, false);
        }
    } 

    // Unknow type start, can't determine the type
    else {
        size = get_toks_size(tokens, start, end);
        return err_c15(data, false, tok->file, tok->y, "Parser", "Can't determine the main purpose of this type", tok->line, tok->x + 1, tok->x + size, false);
    }
    return OK;
}
