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
##  is_value.c

File Description:
##  Determine if the list of token given is a value
##  value: identifier|litteral|calcul|call
\**************************************************************/

#include "parser.h"     // parser functions, parser enum
#include "token.h"      // tokens define
#include "tokenizer.h"  // token_t type
#include "kamion.h"     // compiler_t type, free_ptr & get_toks_size function
#include "error.h"      // error handling
#include <stdlib.h>     // malloc function
#include <stddef.h>     // size_t type, NULL define
#include <stdbool.h>    // boolean type

// Return the type of an operator
static op_type_t get_op_type(token_id_t id)
{
    op_type_t type = _NONE_;

    // A_OP_B: -, +, *, /, %, //, &, |, ^, <<, >>
    if (id == OP_SUB || id == OP_ADD || id == OP_MULT
        || id == OP_DIV || id == OP_MODULO || id == OP_INT_DIV
        || id == OP_AND || id == OP_OR || id == OP_XOR || id == OP_R_SHIFT || id == OP_L_SHIFT)
        type |= A_OP_B;
    
    // I_OP_A: =, ++, --
    if (id == OP_EQ || id == OP_INC || id == OP_DEC)
        type |= I_OP_A;

    // __OP_A: !, ?, ->
    if (id == OP_NOT || id == OP_BOOL || id == OP_ACCESS)
        type |= __OP_A;

    // __OP_I: <-
    if (id == OP_DEREFERENCING)
        type |= __OP_I;

    // I_OP__: -, +
    if (id == OP_SUB || id == OP_ADD)
        type |= I_OP__;

    // OP__EQ: !, ?, -, +, *, /, %, //, &, |, ^, >>, <<, ->, <-
    if (id == OP_NOT || id == OP_BOOL
        || id == OP_SUB || id == OP_ADD || id == OP_MULT
        || id == OP_DIV || id == OP_MODULO || id == OP_INT_DIV
        || id == OP_AND || id == OP_OR || id == OP_XOR || id == OP_R_SHIFT || id == OP_L_SHIFT
        || id == OP_ACCESS || id == OP_DEREFERENCING)
        type |= OP__EQ;

    return type;
}

