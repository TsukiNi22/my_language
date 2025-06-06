/**************************************************************\

 ██╗  ██╗ █████╗ ██████╗ ████████╗ █████╗ ███╗   ██╗██╗ █████╗ 
 ╚██╗██╔╝██╔══██╗██╔══██╗╚══██╔══╝██╔══██╗████╗  ██║██║██╔══██╗
  ╚███╔╝ ███████║██████╔╝   ██║   ███████║██╔██╗ ██║██║███████║
  ██╔██╗ ██╔══██║██╔══██╗   ██║   ██╔══██║██║╚██╗██║██║██╔══██║
 ██╔╝ ██╗██║  ██║██║  ██║   ██║   ██║  ██║██║ ╚████║██║██║  ██║
 ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝

Edition:
##  01/06/2025 by Tsukini

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
    data->adv_dump = false; // Show advencement
    data->actual_adv = 0;
    data->total_adv = 0;
    data->errors = false; // Show errors at the end
    data->binary = BINARY_NAME; // Ouput binary name

    // Set Duplicated option
    data->d_binary = false;
    data->d_errors = false;
    data->d_tok_dump = false;
    data->d_adv_dump = false;
    return OK;
}
