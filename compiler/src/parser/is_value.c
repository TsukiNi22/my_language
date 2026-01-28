/**************************************************************\

 ██╗  ██╗ █████╗ ██████╗ ████████╗ █████╗ ███╗   ██╗██╗ █████╗ 
 ╚██╗██╔╝██╔══██╗██╔══██╗╚══██╔══╝██╔══██╗████╗  ██║██║██╔══██╗
  ╚███╔╝ ███████║██████╔╝   ██║   ███████║██╔██╗ ██║██║███████║
  ██╔██╗ ██╔══██║██╔══██╗   ██║   ██╔══██║██║╚██╗██║██║██╔══██║
 ██╔╝ ██╗██║  ██║██║  ██║   ██║   ██║  ██║██║ ╚████║██║██║  ██║
 ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝

Edition:
##  28/01/2026 by Tsukini

File Name:
##  is_value.c

File Description:
##  Determine if the list of token given is a value
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

// Check if the next token is a valid one after the actual tok
static bool is_next_tok_valid(compiler_t *data, token_t *tok, token_t *next_tok)
{
    // Check for potential null pointer
    if (!data || !tok || !next_tok)
        return err_prog(PTR_ERR, false, ERR_INFO);

    if (tok->type == LITERAL) { // LITERAL -> A_OP_B
        
    }

    else if (tok->type == IDENTIFIERS) { // IDENTIFIER -> DEL_OPEN_PARENTHESIS, DEL_OPEN_ARRAY, A_OP_B, I_OP_A, I_OP__, I_X_EQUAL_V
        
    }
    
    else if (tok->type == OPERATOR) { // OPERATOR -> DELIMITOR & DEL_OPEN_PARENTHESIS, IDENTIFIER, LITERAL
    
    }
    
    else if (tok->type == DELIMITOR && tok->id == DEL_ACCESS) { // DELIMITOR & DEL_ACCESS -> IDENTIFIER
    
    }

    return true;
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
    size_t last_arg = start;
    int count = 0;

    // Check for potential null pointer
    if (!data || !tokens)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    
    // For each tok, while we aren't at the end of the delimitation
    count = 0;
    for (size_t i = start; i <= end; i++) {
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
    if (!is_value(data, tokens, last_arg + 1, end - 1))
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
    for (size_t i = start; i <= end; i++) {
        tok = tokens->data[i];
        next_tok = tokens->data[i + 1];

        // Check if it's a valid tok for a value
        if (tok->type != LITERAL && tok->type != IDENTIFIERS && tok->type != OPERATOR
            && !(tok->type == DELIMITOR && tok->id == DEL_OPEN_PARENTHESIS)
            && !(tok->type == DELIMITOR && tok->id == DEL_OPEN_ARRAY)
            && !(tok->type == DELIMITOR && tok->id == DEL_ACCESS))
            return err_c15(data, false, tok->file, tok->y, "Parser", "Can't have this type of token in a value", tok->line, tok->x + 1, tok->x + tok->size, false);

        // Recursive call for the DEL_OPEN_PARENTHESIS & DEL_OPEN_ARRAY -> skip directly after
        if (tok->type == DELIMITOR && tok->id == DEL_OPEN_PARENTHESIS) { // for (v, v, ...)

            // Get the index of the corresponding pair of parenthesis
            index = find_delimitor_pair(tokens, start, end, DEL_OPEN_PARENTHESIS, DEL_CLOSE_PARENTHESIS);
            if (index == 0) // An error has occured
                return err_prog_n(UNDEF_ERR, ERR_INFO);
            if (index == start) // No corresponding pair of parenthesis have been found
                return err_c15(data, false, tok->file, tok->y, "Parser", "No closing parenthesis have been found", tok->line, tok->x + 1, tok->x + tok->size, false);

            // Recursive call for each argument of the parenthesis -> (v, v, ...)
            if (rec_call_arguments(data, tokens, i, index) != OK)
                return err_c15(data, false, tok->file, tok->y, "Parser", "Invalid value found during the check of the call arguments", tok->line, tok->x + 1, tok->x + tok->size, false);
            
            i = index;
        }
        
        else if (tok->type == DELIMITOR && tok->id == DEL_OPEN_ARRAY) { // for [v]

            // Get the index of the corresponding pair of parenthesis
            index = find_delimitor_pair(tokens, start, end, DEL_OPEN_ARRAY, DEL_CLOSE_ARRAY);
            if (index == 0) // An error has occured
                return err_prog_n(UNDEF_ERR, ERR_INFO);
            if (index == start) // No corresponding pair of parenthesis have been found
                return err_c15(data, false, tok->file, tok->y, "Parser", "No closing array accessor have been found", tok->line, tok->x + 1, tok->x + tok->size, false);

            // Recursive call for each argument of the parenthesis -> (v, v, ...)
            if (!is_value(data, tokens, start + 1, index - 1))
                return err_c15(data, false, tok->file, tok->y, "Parser", "Invalid value found during the check of the call arguments", tok->line, tok->x + 1, tok->x + tok->size, false);
            
            i = index;
        }

        // Check the next token
        else if (!is_next_tok_valid(data, tok, next_tok))
            return false;
    }

    return true;
}
