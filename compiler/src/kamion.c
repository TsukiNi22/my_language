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

#include "hashtable.h"  // hashatble functions
#include "array.h"      // array_t type
#include "memory.h"     // my_strdup function
#include "tokenizer.h"  // tokenizer type
#include "kamion.h"     // compiler_t type
#include "error.h"      // error handling
#include <stddef.h>     // NULL define

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
    array_t *tokens = NULL;

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

    // Execption
    if (data->files->len == 0)
        return err_kmc_arg(data, KO, "File", "No given file or no file found in given directory", NULL, NULL, false);

    // Tokenize every file found
    for (size_t i = 0; i < data->files->len; i++) {
        tokens = tokenizer(data->id, data->files->data[i], &data->err_sys);
        if (!tokens)
            return err_custom("Tokenizer error", KO, ERR_INFO);
        if (ht_insert(data->tokens, my_strdup(data->files->data[i]), tokens, &free_hash_data_str) == KO)
            return err_prog(UNDEF_ERR, KO, ERR_INFO);
    }
    return OK;
}
