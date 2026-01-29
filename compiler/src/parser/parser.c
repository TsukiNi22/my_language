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
##  parser.c

File Description:
##  Main file of the parser, dispatch to other parser function
##  to determine if the file is in the order of the syntax
\**************************************************************/

#include "array.h"      // array_t type
#include "parser.h"     // parser functions
#include "token.h"      // token enum
#include "tokenizer.h"  // token_t type
#include "kamion.h"     // compiler_t type, free_ptr function
#include "error.h"      // error handling
#include <stdbool.h>    // bool type
#include <stddef.h>     // size_t type, NULL define

/* Parser function
----------------------------------------------------------------
 * Check the organisation of the token of a file
----------------------------------------------------------------
##  data -> main data structure
##  tokens -> array of the file tokens
----------------------------------------------------------------
*/
int parser(compiler_t *data, array_t *tokens)
{
    token_t *tok, *tok_tmp = NULL;
    bool found = false;
    size_t start_adv = 0;
    size_t j = 0;
    
    // Check for potential null pointer
    if (!data || !tokens)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    
    /*
     ***************
     * instruction *
     ***************
     [flowcontroller|keyword|initialisation_var|attribution|call|identifier++identifier|identifier--identifier];
     * flowcontroller;          | More information in the next comment
     * keyword;                 | More information in the next comment
     * initialisation_var;      | More information in the next comment
     * attribution;             | More information in the next comment
     * call;                    | More information in the next comment
     * identifier++identifier;  | IDENTIFIERS OP_INC IDENTIFIERS
     * identifier--identifier;  | IDENTIFIERS OP_DEC IDENTIFIERS
    */

    /*
     *********
     * start *
     *********
     * (from)           from    | KW_FROM
     * (set)            set     | KW_DEFINE
     * (init var)       type    | TYPE IDENTIFIERS OPERATOR
     * (init func)      none    | KW_NONE
     * (init func)      type    | TYPE IDENTIFIERS DEL_OPEN_PARENTHESIS
     * (comment)        @>*<@   | LIT_COMMENT
    */

    // dispatch for the different possible start in a file
    start_adv = data->actual_adv;
    for (size_t i = 0; i < tokens->len; i++) {
        data->actual_adv = start_adv + i;
        tok = tokens->data[i];

        if (tok->type == KEY_WORD && tok->id == KW_FROM) {
            // from instruction
        } else if (tok->type == KEY_WORD && tok->id == KW_DEFINE) {
            // set instruction
        } else if (tok->type == KEY_WORD && tok->id == KW_NONE) {
            // init func with none
        } else if (tok->type == LITERAL && tok->id == LIT_COMMENT) {
            // comment first version '@>...<@' (skiped)
        } else if (tok->type == DELIMITOR && tok->id == DEL_COMMENT) {
            // comment second version '@...' (skiped)
            tok_tmp = tokens->data[++i];
            if (!(tok_tmp->type == LITERAL && tok_tmp->id == LIT_COMMENT))
                return err_c15(data, false, tok->file, tok->y, "Parser", "No corresponding comment found for this declaration of comment", tok->line, tok->x + 1, tok->x + tok->size, false);
        } else if (tok->type == TYPE) {
            // init func or init var
            
            // find the end IDENTIFIERS before the '=' or ';' for the var declaration
            found = false;
            for (j = i; !found && j < tokens->len; j++) {
                tok_tmp = tokens->data[j];
                if ((tok_tmp->type == OPERATOR && tok_tmp->id == OP_EQ) || (tok_tmp->type == DELIMITOR && tok_tmp->id == DEL_EXPRESSION_END))
                    found = true;
            }
            
            // no corresponding identifiers found
            if (!found)
                return err_c15(data, false, tok->file, tok->y, "Parser", "No corresponding identifier found for this declaration", tok->line, tok->x + 1, tok->x + tok->size, false);
            
            // check if it's a valid type
            if (!is_type(data, tokens, i, j - 2))
                break;

        } else {
            // unknow line start
            return err_c15(data, false, tok->file, tok->y, "Parser", "Invalid start of instruction outside of a function", tok->line, tok->x + 1, tok->x + tok->size, false);
        }
    }

    data->actual_adv = start_adv + tokens->len;
    if (data->adv_dump && advencement_dump(data) == KO)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    
    return OK;
}
