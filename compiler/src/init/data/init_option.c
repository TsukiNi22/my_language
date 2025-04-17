/**************************************************************\

 ██╗  ██╗ █████╗ ██████╗ ████████╗ █████╗ ███╗   ██╗██╗ █████╗ 
 ╚██╗██╔╝██╔══██╗██╔══██╗╚══██╔══╝██╔══██╗████╗  ██║██║██╔══██╗
  ╚███╔╝ ███████║██████╔╝   ██║   ███████║██╔██╗ ██║██║███████║
  ██╔██╗ ██╔══██║██╔══██╗   ██║   ██╔══██║██║╚██╗██║██║██╔══██║
 ██╔╝ ██╗██║  ██║██║  ██║   ██║   ██║  ██║██║ ╚████║██║██║  ██║
 ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝

Edition:
##  17/04/2025 by Tsukini

File Name:
##  init_option.c

File Description:
## Initialisation of var used in option
\**************************************************************/

#include "kamion.h"     // compiler_t type
#include "error.h"      // error handling
#include <stddef.h>     // NULL define
#include <stdbool.h>    // bool type

/* Option initialisation function
----------------------------------------------------------------
 * Initialisation of var that will be used in option for flag
----------------------------------------------------------------
##  data -> main data structure
----------------------------------------------------------------
*/
int init_option(compiler_t *data)
{
    // Check for potential null pointer
    if (!data)
        return err_prog(PTR_ERR, KO, ERR_INFO);

    // Set to default value
    data->tok_dump = false; // Show tokens at the end
    data->errors = false; // Show errors at the end
    data->binary = NULL; // Ouput binary name
    data->d_binary = false;
    data->d_errors = false;
    data->d_tok_dump = false;
    return OK;
}
