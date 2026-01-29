/**************************************************************\

 ██╗  ██╗ █████╗ ██████╗ ████████╗ █████╗ ███╗   ██╗██╗ █████╗ 
 ╚██╗██╔╝██╔══██╗██╔══██╗╚══██╔══╝██╔══██╗████╗  ██║██║██╔══██╗
  ╚███╔╝ ███████║██████╔╝   ██║   ███████║██╔██╗ ██║██║███████║
  ██╔██╗ ██╔══██║██╔══██╗   ██║   ██╔══██║██║╚██╗██║██║██╔══██║
 ██╔╝ ██╗██║  ██║██║  ██║   ██║   ██║  ██║██║ ╚████║██║██║  ██║
 ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝

Edition:
##  29/01/2026 by Tsukini

File Name:
##  is_valid_file.c

File Description:
## Check if the given path is a valid file
\**************************************************************/

#include "kamion.h"     // compiler_t type
#include "tokenizer.h"  // token_t type
#include "array.h"      // array_t type
#include "error.h"      // error handling

/* Get the size of multiple tokens
----------------------------------------------------------------
 * Calcul the size of multiple tokens
 * between tow given bounds
----------------------------------------------------------------
##  tokens -> List of the tokens
##  start -> Start bound
##  end -> End bound
----------------------------------------------------------------
*/
size_t get_toks_size(array_t *tokens, size_t start, size_t end)
{
    token_t *tok = NULL;
    size_t y, x = 0;
    size_t i = 0;

    // Check for potential null pointer
    if (!tokens)
        return err_prog(PTR_ERR, 0, ERR_INFO);

    tok = tokens->data[start];
    x = tok->x;
    y = tok->y;
    for (i = start; ((token_t *) tokens->data[i])->y == y && i <= end; i++);
    tok = tokens->data[i - 1];
    return (tok->x - x) + tok->size;
}
