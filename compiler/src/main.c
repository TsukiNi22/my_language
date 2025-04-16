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
##  main.c

File Description:
## Launch file, initialisation of the principale structure,
## initialisation of some var of the main structure,
## and call of the compiler
\**************************************************************/

#include "kamion.h"     // compiler function, compiler_t type
#include "write.h"      // printf function
#include "error.h"      // error handling
#include <stdbool.h>    // boolean type

/* Main function
----------------------------------------------------------------
 * initialisation of the main structure
 * call of the compiler
 * check compiler function return return
----------------------------------------------------------------
##  argc -> number of argument given to the binary
##  argv -> arguments given to the binary
----------------------------------------------------------------
*/
int main(int const argc, char const *argv[])
{
    // Initialisation of the main structure and return ouput
    compiler_t data = {0};
    int res = 0;

    // Check for potential null pointer
    if (!argv)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    
    // Initialisation of the var used for error return and help
    data.exe_name = argv[0];
    data.help = false;
    data.err_sys = false;
    data.nb_error = 0;
    data.nb_warning = 0;

    err_c15(&data, KO, "file.c15", 6, "Tokenizer error", "Unknow token found", "i'm a line 'this is the error' yet", 13, 29, true);
    err_c15(&data, KO, "file.c15", 6, "Tokenizer error", "Unknow token found", "i'm a line 'this is the error' yet", 13, 29, false);
    return KO;

    // Call of the compiler and recuperation of the ouput
    res = kamion(argc, argv, &data);

    // Free data and return an error or a success depending on the ouput of the compiler
    if (res == KO || res == FATAL_ERR) {
        if (res != FATAL_ERR)
            free_data(&data);
        if (!data.err_sys)
            my_printf("%O%s: An error has occurred, execution has been interrupted.\n", STDERR, data.exe_name);
        return KO;
    }
    return free_data(&data);
}
