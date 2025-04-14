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
##  tokenizer.c

File Description:
## Main file of the tokenizer
\**************************************************************/

#include "hashtable.h"  // hashtable_t type
#include "array.h"      // array_t type
#include "tokenizer.h"  // tokenizer functions
#include "error.h"      // error handling
#include <stddef.h>     // NULL define

/* Main tokenizer function
----------------------------------------------------------------
 *  
----------------------------------------------------------------
##  id -> all the possible token as: key=strings | value=id
##  file -> file to get the tokens
----------------------------------------------------------------
##  return -> a list of all the token found in the given file
----------------------------------------------------------------
*/
array_t *tokenizer(hashtable_t *id, char const *file)
{
    // Check for potential null pointer
    if (!id || !file)
        return err_prog_n(PTR_ERR, ERR_INFO);
    return NULL;
}
