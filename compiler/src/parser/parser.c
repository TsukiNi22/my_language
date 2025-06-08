/**************************************************************\

 ██╗  ██╗ █████╗ ██████╗ ████████╗ █████╗ ███╗   ██╗██╗ █████╗ 
 ╚██╗██╔╝██╔══██╗██╔══██╗╚══██╔══╝██╔══██╗████╗  ██║██║██╔══██╗
  ╚███╔╝ ███████║██████╔╝   ██║   ███████║██╔██╗ ██║██║███████║
  ██╔██╗ ██╔══██║██╔══██╗   ██║   ██╔══██║██║╚██╗██║██║██╔══██║
 ██╔╝ ██╗██║  ██║██║  ██║   ██║   ██║  ██║██║ ╚████║██║██║  ██║
 ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝

Edition:
##  08/06/2025 by Tsukini

File Name:
##  parser.c

File Description:
##  Main file of the parser, dispatch to other parser function
##  to determine if the file is in the order of the syntax
\**************************************************************/

#include "parser.h"     // parser functions
#include "kamion.h"     // compiler_t type, free_ptr function
#include "error.h"      // error handling
#include <stddef.h>     // size_t type

/* Parser function
----------------------------------------------------------------
 * Check the organisation of the token of a file
----------------------------------------------------------------
##  data -> main data structure
----------------------------------------------------------------
*/
int parser(compiler_t *data)
{
    // Check for potential null pointer
    if (!data)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    
    return OK;
}
