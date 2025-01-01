##
## PHYTON PROJECT, 2024
## lexicon_unit.py
## File description:
## Lexicon of id by name and type
##

comparator = {
    ">": "c_greater",
    "<": "c_less",
    "==": "c_equal",
    "!=": "c_diffrent",
    "~=": "c_praticly_equal"
}

operator = {
    "=": "o_attribution",
    "!": "o_negation",
    "?": "o_boolean",
    "-": "o_minus",
    "+": "o_add",
    "*": "o_multiplie",
    "/": "o_divided",
    "^": "o_power",
    "%": "o_remainder",
    "//": "o_divided_interger",
    "&": "o_binary_and",
    "|": "o_binary_or",
    ">>": "o_binary_switch_right",
    "<<": "o_binary_switch_left",
    "->": "o_memory_adresse",
    "<-": "o_memory_value",
    "++": "o_add_variable",
    "--": "o_minus_variable",

    ".+": "o_add_one",
    ".-": "o_minus_one",
    ".=": "o_operator_atrribution"
}

data_type = {
    "char": "t_char",
    "bool": "t_bool",
    "int": "t_int",
    "float": "t_float",
    "str": "t_str",
    "hex": "t_hex",
    "bin": "t_bin",
    "ptr": "t_ptr",
    "array": "t_array",
    "struct": "t_struct",
    "link": "t_link",
    "reversed": "t_reversed",
    "looped": "t_looped",
    "unsigned": "t_unisgned",
}

delimitor = {
    ";": "d_instruction_end",
    ",": "d_comma",
    "@": "d_comment",
    "@>": "d_comment_start",
    "<@": "d_comment_end",
    "(": "d_round_1",
    ")": "d_round_2",
    "[": "d_square_1",
    "]": "d_square_2",
    "{": "d_curly_1",
    "}": "d_curly_2",
}

flow_controler = {
    "if": "f_if",
    "&if": "f_if",
    "elif": "f_else_if",
    "else": "f_else",
    "for": "f_for",
    "break": "f_break",
    "continue": "f_continue",
    "return": "f_return",
    "exit": "f_exit",
    "error": "f_error",
    "jump": "f_jump"
}

key_word = {
    "<<<": "k_print",
    ">>>": "k_read",
    "set": "k_set",
    "get": "k_get",
    "from": "k_from",
    "@error@": "k_error",
    "none": "k_none"
}
