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
#include "memory.h"     // my_strdup functions
#include "array.h"      // array functions
#include "token.h"      // array functions
#include "kamion.h"     // compiler_t type
#include "error.h"      // error handling
#include <stdlib.h>     // malloc function
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
    token_id_t *id = NULL;

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

    // Init hashtable element for token id
    for (int i = 0; token_str[i]; i++) {
        id = malloc(sizeof(token_id_t));
        if (!id)
            return err_prog(MALLOC_ERR, KO, ERR_INFO);
        *id = i;
        if (ht_insert(data->id, my_strdup(token_str[i]), id, &free_hash_data_str) == KO)
            return err_prog(UNDEF_ERR, KO, ERR_INFO);
    }
    return OK;
}
