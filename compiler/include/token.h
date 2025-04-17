/**************************************************************\

 ██╗  ██╗ █████╗ ██████╗ ████████╗ █████╗ ███╗   ██╗██╗ █████╗ 
 ╚██╗██╔╝██╔══██╗██╔══██╗╚══██╔══╝██╔══██╗████╗  ██║██║██╔══██╗
  ╚███╔╝ ███████║██████╔╝   ██║   ███████║██╔██╗ ██║██║███████║
  ██╔██╗ ██╔══██║██╔══██╗   ██║   ██╔══██║██║╚██╗██║██║██╔══██║
 ██╔╝ ██╗██║  ██║██║  ██║   ██║   ██║  ██║██║ ╚████║██║██║  ██║
 ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝

Edition:
##  16/04/2025 by Tsukini

File Name:
##  token_id.c

File Description:
## Constant for the token info
\**************************************************************/

#ifndef TOKEN_H
    #define TOKEN_H

//----------------------------------------------------------------//
/* TYPEDEF */

/* type value */
typedef enum type_e {
    DELIMITOR = 0,
    OPERATOR,
    TYPE,
    FLOW_CONTROLER,
    KEY_WORD,
    LITERAL,
    IDENTIFIER
} type_t;

/* id value */
typedef enum token_id_e {
    DEL_EXPRESSION_END = 0,
    DEL_SEP_1,
    DEL_SEP_2,
    DEL_COMMENT,
    DEL_OPEN_COMMENT,
    DEL_CLOSE_COMMENT,
    DEL_OPEN_PARENTHESIS,
    DEL_CLOSE_PARENTHESIS,
    DEL_OPEN_CURLY,
    DEL_CLOSE_CURLY,
    DEL_CHAR,
    DEL_STR,

    OP_EQ,
    OP_NOT,
    OP_BOOL,
    OP_SUB,
    OP_ADD,
    OP_MULT,
    OP_DIV,
    OP_POW,
    OP_MODULO,
    OP_INT_DIV,
    OP_AND,
    OP_OR,
    OP_R_SHIFT,
    OP_L_SHIFT,
    OP_ACCESS,
    OP_DEREFERENCING,
    OP_INC,
    OP_DEC,

    T_CHAR,
    T_STR,
    T_BOOL,
    T_BIN,
    T_OCT,
    T_INT,
    T_HEX,
    T_FLOAT,
    T_PTR,
    T_ARRAY,
    T_STRUCT,
    T_UNSIGNED,

    FLC_IF,
    FLC_AND_IF,
    FLC_OR_IF,
    FLC_ELIF,
    FLC_ELSE,
    FLC_FOR,
    FLC_DO,
    FLC_BREAK,
    FLC_CONTINUE,
    FLC_RETURN,
    FLC_JUMP,
    FLC_IF_JUMP,
    FLC_EXIT,
    FLC_ERROR,

    KW_WRITE,
    KW_READ,
    KW_DEFINE,
    KW_GET,
    KW_FROM,
    KW_ERROR,
    KW_NONE,

    COMMENT
} token_id_t;

#endif /* TOKEN_H */
