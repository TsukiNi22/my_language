/**************************************************************\

 ██╗  ██╗ █████╗ ██████╗ ████████╗ █████╗ ███╗   ██╗██╗ █████╗ 
 ╚██╗██╔╝██╔══██╗██╔══██╗╚══██╔══╝██╔══██╗████╗  ██║██║██╔══██╗
  ╚███╔╝ ███████║██████╔╝   ██║   ███████║██╔██╗ ██║██║███████║
  ██╔██╗ ██╔══██║██╔══██╗   ██║   ██╔══██║██║╚██╗██║██║██╔══██║
 ██╔╝ ██╗██║  ██║██║  ██║   ██║   ██║  ██║██║ ╚████║██║██║  ██║
 ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝

Edition:
##  14/04/2025 by Tsukini

File Name:
##  kamion.c

File Description:
## Main file of the compiler,
## init all the uninitialized data and check the falg '-' | '--'
## and call each part of the compiler
\**************************************************************/

#include "kamion.h" // compiler_t type
#include "error.h"  // error handling

/* Main compiler function
----------------------------------------------------------------
 * Init uninitialized data in the main structure,
 * setup the option and other thing related to the flags
 * Call each of the part of the compiler and check the return
----------------------------------------------------------------
##  argc -> number of argument given to the binary
##  argv -> arguments given to the binary
##  data -> main data structure
----------------------------------------------------------------
*/
int kamion(int const argc, char const *argv[], compiler_t *data)
{
    // Check for potential null pointer
    if (!data || !argv)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    
    // Init uninitialized var in the main structure
    if (init_data(data) == KO)
        return err_custom("Data initialisation error", FATAL_ERR, ERR_INFO);
    // Init var related to the flag '-' or '--'
    if (init_flag(data, argc, argv) == KO)
        return err_custom("Flag initialisation error", KO, ERR_INFO);

    // Exit in case of a '-h' or '--help'
    if (data->help)
        return OK;
    return OK;
}
