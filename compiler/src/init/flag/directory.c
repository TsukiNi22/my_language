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
##  directory.c

File Description:
## Handle the directory flag option
\**************************************************************/

#include "kamion.h" // compiler_t type
#include "error.h"  // error handling

/* Directory function
----------------------------------------------------------------
 * That will extract the file in the given directory
 * and use them in the compilation
----------------------------------------------------------------
##  data -> main data structure
##  argc -> number of argument given to the binary
##  argv -> arguments given to the binary
----------------------------------------------------------------
*/
int flag_directory(compiler_t *data, int const argc, char const *argv[])
{
    // Check for potential null pointer
    if (!data || !argv)
        return err_prog(PTR_ERR, KO, ERR_INFO);

    // Check argument
    if (argc < 2 || argv[1][0] == '-')
        return err_kmc_arg(data, KO, "Argument", "Insufficient argument, need a 'directory_path'", *argv, "directory_path", false);
    if (!is_valid_dir(data, argv[1]))
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    return OK;
}
