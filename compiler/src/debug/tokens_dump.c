/**************************************************************\

 ██╗  ██╗ █████╗ ██████╗ ████████╗ █████╗ ███╗   ██╗██╗ █████╗ 
 ╚██╗██╔╝██╔══██╗██╔══██╗╚══██╔══╝██╔══██╗████╗  ██║██║██╔══██╗
  ╚███╔╝ ███████║██████╔╝   ██║   ███████║██╔██╗ ██║██║███████║
  ██╔██╗ ██╔══██║██╔══██╗   ██║   ██╔══██║██║╚██╗██║██║██╔══██║
 ██╔╝ ██╗██║  ██║██║  ██║   ██║   ██║  ██║██║ ╚████║██║██║  ██║
 ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝

Edition:
##  18/04/2025 by Tsukini

File Name:
##  tokens_dump.c

File Description:
##  display tokens found
\**************************************************************/

#include "hashtable.h"  // hashtable_t type + functions
#include "write.h"      // writing function
#include "tokenizer.h"  // token_t type
#include "token.h"      // token defines
#include "error.h"      // error handling

static char *type_str[] = {
    "Delimitor",
    "Operator",
    "Type",
    "Flow Controler",
    "Key Word",
    "Literal",
    "Identifier",
};

static char *lit_str[] = {
    "Comment",
    "Char",
    "String",
    "Bool",
    "Binary",
    "Octal",
    "Hexa",
    "Decimal",
    "Float",
};

static int display_token(void *ptr)
{
    token_t *tok = ptr;

    // Check for potential null pointer
    if (!ptr)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    if (tok->id != KO && tok->id <= MAX_KW)
        return my_printf("\t|%-14s|\t|%-8s|\t|%u|\t|%d|\t|%u|\t|%s|\n",
        type_str[tok->type], token_str[tok->id], tok->y, tok->x, tok->size, tok->value);
    if (tok->id > MAX_KW)
        return my_printf("\t|%-14s|\t|%-8s|\t|%u|\t|%d|\t|%u|\t|%s|\n",
        type_str[tok->type], lit_str[tok->id - (MAX_KW + 1)], tok->y, tok->x, tok->size, tok->value);
    return my_printf("\t|%-14s|\t|%-8s|\t|%u|\t|%d|\t|%u|\t|%s|\n",
    type_str[tok->type], NULL, tok->y, tok->x, tok->size, tok->value);
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
    int res = OK;

    // Check for potential null pointer
    if (!tokens)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    
    // Get all keys (file name) of the hashtable
    keys = ht_keys(tokens);
    if (!keys)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);

    for (int i = 0; res == OK && keys[i]; i++) {
        res += my_printf("Tokens File: %S%s%R\n", keys[i]);
        res += my_putstr(STDOUT, "--------------------------------------------------------------------------------\n");
        res += my_putstr(STDOUT, "|n°|\t|type          |\t|id      |\t|line|\t|start|\t|size|\t|value|\n");
        res += my_putstr(STDOUT, "--------------------------------------------------------------------------------\n");
        if (array_dump(ht_search(tokens, keys[i]), &display_token) == KO)
            return err_prog(UNDEF_ERR, KO, ERR_INFO);
        if (keys[i + 1])
            res += my_putchar(STDOUT, '\n');
    }
    if (res != OK)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    return free_hash_keys(keys);
}