// Check if the next token is a valid one after the actual tok
static bool is_next_tok_valid(compiler_t *data, token_t *tok, token_t *next_tok)
{
    op_type_t type = _NONE_;
    op_type_t next_type = _NONE_;

    // Check for potential null pointer
    if (!data || !tok || !next_tok)
        return err_prog(PTR_ERR, false, ERR_INFO);
    
    // Get the operator type or _NONE_ for other token
    type = get_op_type(tok->id);
    next_type = get_op_type(next_tok->id);
    
    // LITERAL -> A_OP_B
    if (tok->type == LITERAL) {
        if (get_op_type(next_tok->id) & A_OP_B)
            return true;
        return err_c15(data, false, next_tok->file, next_tok->y, "Parser", "Invalid token after an operator, can only be follow by an identifier", next_tok->line, next_tok->x + 1, next_tok->x + next_tok->size, false);
    }

    // IDENTIFIER -> DEL_ACCESS, DEL_OPEN_PARENTHESIS, DEL_OPEN_ARRAY, A_OP_B, I_OP_A, I_OP__
    else if (tok->type == IDENTIFIERS) {
        if (next_type & A_OP_B || next_type & I_OP_A || next_type & I_OP__
            || (next_tok->type == DELIMITOR && next_tok->id == DEL_ACCESS)
            || (next_tok->type == DELIMITOR && next_tok->id == DEL_OPEN_PARENTHESIS)
            || (next_tok->type == DELIMITOR && next_tok->id == DEL_OPEN_ARRAY))
            return true;

        return err_c15(data, false, next_tok->file, next_tok->y, "Parser", "Invalid token after an identifier, can only be followed by an open parenthesis, an open array accessor, an operator or an accessor", next_tok->line, next_tok->x + 1, next_tok->x + next_tok->size, false);
    }
    
    // OPERATOR -> DELIMITOR & DEL_OPEN_PARENTHESIS, IDENTIFIER, LITERAL
    else if (tok->type == OPERATOR) {
        
        // OPERATOR OP__EQ followed by the OP_EQ
        if (type & OP__EQ && next_tok->type == OPERATOR && next_tok->id == OP__EQ)
            return true;

        // OPERATOR with an IDENTIFIER after
        if (type & __OP_I) {
            if (next_tok->type != IDENTIFIERS)
                return err_c15(data, false, next_tok->file, next_tok->y, "Parser", "Invalid token after an operator, can only be follow by an identifier", next_tok->line, next_tok->x + 1, next_tok->x + next_tok->size, false);
            return true;
        }

        /*
        // OPERATOR with nothing after
        else if (get_op_type(tok->id) & I_OP__) {
            if (next_tok->type != OPERATOR)
                return err_c15(data, false, next_tok->file, next_tok->y, "Parser", "Invalid token after an operator, can only be follow by an operator", next_tok->line, next_tok->x + 1, next_tok->x + next_tok->size, false);
        }
        */

        // OPERATOR with a value/operator after
        if (type & A_OP_B || type & I_OP_A || type & __OP_A || type & __OP_I) {
            // OPERATOR with an operator after
            if (next_tok->type == OPERATOR && type & I_OP__)
                return true;

            // OPERATOR with a value after
            if (next_tok->type == LITERAL || next_tok->type == IDENTIFIERS
                || (next_tok->type == DELIMITOR && next_tok->id == DEL_OPEN_PARENTHESIS))
                return true;
            
            // Tow different possible messgae
            if (type & I_OP__) return err_c15(data, false, next_tok->file, next_tok->y, "Parser", "Invalid token after an operator, can only be follow by an identifier, a litteral, an open parenthesis or an operator", next_tok->line, next_tok->x + 1, next_tok->x + next_tok->size, false);
            else return err_c15(data, false, next_tok->file, next_tok->y, "Parser", "Invalid token after an operator, can only be follow by an identifier, a litteral or an open parenthesis", next_tok->line, next_tok->x + 1, next_tok->x + next_tok->size, false);
        }
    }
    
    // DELIMITOR & DEL_ACCESS -> IDENTIFIER
    else if (tok->type == DELIMITOR && tok->id == DEL_ACCESS) {
        if (next_tok->type == IDENTIFIERS)
            return true;
        return err_c15(data, false, next_tok->file, next_tok->y, "Parser", "Invalid token after the access token, can only be follow by an identifier", next_tok->line, next_tok->x + 1, next_tok->x + next_tok->size, false);
    }

    // Impossible error
    return err_c15(data, false, next_tok->file, next_tok->y, "Parser", "Invalid token found in a value (Impossible Error)", next_tok->line, next_tok->x + 1, next_tok->x + next_tok->size, false);
}

// return the index of the corresponding pair of delimitor
static size_t find_delimitor_pair(array_t *tokens,
    size_t start, size_t end,
    int open_del, int close_del)
{
    token_t *tok = NULL;
    size_t index = 0;
    int count = 0;

    // Check for potential null pointer
    if (!tokens)
        return err_prog(PTR_ERR, 0, ERR_INFO);

    // Find the index of the corresponding parenthesis
    count = 1;
    for (index = start + 1; count > 0 && index <= end; index++) {
        tok = tokens->data[index];

        // Encouter a opening delimitor
        if (tok->type == DELIMITOR && tok->id == open_del)
            count++;
        // Encouter a closing delimitor
        else if (tok->type == DELIMITOR && tok->id == close_del)
            count--;
    }

    if (index > end && count > 0)
        return err_prog(UNDEF_ERR, start, ERR_INFO);
    return index - 1;
}

