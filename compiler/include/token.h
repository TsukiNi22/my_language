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
##  token.h

File Description:
## Constant for the token info
\**************************************************************/

#ifndef TOKEN_H
    #define TOKEN_H

    //----------------------------------------------------------------//
    /* DEFINE */
    
    /* delimitation for id */
    #define MAX_DEL DEL_STRING
    #define MAX_OP OP_DEC
    #define MAX_CMP CMP_LOGICAL_OR
    #define MAX_T T_UNSIGNED
    #define MAX_FLC FLC_ERROR
    #define MAX_KW KW_NONE

//----------------------------------------------------------------//
/* TYPEDEF */

/* type value */
typedef enum type_e {
    DELIMITOR = 0,
    OPERATOR,
    COMPARATOR,
    TYPE,
    FLOW_CONTROLER,
    KEY_WORD,
    LITERAL,
    IDENTIFIERS
} type_t;

/* id value */
typedef enum token_id_e {
    DEL_EXPRESSION_END = 0,
    DEL_SEP_1,
    DEL_SEP_2,
    DEL_ACCESS,
    DEL_COMMENT,
    DEL_OPEN_COMMENT,
    DEL_CLOSE_COMMENT,
    DEL_OPEN_PARENTHESIS,
    DEL_CLOSE_PARENTHESIS,
    DEL_OPEN_CURLY,
    DEL_CLOSE_CURLY,
    DEL_CHAR,
    DEL_STRING,

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

    CMP_GREATER_THAN,
    CMP_GREATER_OR_EQUAL_THAN,
    CMP_LESS_THAN,
    CMP_LESS_OR_EQUAL_THAN,
    CMP_EQUAL_TO,
    CMP_STRICTLY_EQUAL_TO,
    CMP_NOT_EQUAL_TO,
    CMP_STRICTLY_NOT_EQUAL_TO,
    CMP_SLIGHTLY_DIFFERENT,
    CMP_LOGICAL_AND,
    CMP_LOGICAL_OR,

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

    LIT_COMMENT,
    LIT_CHAR,
    LIT_STRING,
    LIT_BOOL,
    LIT_BINARY,
    LIT_OCTAL,
    LIT_HEXADECIMAL,
    LIT_DECIMAL,
    LIT_FLOAT
} token_id_t;

#endif /* TOKEN_H */
