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
##  tokenizer.c

File Description:
## Main file of the tokenizer
\**************************************************************/

#include "hashtable.h"  // hashtable_t type
#include "array.h"      // array_t type
#include "memory.h"     // my_strndup type
#include "tokenizer.h"  // tokenizer functions
#include "token.h"      // token enum + define
#include "kamion.h"     // compiler_t type
#include "error.h"      // error handling
#include <stdio.h>      // file handling functions
#include <stdlib.h>     // malloc, free functions
#include <stddef.h>     // size_t type, NULL define
#include <stdbool.h>    // bool type

// Init the token to default value
static int init_tok(token_t *tok)
{
    // Check for potential null pointer
    if (!tok)
        return err_prog(PTR_ERR, KO, ERR_INFO);

    tok->type = -1;
    tok->id = -1;
    tok->file = NULL;
    tok->line = NULL;
    tok->x = 0;
    tok->y = 0;
    tok->size = 0;
    tok->value = NULL;
    return OK;
}

// Setup the token to given value
static int setup_tok(token_t *tok,
    char const *file, char const *line, char const *tok_str,
    int const n, int const i, size_t const size,
    int *id)
{
    // Check for potential null pointer
    if (!tok || !file || !line || !tok_str || !id)
        return err_prog(PTR_ERR, KO, ERR_INFO);

    // Setup type and id with the id found
    tok->id = *id;
    if (*id == -1)
        tok->type = IDENTIFIERS;
    else if (*id < MAX_DEL)
        tok->type = DELIMITOR;
    else if (*id < MAX_OP)
        tok->type = OPERATOR;
    else if (*id < MAX_T)
        tok->type = TYPE;
    else if (*id < MAX_FLC)
        tok->type = FLOW_CONTROLER;
    else if (*id < MAX_KW)
        tok->type = KEY_WORD;
    else
        tok->type = LITERAL;

    // Setup other info for position in file and file
    tok->x = i;
    tok->y = n;
    tok->size = size;
    if (tok->file && tok->line && tok->value) {
        free(tok->file);
        free(tok->line);
        free(tok->value);
    }
    tok->file = my_strdup(file);
    tok->line = my_strdup(line);
    tok->value = my_strdup(tok_str);
    if (!tok->file || !tok->line || !tok->value)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    return OK;
}

// Extract the token of the given line
static int extract_token(compiler_t *data, hashtable_t *ids, array_t *tokens,
    char const *file, char const *line, int const n)
{
    token_t *tok = NULL;
    char *tok_start = NULL;
    char *tok_str = NULL;
    int *id = NULL;
    bool valid = false;
    size_t size = 0;

    // Check for potential null pointer
    if (!data || !ids || !tokens || !file || !line)
        return err_prog(PTR_ERR, KO, ERR_INFO);

    // Loop while we havn't check every token until the last char
    for (int i = 0; line[i];) {
        for (; line[i] == ' '; i++);
        valid = false;
        tok_start = (char *) &line[i];
        tok = malloc(sizeof(token_t));
        if (!tok || init_tok(tok) == KO)
            return err_prog(MALLOC_ERR, KO, ERR_INFO);

        // Try to find token in the line
        for (size = 1; tok_start[size - 1]; size++) {
            tok_str = my_strndup(tok_start, size);
            id = ht_search(ids, tok_str);
            if (id || is_identifier(tok, tok_str, &id) || is_literal(tok, tok_str, &id)) {
                valid = true;
                if (setup_tok(tok, file, line, tok_str, n, i, size, id) == KO)
                    return err_prog(UNDEF_ERR, KO, ERR_INFO);
            } else if (valid)
                break;
            free(tok_str);
        }

        // Check if a token have been found
        if (!valid) {
            free(tok);
            return err_c15(data, KO, file, n, "Tokenizer", "Can't identify this", line, i + 1, i + size, false);
        } else if (add_array(tokens, tok) == KO)
            return err_prog(UNDEF_ERR, KO, ERR_INFO);
        i += size - 1;
    }
    return OK;
}

/* Main tokenizer function
----------------------------------------------------------------
 *  Extract the token of a given file
 *  add the token found to the tokens hashtable
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
