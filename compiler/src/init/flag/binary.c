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
##  binary.c

File Description:
## Handle the binary flag option
\**************************************************************/

#include "kamion.h" // compiler_t type
#include "error.h"  // error handling

/* Binary function
----------------------------------------------------------------
 * That function will set the name of file created
----------------------------------------------------------------
##  data -> main data structure
##  argc -> number of argument given to the binary
##  argv -> arguments given to the binary
----------------------------------------------------------------
*/
int flag_binary(compiler_t *data, int const argc, char const *argv[])
{
    // Check for potential null pointer
    if (!data || !argv)
        return err_prog(PTR_ERR, KO, ERR_INFO);

    // Check argument
    if (argc < 2 || argv[1][0] == '-')
        return err_kmc_arg(data, KO, "Argument", "Insufficient argument, need a 'binary_name'", *argv, "binary_name", false);

    // If the option have already been writed
    if (data->binary && !data->d_binary) {
        data->d_binary = true;
        return err_kmc_arg(data, OK, "Option", "Duplicated option (only say one time)", *argv, NULL, true);
    }

    data->binary = argv[1];
    return OK;
}
