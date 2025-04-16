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
#include "kamion.h"     // compiler_t type
#include "error.h"      // error handling
#include <stdio.h>      // file handling functions
#include <stdlib.h>     // free function
#include <stddef.h>     // NULL define
#include <stdbool.h>    // bool type

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
array_t *tokenizer(compiler_t *data, hashtable_t *id, char const *file)
{
    FILE *fs = NULL;
    char *line= NULL;
    int res = 0;

    // Check for potential null pointer
    if (!data || !id || !file)
        return err_prog_n(PTR_ERR, ERR_INFO);

    // Set the stream for the file to tokenize
    fs = fopen(file, "r");
    if (!fs)
        return err_prog_n(UNDEF_ERR, ERR_INFO);

    // For each line in the file extract token
    while ((res = getline(&line, &(size_t){0}, fs)) != KO) {
        line[res - 1] = '\0';
        // ...
    }

    fclose(fs);
    free(line);
    return NULL;
}
