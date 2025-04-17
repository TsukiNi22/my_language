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
##  tokens_dump.c

File Description:
##  display tokens found
\**************************************************************/

#include "hashtable.h"  // hashtable_t type + functions
#include "write.h"      // writing function
#include "tokenizer.h"  // token_t type
#include "error.h"      // error handling

static int display_token(void *ptr)
{
    token_t *tok = ptr;

    // Check for potential null pointer
    if (!ptr)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    return my_printf(" \t|%d| \t|%d| \t|%u| \t|%d| \t|%u| \t|%s|\n",
    tok->type, tok->id, tok->y, tok->x, tok->size, tok->value);
}

/* Tokens Dump for debug
----------------------------------------------------------------
 * A debuging function to display the tokens for each file
----------------------------------------------------------------
##  tokens -> an hashtable with the tokens for each file
----------------------------------------------------------------
*/
int tokens_dump(hashtable_t *tokens)
{
    char **keys = NULL;

    // Check for potential null pointer
    if (!tokens)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    
    // Get all keys (file name) of the hashtable
    keys = ht_keys(tokens);
    if (!keys)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);

    for (int i = 0; keys[i]; i++) {
        my_printf("Tokens File: %S%s%R\n", keys[i]);
        my_putstr(STDOUT, "-----------------------------------------------------------------\n");
        my_putstr(STDOUT, "|n°|\t|type|\t|id|\t|line|\t|start|\t|size|\t|value|\n");
        my_putstr(STDOUT, "-----------------------------------------------------------------\n");
        if (array_dump(ht_search(tokens, keys[i]), &display_token) == KO)
            return err_prog(UNDEF_ERR, KO, ERR_INFO);
    }
    return free_hash_keys(keys);
}
