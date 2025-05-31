/**************************************************************\

 ██╗  ██╗ █████╗ ██████╗ ████████╗ █████╗ ███╗   ██╗██╗ █████╗ 
 ╚██╗██╔╝██╔══██╗██╔══██╗╚══██╔══╝██╔══██╗████╗  ██║██║██╔══██╗
  ╚███╔╝ ███████║██████╔╝   ██║   ███████║██╔██╗ ██║██║███████║
  ██╔██╗ ██╔══██║██╔══██╗   ██║   ██╔══██║██║╚██╗██║██║██╔══██║
 ██╔╝ ██╗██║  ██║██║  ██║   ██║   ██║  ██║██║ ╚████║██║██║  ██║
 ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝

Edition:
##  31/05/2025 by Tsukini

File Name:
##  kamion.c

File Description:
## Main file of the compiler,
## init all the uninitialized data and check the falg '-' | '--'
## and call each part of the compiler
\**************************************************************/

#include "define.h"     // STDOUT define
#include "my_string.h"  // get_fullpath, my_strcmp function
#include "hashtable.h"  // hashatble functions
#include "write.h"      // my_printf functions
#include "array.h"      // array_t type
#include "memory.h"     // my_strdup function
#include "tokenizer.h"  // tokenizer type
#include "kamion.h"     // compiler_t type
#include "error.h"      // error handling
#include <stddef.h>     // NULL define

// Add the file given directly to the list
static int direct_file(compiler_t *data, int const argc, char const *argv[])
{
    char *ptr = NULL;

    // Check for potential null pointer
    if (!data || !argv)
        return err_prog(PTR_ERR, KO, ERR_INFO);

    for (int i = 1; i < argc; i++) {
        // End of the normal file definition
        if (argv[i][0] == '-')
            break;

        // Check if the file end with the right extension
        ptr = NULL;
        for (int j = 0; argv[i][j]; j++) {
            if (argv[i][j] == '.')
                ptr = (char *) &argv[i][j];
        }
        if (my_strcmp(ptr, FILE_EXTENSION) != 0 && my_strcmp(ptr, HEADER_EXTENSION) != 0) {
            err_kmc_arg(data, OK, "Argument", "Invalid extension, won't be taken in the compilation", argv[i], NULL, true);
            continue;
        }
    
        // Set the file in the array
        if (is_valid_file(data, argv[i], false) && add_array(data->files, my_strdup((char *) argv[i])) == KO)
            return err_prog(UNDEF_ERR, KO, ERR_INFO);
    }
    return OK;
}

// Try to tokenize every file found
static int tokenize_files(compiler_t *data)
{
    array_t *tokens = NULL;
    int res = OK;

    // Check for potential null pointer
    if (!data)
        return err_prog(PTR_ERR, KO, ERR_INFO);

    // For every given file
    for (size_t i = 0; i < data->files->len; i++) {
        tokens = tokenizer(data, data->id, data->files->data[i]);
        if (!tokens)
            return err_custom("Tokenizer error", KO, ERR_INFO);
        if (tokens->len == 0) {
            data->nb_warning++;
            res += my_printf("%O%C%S[Warging n°%d]%R %S%s:%u:%u%R -> %s: %s%R\n",
            STDOUT, 175, 0, 175, data->nb_warning, data->files->data[i], 1, 1,
            "File", "Empty file, won't be taken in the compilation");
            res += delete_array(&tokens, &free_token);
            if (res != OK)
                return err_prog(UNDEF_ERR, KO, ERR_INFO);
            continue;
        }
        if (ht_insert(data->tokens, my_strdup(data->files->data[i]), tokens, &free_hash_data_str) == KO)
            return err_prog(UNDEF_ERR, KO, ERR_INFO);
    }
    return OK;
}

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
    
    // Init the main structure & given arguments
    if (init_data(data) == KO)
        return err_custom("Data initialisation error", FATAL_ERR, ERR_INFO);
    if (init_flag(data, argc, argv) == KO)
        return err_custom("Flag initialisation error", KO, ERR_INFO);
    if (direct_file(data, argc, argv) == KO)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);

    // Exit in case of a '-h' or '--help'
    if (data->help)
        return OK;

    // Execption
    if (data->files->len == 0)
        return err_kmc_arg(data, KO, "File", "No valid file found for the compilation", NULL, NULL, false);

    // Tokenization
    if (tokenize_files(data) == KO)
        return err_custom("Tokenization error", KO, ERR_INFO);
    if (data->tok_dump)
        return tokens_dump(data->tokens);
    
    return OK;
}
