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
##  init_global.c

File Description:
## Initialisation of global var
\**************************************************************/

#include "hashtable.h"  // hashtable functions
#include "array.h"      // array functions
#include "kamion.h"     // compiler_t type
#include "error.h"      // error handling
#include <stdbool.h>    // bool type

/* Global initialisation function
----------------------------------------------------------------
 * Initialisation of var that will be used in every file
----------------------------------------------------------------
##  data -> main data structure
----------------------------------------------------------------
*/
int init_global(compiler_t *data)
{
    // Check for potential null pointer
    if (!data)
        return err_prog(PTR_ERR, KO, ERR_INFO);

    // Init hashtable
    data->id = new_hashtable(&hash, DEFAULT_HASH_SIZE);
    data->tokens = new_hashtable(&hash, DEFAULT_HASH_SIZE);
    if (!data->id || !data->tokens)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);

    // Init array for File information
    data->files = new_array();
    if (!data->files)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    return OK;
}
