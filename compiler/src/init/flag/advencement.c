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
##  advencement.c

File Description:
## Handle the advencement flag option
\**************************************************************/

#include "macro.h"      // UNUSED macro
#include "kamion.h"     // compiler_t type
#include "error.h"      // error handling
#include <stdbool.h>    // bool type

/* Errors function
----------------------------------------------------------------
 * This function will set the option show advencement to true
----------------------------------------------------------------
##  data -> main data structure
##  argc -> number of argument given to the binary
##  argv -> arguments given to the binary
----------------------------------------------------------------
*/
int flag_advencement(compiler_t *data, UNUSED int const argc, char const *argv[])
{
    // Check for potential null pointer
    if (!data || !argv)
        return err_prog(PTR_ERR, KO, ERR_INFO);

    // If the option have already been writed
    if (data->adv_dump && !data->d_adv_dump) {
        data->d_adv_dump = true;
        return err_kmc_arg(data, OK, "Option", "Duplicated option (only say one time)", *argv, NULL, true);
    }

    // Set the option to true
    data->adv_dump = true;
    return OK;
}
