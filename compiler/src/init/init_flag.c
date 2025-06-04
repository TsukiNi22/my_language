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
##  init_flag.c

File Description:
##  You know, I don t think there are good or bad descriptions,
##  for me, life is all about functions...
\**************************************************************/

#include "memory.h"     // clone str function
#include "kamion.h"     // compiler_t type
#include "error.h"      // error handling
#include <string.h>     // strcmp function
#include <stddef.h>     // NULL define
#include <stdbool.h>    // bool type

// Function for dispatch call of flag with '--'
static int full_flag(compiler_t *data, int const argc, char const *argv[], int const i)
{
    // Check for potential null pointer
    if (!data || !argv)
        return err_prog(PTR_ERR, KO, ERR_INFO);

    // For each know flag with '--'
    for (int j = 0; full_flags[j]; j++) {
        // If the argument is a know flag, call the corresponding function
        if (strcmp(argv[i], full_flags[j]) == 0)
            return flag_functions[j](data, argc - i, &(argv[i]));
    }

    // Error handling for unknow flag with '--'
    return err_kmc_arg(data, KO, &argv[i][2], "Unrecognized option", argv[i], NULL, false);
}

// Detect if the given char in a flag
static int is_flag_char(char const c, int *index)
{
    // Check for potential null pointer
    if (!index)
        return err_prog(PTR_ERR, false, ERR_INFO);

    // Check if the given char is a flag and set the index to the falg index
    for (int i = 0; flags[i]; i++) {
        if (c == flags[i]) {
            *index = i;
            return true;
        }
    }
    return false;
}

// Function for dispatch call of flag with '-'
static int flag(compiler_t *data, int const argc, char const *argv[], int const i)
{
    int index = 0;

    // Check for potential null pointer
    if (!data || !argv)
        return err_prog(PTR_ERR, KO, ERR_INFO);

    // For each argument in argv
    for (int j = 1; argv[i][j]; j++) {
        // Error handling for unknow flag
        if (!is_flag_char(argv[i][j], &index))
            return err_kmc_arg(data, KO, my_strndup(&argv[i][j], 1), "Unrecognized option", argv[i], NULL, false);
        // Error handling for flag that can't can be with other in the same '-'
        if (flags_argc[index] != 0 && (j > 1 || argv[i][j + 1]))
            return err_kmc_arg(data, KO, my_strndup(&argv[i][j], 1), "Can't be combined with other", argv[i], NULL, false);
        // Call of the function of the flag to set the var in the structure
        if (flag_functions[index](data, argc - i, &(argv[i])) == KO)
            return err_prog(UNDEF_ERR, KO, ERR_INFO);
    }
    return OK;
}

/* Flag initialisation function
----------------------------------------------------------------
 * Check each argument for any know flag in '-' and '--'
 * Call function depending on the flag found
----------------------------------------------------------------
##  data -> main data structure
##  argc -> number of argument given to the binary
##  argv -> arguments given to the binary
----------------------------------------------------------------
*/
int init_flag(compiler_t *data, int const argc, char const *argv[])
{
    // Check for potential null pointer
    if (!data || !argv)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    
    // Check to find an '-h' or '--help'
    for (int i = 0; i < argc; i++) {
        if ((argv[i][0] == '-' && argv[i][1] == flags[0] && !argv[i][2]) || strcmp(argv[i], full_flags[0]) == 0) {
            data->help = true;
            return flag_help();
        }
    }

    // Check for each flag '-' and '--'
    for (int i = 0; i < argc; i++) {
        if (argv[i][0] != '-')
            continue;
        if (argv[i][1] == '-' && argv[i][2] && full_flag(data, argc, argv, i) == KO)
            return err_prog(UNDEF_ERR, KO, ERR_INFO);
        if (argv[i][1] != '-' && argv[i][1] && flag(data, argc, argv, i) == KO)
            return err_prog(UNDEF_ERR, KO, ERR_INFO);
    }
    return OK;
}
