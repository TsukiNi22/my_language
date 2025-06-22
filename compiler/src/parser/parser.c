/**************************************************************\

 ██╗  ██╗ █████╗ ██████╗ ████████╗ █████╗ ███╗   ██╗██╗ █████╗ 
 ╚██╗██╔╝██╔══██╗██╔══██╗╚══██╔══╝██╔══██╗████╗  ██║██║██╔══██╗
  ╚███╔╝ ███████║██████╔╝   ██║   ███████║██╔██╗ ██║██║███████║
  ██╔██╗ ██╔══██║██╔══██╗   ██║   ██╔══██║██║╚██╗██║██║██╔══██║
 ██╔╝ ██╗██║  ██║██║  ██║   ██║   ██║  ██║██║ ╚████║██║██║  ██║
 ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝

Edition:
##  22/06/2025 by Tsukini

File Name:
##  parser.c

File Description:
##  Main file of the parser, dispatch to other parser function
##  to determine if the file is in the order of the syntax
\**************************************************************/

#include "array.h"      // array_t type
#include "parser.h"     // parser functions
#include "kamion.h"     // compiler_t type, free_ptr function
#include "error.h"      // error handling
#include <stddef.h>     // size_t type

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
    // Check for potential null pointer
    if (!data || !tokens)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    
    // Skip comment: @error@ @ comment

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
     * (from)       from    | KW_FROM
     * (set)        set     | KW_SET
     * (init var)   type    | TYPE IDENTIFIERS OPERATOR
     * (init func)  none    | KW_NONE
     * (init func)  type    | TYPE IDENTIFIERS DEL_OPEN_PARENTHESIS
    */

    if (data->adv_dump && advencement_dump(data) == KO)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    
    return OK;
}
