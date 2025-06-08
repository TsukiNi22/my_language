/**************************************************************\

 ██╗  ██╗ █████╗ ██████╗ ████████╗ █████╗ ███╗   ██╗██╗ █████╗ 
 ╚██╗██╔╝██╔══██╗██╔══██╗╚══██╔══╝██╔══██╗████╗  ██║██║██╔══██╗
  ╚███╔╝ ███████║██████╔╝   ██║   ███████║██╔██╗ ██║██║███████║
  ██╔██╗ ██╔══██║██╔══██╗   ██║   ██╔══██║██║╚██╗██║██║██╔══██║
 ██╔╝ ██╗██║  ██║██║  ██║   ██║   ██║  ██║██║ ╚████║██║██║  ██║
 ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝

Edition:
##  08/06/2025 by Tsukini

File Name:
##  kamion.h

File Description:
## The main header of the kamion compiler
\**************************************************************/

#ifndef KAMION_H
    #define KAMION_H

    //----------------------------------------------------------------//
    /* INCLUDE */

    /* type */
    #include "hashtable.h"  // hashtable_t
    #include "array.h"      // array_t
    #include <regex.h>      // regex_t
    #include <stddef.h>     // size_t
    #include <stdbool.h>    // boolean

    //----------------------------------------------------------------//
    /* DEFINE */

    /* extension */
    #define FILE_EXTENSION ".15"
    #define HEADER_EXTENSION ".15h"

    /* files_name */
    #define BINARY_NAME "15.out"

    /* regex */
    #define REGEX_NUMBER 9
    
    /* debug */
    #define ADV_SIZE 50

//----------------------------------------------------------------//
/* TYPEDEF */

/* data */
typedef struct compiler_s {
    /* global_info */
    int argc;
    char const **argv;
    char const *exe_name;
    regex_t regex[REGEX_NUMBER];

    /* option */
    bool tok_dump;
    bool adv_dump;
    bool errors;
    char const *binary;

    /* option duplicated */
    bool d_binary;
    bool d_errors;
    bool d_tok_dump;
    bool d_adv_dump;

    /* advencement option */
    size_t actual_adv;
    size_t total_adv;

    /* token id */
    hashtable_t *id;

    /* file information */
    array_t *files;
    hashtable_t *tokens;

    /* ouput */
    bool help;
    bool err_sys;
    size_t nb_error;
    size_t nb_warning;
} compiler_t;

//----------------------------------------------------------------//
/* PROTOTYPE */

/* kamion */
int kamion(int const argc, char const *argv[], compiler_t *data); // Error: KO

/* init_data */
int init_data(compiler_t *data); // Error: KO
int init_global(compiler_t *data); // Error: KO
int init_regex(compiler_t *data); // Error: KO
int init_option(compiler_t *data); // Error: KO

/* init_flag */
int init_flag(compiler_t *data, int const argc, char const *argv[]); // Error: KO
int flag_help(void); // Error: KO
int flag_null(compiler_t *data, int const argc, char const *argv[]); // Error: KO
int flag_binary(compiler_t *data, int const argc, char const *argv[]); // Error: KO
int flag_Errors(compiler_t *data, int const argc, char const *argv[]); // Error: KO
int flag_directory(compiler_t *data, int const argc, char const *argv[]); // Error: KO
int flag_Directory(compiler_t *data, int const argc, char const *argv[]); // Error: KO
int flag_tokens(compiler_t *data, int const argc, char const *argv[]); // Error: KO
int flag_advencement(compiler_t *data, int const argc, char const *argv[]); // Error: KO

/* useful */
bool is_valid_dir(compiler_t *data, char const *path, bool err); // Error: false
bool is_valid_file(compiler_t *data, char const *path, bool err); // Error: false

/* debug */
int setup_files_advencement(compiler_t *data); // Error: KO
int advencement_dump(compiler_t *data); // Error: KO

/* exit */
int free_data(compiler_t *data); // Error: KO

//----------------------------------------------------------------//
/* GLOBAL_CONST */

/* flag */
extern char const flags[];
extern char const *full_flags[];
extern int const flags_argc[];
extern int (* const flag_functions[])(compiler_t *, int const, char const *[]);

/* token id */
extern char const *token_str[];

#endif /* KAMION_H */
