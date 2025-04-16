/**************************************************************\

 ██╗  ██╗ █████╗ ██████╗ ████████╗ █████╗ ███╗   ██╗██╗ █████╗ 
 ╚██╗██╔╝██╔══██╗██╔══██╗╚══██╔══╝██╔══██╗████╗  ██║██║██╔══██╗
  ╚███╔╝ ███████║██████╔╝   ██║   ███████║██╔██╗ ██║██║███████║
  ██╔██╗ ██╔══██║██╔══██╗   ██║   ██╔══██║██║╚██╗██║██║██╔══██║
 ██╔╝ ██╗██║  ██║██║  ██║   ██║   ██║  ██║██║ ╚████║██║██║  ██║
 ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝

Edition:
##  15/04/2025 by Tsukini

File Name:
##  Errors.c

File Description:
## Handle the Errors flag option
\**************************************************************/

#include "kamion.h"     // compiler_t type
#include "error.h"      // error handling
#include <stdbool.h>    // bool type

/* Errors function
----------------------------------------------------------------
 * This function will set the option show error at end to true
----------------------------------------------------------------
##  data -> main data structure
##  argc -> number of argument given to the binary
##  argv -> arguments given to the binary
----------------------------------------------------------------
*/
int flag_Errors(compiler_t *data, int const argc, char const *argv[])
{
    // Check for potential null pointer
    if (!data || !argv)
        return err_prog(PTR_ERR, KO, ERR_INFO);

    // If the option have already been writed
    if (data->errors)
        return err_kmc_arg(data, OK, "Option", "Duplicated option", *argv, NULL, true);

    // Set the option to true
    data->errors = true;
    return OK;
}
