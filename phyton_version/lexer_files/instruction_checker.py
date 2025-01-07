##
## PYTHON PROJECT, 2024
## instruction_checker.py
## File description:
## Check the instruction
##

"""
Possibility:
import (already checked) -> start with 'get'
function -> start with 'data_type' or 'k_none'
initialization -> start with 'data_type'
attribution -> 'identifier'
flow control -> start with 'flow_controler'
function call -> start with 'identifier'
k_print -> start with 'literal' or 'identifier'
k_read -> start with 'd_round_1'
error message -> 'k_error' can be anywhere but not in double
"""

from error import c15SyntaxError

def check_error_message(file, token):
    if token.value.count("@error@") > 1:
        raise c15SyntaxError("Multiple error message defined one a single ligne", token.x_start, token.x_end, token.y, file[token.y])

def instruction_checker(file, insts, inst, i):
    """print()
    for tok in inst:
        print(tok)
    """
    f_tok = inst[0]

    if len(inst) == 1 and f_tok.type == "key_word" and f_tok.id == "k_error":
        return check_error_message(file, f_tok)
    pass
