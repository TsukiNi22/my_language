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
#include "my_string.h"  // my_str_is function
#include "memory.h"     // my_strndup function
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
    else if (*id <= MAX_DEL)
        tok->type = DELIMITOR;
    else if (*id <= MAX_OP)
        tok->type = OPERATOR;
    else if (*id <= MAX_T)
        tok->type = TYPE;
    else if (*id <= MAX_FLC)
        tok->type = FLOW_CONTROLER;
    else if (*id <= MAX_KW)
        tok->type = KEY_WORD;
    else
        tok->type = LITERAL;

    if ((tok->type == LITERAL && tok->id != LIT_COMMENT) || tok->type == IDENTIFIERS)
        free(id);

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
static int extract_tokens(compiler_t *data, hashtable_t *ids, array_t *tokens,
    char const *file, char const *line, int const y)
{
    token_t *tok = NULL;
    char *tok_start = NULL;
    char *tok_str = NULL;
    int *id = NULL;
    bool valid = false;
    size_t max_size = 0;
    size_t size = 0;

    // Check for potential null pointer
    if (!data || !ids || !tokens || !file || !line)
        return err_prog(PTR_ERR, KO, ERR_INFO);

    // Loop while we havn't check every token until the last char
    for (int i = 0; line[i];) {
        for (; line[i] == ' ' || line[i] == '\t'; i++);
        valid = false;
        max_size = 0;
        tok_start = (char *) &line[i];
        tok = malloc(sizeof(token_t));
        if (!tok || init_tok(tok) == KO)
            return err_prog(UNDEF_ERR, KO, ERR_INFO);

        // Try to find token in the line
        for (size = 1; tok_start[size - 1]; size++) {
            tok_str = my_strndup(tok_start, size);
            id = ht_search(ids, tok_str);
            if (id || is_identifier(tok_str, &id) || is_literal(tok_str, &id)) {
                valid = true;
                max_size = size;
                if (setup_tok(tok, file, line, tok_str, y, i, size, id) == KO)
                    return err_prog(UNDEF_ERR, KO, ERR_INFO);
            }
            free(tok_str);
        }

        // Check if a token have been found
        if (!valid) {
            free(tok);
            return err_c15(data, KO, file, y, "Tokenizer", "Can't identify this", line, i + 1, i + (size - 1), false);
        } else if (add_array(tokens, tok) == KO)
            return err_prog(UNDEF_ERR, KO, ERR_INFO);
        i += max_size;

        // In case of simple comment with '@'
        if (valid && ((tok->type == DELIMITOR && tok->id == DEL_COMMENT)
            || (tok->type == KEY_WORD && tok->id == KW_ERROR))) {
            tok = malloc(sizeof(token_t));
            if (!tok || init_tok(tok) == KO)
                return err_prog(UNDEF_ERR, KO, ERR_INFO);
            for (size = 1; line[i + (size + 1)]; size++);
            if (setup_tok(tok, file, line, &line[i], y, i, size, &(int){LIT_COMMENT}) == KO)
                return err_prog(UNDEF_ERR, KO, ERR_INFO);
            if (add_array(tokens, tok) == KO)
                return err_prog(UNDEF_ERR, KO, ERR_INFO);
            return OK;
        }
    }
    return OK;
}

// Obtain the file in a char *
static char *get_file(const char *file)
{
    FILE *fs = NULL;
    char *buff = NULL;
    size_t size = 0;
    size_t res = 0;

    // Check for potential null pointer
    if (!file)
        return err_prog_n(PTR_ERR, ERR_INFO);

    // Set the stream for the file to tokenize
    fs = fopen(file, "r");
    if (!fs)
        return err_prog_n(UNDEF_ERR, ERR_INFO);

    // Get the size
    fseek(fs, 0, SEEK_END);
    size = ftell(fs);
    rewind(fs);

    // Malloc the good size for the whole file
    if (my_malloc_c(&buff, (size * 2) + 2) == KO)
        return err_prog_n(UNDEF_ERR, ERR_INFO);

    // Set the file content
    res = fread(buff, 1, size, fs);
    if (res != size)
        return err_prog_n(UNDEF_ERR, ERR_INFO);

    fclose(fs);
    return buff;
}

// Set all the \n to \ and n
static int set_buff_n(char *buff)
{
    bool char_b, string_b, comment_b = false;
    int len = 0;

    // Check for potential null pointer
    if (!buff)
        return err_prog(PTR_ERR, KO, ERR_INFO);

    for (len = 0; buff[len]; len++);
    for (int i = 0; buff[i]; i++) {
        // Skip the simple '@' comment
        if (buff[i] == '@' && (i == 0 || buff[i - 1] != '<') && buff[i + 1] != '>')
            for (; buff[i] && buff[i] != '\n'; i++);
        
        // Detect if in a string a char or a comment
        if (!string_b && !comment_b && buff[i] == '\'')
            char_b = !char_b;
        if (!char_b && !comment_b && buff[i] == '\"')
            string_b = !string_b;
        if (!char_b && !string_b && !comment_b && my_strncmp(&buff[i], "@>", 2) == 0)
            comment_b = true;
        if (!char_b && !string_b && comment_b && my_strncmp(&buff[i], "<@", 2) == 0)
            comment_b = false;

        if (buff[i] == '\n' && (char_b || string_b || comment_b)) {
            for (int j = len; j > i; j--)
                buff[j + 1] = buff[j];
            buff[i] = '\\';
            buff[i + 1] = 'n';
            i++;
        }   
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
array_t *tokenizer(compiler_t *data, hashtable_t *ids, char const *file)
{
    array_t *tokens = NULL;
    char *buff = NULL;
    char *line = NULL;
    int index = 0;

    // Check for potential null pointer
    if (!data || !ids || !file)
        return err_prog_n(PTR_ERR, ERR_INFO);
    
    // Init the token array
    tokens = new_array();
    if (!tokens)
        return err_prog_n(UNDEF_ERR, ERR_INFO);

    // Set the file str for the \n in the line
    buff = get_file(file);
    if (!buff)
        return err_prog_n(UNDEF_ERR, ERR_INFO);
    if (set_buff_n(buff) == KO)
        return err_prog_n(UNDEF_ERR, ERR_INFO);

    // Extract all the token of the file
    line = buff;
    while (*line) {
        for (index = 0; line[index] && line[index] != '\n'; index++);
        line[index] = '\0';
        if (!my_str_is(line, " \t") && extract_tokens(data, ids, tokens, file, line, 1) == KO)
            return err_prog_n(UNDEF_ERR, ERR_INFO);
        line = &line[index + 1];
    }

    free(buff);
    return tokens;
}
