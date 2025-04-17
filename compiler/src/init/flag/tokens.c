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
##  tokens.c

File Description:
## Handle the tokens flag option
\**************************************************************/

#include "macro.h"      // UNUSED macro
#include "kamion.h"     // compiler_t type
#include "error.h"      // error handling
#include <stdbool.h>    // bool type

/* Errors function
----------------------------------------------------------------
 * This function will set the option show tokens at end to true
----------------------------------------------------------------
##  data -> main data structure
##  argc -> number of argument given to the binary
##  argv -> arguments given to the binary
----------------------------------------------------------------
*/
int flag_tokens(compiler_t *data, UNUSED int const argc, char const *argv[])
{
    // Check for potential null pointer
    if (!data || !argv)
        return err_prog(PTR_ERR, KO, ERR_INFO);

    // If the option have already been writed
    if (data->tok_dump)
        return err_kmc_arg(data, OK, "Option", "Duplicated option", *argv, NULL, true);

    // Set the option to true
    data->tok_dump = true;
    return OK;
}