// Call is_value for each argument of the call
static int rec_call_arguments(compiler_t *data, array_t *tokens, size_t start, size_t end)
{
    token_t *tok = NULL;
    size_t last_arg = start + 1;
    int count = 0;

    // Check for potential null pointer
    if (!data || !tokens)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    
    // For each tok, while we aren't at the end of the delimitation
    count = 0;
    for (size_t i = start + 1; i <= end; i++) {
        tok = tokens->data[i];

        // Encouter a '('
        if (tok->type == DELIMITOR && tok->id == DEL_OPEN_PARENTHESIS)
            count++;
        // Encouter a ')'
        else if (tok->type == DELIMITOR && tok->id == DEL_CLOSE_PARENTHESIS)
            count--;

        // If we aren't in a sub '()' and the delimitor ',' is encouter
        if (count == 0 && tok->type == DELIMITOR && tok->id == DEL_SEP_1) {
            if (!is_value(data, tokens, last_arg, i - 1))
                return err_prog(UNDEF_ERR, KO, ERR_INFO);
            last_arg = i + 1;
        }
    }

    // Last check
    if (!is_value(data, tokens, last_arg, end - 1))
        return err_prog(UNDEF_ERR, KO, ERR_INFO);

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
    token_t *tok, *next_tok = NULL;
    size_t index = 0;

    // Check for potential null pointer
    if (!data || !tokens)
        return err_prog(PTR_ERR, false, ERR_INFO);

    // Loop on each token
    for (size_t i = start; i < end; i++) {
        tok = tokens->data[i];
        next_tok = tokens->data[i + 1];

        // Check if it's a valid tok for a value
        if (tok->type != LITERAL && tok->type != IDENTIFIERS && tok->type != OPERATOR
            && !(tok->type == DELIMITOR && tok->id == DEL_OPEN_PARENTHESIS)
            && !(tok->type == DELIMITOR && tok->id == DEL_OPEN_ARRAY)
            && !(tok->type == DELIMITOR && tok->id == DEL_ACCESS)) {

            // Invalid closing parenthesis or closing array accessor
            if (tok->type == DELIMITOR && tok->id == DEL_CLOSE_PARENTHESIS) return err_c15(data, false, tok->file, tok->y, "Parser", "No corresponding open parenthesis have been found", tok->line, tok->x + 1, tok->x + tok->size, false);
            else if (tok->type == DELIMITOR && tok->id == DEL_CLOSE_ARRAY) return err_c15(data, false, tok->file, tok->y, "Parser", "No corresponding open array accessor have been found", tok->line, tok->x + 1, tok->x + tok->size, false);

            // Other
            else return err_c15(data, false, tok->file, tok->y, "Parser", "Can't have this type of token in a value", tok->line, tok->x + 1, tok->x + tok->size, false);
        }

        // Recursive call for the DEL_OPEN_PARENTHESIS & DEL_OPEN_ARRAY -> skip directly after
        if (tok->type == DELIMITOR && tok->id == DEL_OPEN_PARENTHESIS) { // for (v, v, ...)

            // Get the index of the corresponding pair of parenthesis
            index = find_delimitor_pair(tokens, i, end, DEL_OPEN_PARENTHESIS, DEL_CLOSE_PARENTHESIS);
            if (index == 0) // An error has occured
                return err_prog_n(UNDEF_ERR, ERR_INFO);
            if (index == i) // No corresponding pair of parenthesis have been found
                return err_c15(data, false, tok->file, tok->y, "Parser", "No closing parenthesis have been found", tok->line, tok->x + 1, tok->x + tok->size, false);

            // Recursive call for each argument of the parenthesis -> (v, v, ...)
            if (rec_call_arguments(data, tokens, i, index) != OK) {
                size_t size = get_toks_size(tokens, i, index);
                if (!size) return err_prog(PTR_ERR, false, ERR_INFO);
                return err_c15(data, false, tok->file, tok->y, "Parser", "Invalid value found during the check of the call arguments", tok->line, tok->x + 1, tok->x + size, false);
            }

            i = index;
        }
        
        else if (tok->type == DELIMITOR && tok->id == DEL_OPEN_ARRAY) { // for [v]

            // Get the index of the corresponding pair of parenthesis
            index = find_delimitor_pair(tokens, i, end, DEL_OPEN_ARRAY, DEL_CLOSE_ARRAY);
            if (index == 0) // An error has occured
                return err_prog_n(UNDEF_ERR, ERR_INFO);
            if (index == i) // No corresponding pair of parenthesis have been found
                return err_c15(data, false, tok->file, tok->y, "Parser", "No closing array accessor have been found", tok->line, tok->x + 1, tok->x + tok->size, false);
            if (index == i + 1) // Empty [] found
                return err_c15(data, false, tok->file, tok->y, "Parser", "Can't eval an empty value", tok->line, tok->x + 1, tok->x + tok->size + next_tok->size, false);

            // Recursive call for each argument of the parenthesis -> (v, v, ...)
            if (!is_value(data, tokens, i + 1, index - 1)) {
                size_t size = get_toks_size(tokens, i, index);
                if (!size) return err_prog(PTR_ERR, false, ERR_INFO);
                return err_c15(data, false, tok->file, tok->y, "Parser", "Invalid value found during the check of the call arguments", tok->line, tok->x + 1, tok->x + size, false);
            }

            i = index;
        }

        // Check the next token
        else if (!is_next_tok_valid(data, tok, next_tok))
            return false;
    }

    return true;
}
