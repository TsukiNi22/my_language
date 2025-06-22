/**************************************************************\

 ██╗  ██╗ █████╗ ██████╗ ████████╗ █████╗ ███╗   ██╗██╗ █████╗ 
 ╚██╗██╔╝██╔══██╗██╔══██╗╚══██╔══╝██╔══██╗████╗  ██║██║██╔══██╗
  ╚███╔╝ ███████║██████╔╝   ██║   ███████║██╔██╗ ██║██║███████║
  ██╔██╗ ██╔══██║██╔══██╗   ██║   ██╔══██║██║╚██╗██║██║██╔══██║
 ██╔╝ ██╗██║  ██║██║  ██║   ██║   ██║  ██║██║ ╚████║██║██║  ██║
 ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝

Edition:
##  19/06/2025 by Tsukini

File Name:
##  const.c

File Description:
## Constant used in flag initialisation and other thing
\**************************************************************/

#include "token.h"  // token_id_t type
#include "kamion.h" // compiler_t type

// Flag that are with '-'
char const flags[] = {
    'h',
    'b',
    'E',
    'd',
    'D',
    't',
    'a',
    '\0'
};

// Flag that are with '--'
char const *full_flags[] = {
    "--help",
    "--binary",
    "--Errors",
    "--directory",
    "--Directory",
    "--tokens",
    "--advencement",
    NULL
};

// Used for the number of arg of a flag (-1 for those who can't be conbined)
int const flags_argc[] = {
    -1, // help
    1,  // binary
    0,  // Errors
    1,  // directory
    1,  // Directory
    0,  // tokens
    0,  // advencement
};

// Function call at the detection of  a flag
int (* const flag_functions[])(compiler_t *, int const, char const *[]) = {
    &flag_null, // help
    &flag_binary, // binary
    &flag_Errors, // Errors
    &flag_directory, // directory
    &flag_Directory, // Directory
    &flag_tokens, // tokens
    &flag_advencement, // advencement
};

// Regex patterns for litteral
const char *patterns[REGEX_NUMBER] = {
    "^(0|1|true|false)$",               // Bool
    "^0b[01]*$",                        // Bin
    "^0[0-7]*$",                        // Oct
    "^0x[0-9a-fA-F]*$",                 // Hex
    "^-?[0-9]+$",                       // Int
    "^-?([0-9]+\\.[0-9]*|\\.[0-9]+)$",  // Float
    "^\"([^\"\\\\]|\\\\.)*\"$",         // String
    "^'(\\.|[^'\\\\])'$",               // Char
    "^@>.*<@$"                          // Comment
};

// Value of the patterns
token_id_t patterns_val[REGEX_NUMBER] = {
    LIT_BOOL,
    LIT_BINARY,
    LIT_OCTAL,
    LIT_HEXADECIMAL,
    LIT_DECIMAL,
    LIT_FLOAT,
    LIT_STRING,
    LIT_CHAR,
    LIT_COMMENT,
};

// token str
char const *token_str[] = {
    ";",         // del_expresion_end
    ",",         // del_sep_1
    ":",         // del_sep_2
    ".",         // del_access
    "@",         // del_comment
    "@>",        // del_open_comment
    "<@",        // del_close_comment
    "(",         // del_open_parenthesis
    ")",         // del_close_parenthesis
    "{",         // del_open_curly
    "}",         // del_close_curly
    "'",         // del_char
    "\"",        // del_str

    "=",         // op_eq
    "!",         // op_not
    "?",         // op_bool
    "-",         // op_sub
    "+",         // op_add
    "*",         // op_mult
    "/",         // op_div
    "^",         // op_pow
    "%",         // op_modulo
    "//",        // op_int_div
    "&",         // op_and
    "|",         // op_or
    ">>",        // op_r_shift
    "<<",        // op_l_shift
    "<-",        // op_access
    "->",        // op_dereferencing
    "++",        // op_inc
    "--",        // op_dec

    ">",         // cmp_greater_than
    ">=",        // cmp_greater_or_equal_than
    "<",         // cmp_less_than
    "<=",        // cmp_less_or_equal_than
    "==",        // cmp_equal_to
    "===",       // cmp_sctrictly_equal_to
    "!=",        // cmp_not_equal_to
    "!==",       // cmp_sctrictly_not_equla_to
    "~=",        // cmp_slightly_different
    "&&",        // cmp_logical_and
    "||",        // cmp_logical_or

    "char",      // t_char
    "str",       // t_str
    "bool",      // t_bool
    "bin",       // t_bin
    "oct",       // t_oct
    "int",       // t_int
    "hex",       // t_hex
    "float",     // t_float
    "ptr",       // t_ptr
    "array",     // t_array
    "struct",    // t_struct
    "unsigned",  // t_unsigned

    "if",        // flc_if
    "&if",       // flc_and_if
    "|if",       // flc_or_if
    "elif",      // flc_elif
    "else",      // flc_else
    "for",       // flc_for
    "do",        // flc_do
    "break",     // flc_break
    "continue",  // flc_continue
    "return",    // flc_return
    "jump",      // flc_jump
    "ifjp",      // flc_if_jump
    "exit",      // flc_exit
    "error",     // flc_error

    "<<<",       // kw_write
    ">>>",       // kw_read
    "set",       // kw_define
    "get",       // kw_get
    "from",      // kw_from
    "@error@",   // kw_error
    "none",      // kw_none

    NULL
};
