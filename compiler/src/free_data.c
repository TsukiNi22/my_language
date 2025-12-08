/**************************************************************\

 ██╗  ██╗ █████╗ ██████╗ ████████╗ █████╗ ███╗   ██╗██╗ █████╗ 
 ╚██╗██╔╝██╔══██╗██╔══██╗╚══██╔══╝██╔══██╗████╗  ██║██║██╔══██╗
  ╚███╔╝ ███████║██████╔╝   ██║   ███████║██╔██╗ ██║██║███████║
  ██╔██╗ ██╔══██║██╔══██╗   ██║   ██╔══██║██║╚██╗██║██║██╔══██║
 ██╔╝ ██╗██║  ██║██║  ██║   ██║   ██║  ██║██║ ╚████║██║██║  ██║
 ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝

Edition:
##  01/08/2025 by Tsukini

File Name:
##  free_data.c

File Description:
## Free any malloced memory during the compilation
\**************************************************************/

#include "hashtable.h"  // free hashtable functions
#include "array.h"      // free array functions
#include "tokenizer.h"  // token_t type
#include "kamion.h"     // compiler_t type
#include "error.h"      // error handling
#include <pcre.h>       // regex free function
#include <stdlib.h>     // free function

/* Token free function
----------------------------------------------------------------
 * Free the dynamic array for the token
----------------------------------------------------------------
##  ptr -> pointer to a thing to free
----------------------------------------------------------------
*/
int free_token(void *ptr)
{
    token_t *token = ptr;

    // Check for potential null pointer
    if (!ptr)
        return err_prog(PTR_ERR, KO, ERR_INFO);

    if (token->file)
        free(token->file);
    if (token->line)
        free(token->line);
    if (token->value)
        free(token->value);
    free(token);
    return OK;
}

// Free hash for str + tokens array
static int free_hash_tokens(void *ptr)
{
    hash_linked_data_t *ht_data = ptr;
    int res = OK;

    // Check for potential null pointer
    if (!ptr)
        return err_prog(PTR_ERR, KO, ERR_INFO);

    free(ht_data->key);
    res = delete_array((array_t **) &ht_data->value, &free_token);
    free(ht_data);
    return res;
}

// Free simple pointer
static int free_ptr(void *ptr)
{
    // Check for potential null pointer
    if (!ptr)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    free(ptr);
    return OK;
}

// Free regex
static int free_regex(compiler_t *data)
{
    // Check for potential null pointer
    if (!data)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    for (int i = 0; i < REGEX_NUMBER; i++) {
        pcre_free(data->regex[i]);
        if (data->study[i])
            pcre_free_study(data->study[i]);
    }
    return OK;
}

/* Free data function
----------------------------------------------------------------
 * Free the var in the main structure who was malloced
 * during the compilation
----------------------------------------------------------------
##  data -> main data structure
----------------------------------------------------------------
*/
int free_data(compiler_t *data)
{
    int res = OK;

    // Check for potential null pointer
    if (!data)
        return err_prog(PTR_ERR, KO, ERR_INFO);

    res += delete_hashtable(data->id, &free_hash_data_str);
    res += delete_hashtable(data->tokens, &free_hash_tokens);
    res += delete_array(&data->files, &free_ptr);
    res += free_regex(data);
    if (res != OK)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    return OK;
}
