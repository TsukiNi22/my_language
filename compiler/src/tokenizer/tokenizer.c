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
##  tokenizer.c

File Description:
## Main file of the tokenizer
\**************************************************************/

#include "hashtable.h"  // hashtable_t type
#include "array.h"      // array_t type
#include "memory.h"     // my_strndup type
#include "tokenizer.h"  // tokenizer functions
#include "kamion.h"     // compiler_t type
#include "error.h"      // error handling
#include <stdio.h>      // file handling functions
#include <stdlib.h>     // malloc, free functions
#include <stddef.h>     // size_t type, NULL define
#include <stdbool.h>    // bool type

// Extract the token of the given line
int extract_token(compiler_t *data, hashtable_t *id, array_t *tokens, char const *file, char const *line, int n)
{
    token_t *tok = NULL;
    char *tok_start = NULL;
    bool valid = false;
    size_t size = 0;

    // Check for potential null pointer
    if (!data || !id || !tokens || !file || !line)
        return err_prog(PTR_ERR, KO, ERR_INFO);

    // Loop while we havn't check every token until the last char
    for (int i = 0; line[i];) {
        tok_start = (char *) &line[i];
        valid = false;
        tok = malloc(sizeof(token_t));
        if (!tok)
            return err_prog(MALLOC_ERR, KO, ERR_INFO);

        for (size = 1; tok_start[size - 1]; size++) {
            if (is_key_word(tok, my_strndup(tok_start, size))
                || is_flow_controler(tok, my_strndup(tok_start, size))
                || is_type(tok, my_strndup(tok_start, size))
                || is_operator(tok, my_strndup(tok_start, size))
                || is_delimitor(tok, my_strndup(tok_start, size))
                || is_identifier(tok, my_strndup(tok_start, size))
                || is_literal(tok, my_strndup(tok_start, size))) {
                valid = true;
            } else if (valid)
                break;
        }
        if (!valid) {
            free(tok);
            return err_c15(data, KO, file, n, "Tokenizer", "Can't identify this", line, i + 1, i + size, false);
        } else if (add_array(tokens, tok) == KO)
            return err_prog(UNDEF_ERR, KO, ERR_INFO);
        i += size;
    }
    return OK;
}

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
    array_t *tokens = NULL;
    FILE *fs = NULL;
    char *line= NULL;
    int res = 0;

    // Check for potential null pointer
    if (!data || !id || !file)
        return err_prog_n(PTR_ERR, ERR_INFO);
    
    data->comment = false;

    // Init the token array
    tokens = new_array();
    if (!tokens)
        return err_prog_n(UNDEF_ERR, ERR_INFO);

    // Set the stream for the file to tokenize
    fs = fopen(file, "r");
    if (!fs)
        return err_prog_n(UNDEF_ERR, ERR_INFO);

    // For each line in the file extract token
    for (int n = 1; (res = getline(&line, &(size_t){0}, fs)) != KO; n++) {
        line[res - 1] = '\0';
        if (extract_token(data, id, tokens, file, line, n) == KO)
            return err_prog_n(UNDEF_ERR, ERR_INFO);
    }

    fclose(fs);
    free(line);
    return tokens;
}
