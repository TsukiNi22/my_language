##
## PYTHON PROJECT, 2024
## instruction_checker.py
## File description:
## Check the instruction
##

"""
Possibility:
import (already checked) -> start with 'get'

flow control -> start with 'flow_controler'

function -> start with 'data_type' or 'k_none'
initialization -> start with 'data_type'

attribution -> 'identifier'
function call -> start with 'identifier'

k_print -> start with 'literal' or 'identifier'

k_read -> start with 'd_round_1'

error message -> 'k_error' can be anywhere but not in double
"""

from error import c15SyntaxError


def check_initialization(file, inst):
    pass

def check_function(file, inst):
    pass

def check_attribution(file, inst):
    pass

def check_function_call(file, inst):
    pass

def check_read(file, inst):
    pass

def check_print(file, inst):
    pass

def check_error_message(file, token):
    if token.value.count("@error@") > 1:
        raise c15SyntaxError("Multiple error message defined one a single ligne", token.x_start, token.x_end, token.y, file[token.y])

def instruction_checker(file, insts, inst, i):
    """print()
    for tok in inst:
        print(tok)"""
    f_tok = inst[0]
    size = len(inst)

    if f_tok.type == "key_word" and f_tok.id == "k_get":
        return
    elif size >= 2 and f_tok.type == "data_type" and inst[-1].type == "identifier":
        return check_initialization(file, inst)
    elif size >= 4 and (f_tok.type == "data_type" or (f_tok.type == "key_word" and f_tok.id == "k_none")):
        if any((tok.type == "operator" and tok.id == "o_attribution") for tok in inst):
            return check_initialization(file, inst)
        if any((tok.type == "identifier") for tok in inst):
            return check_function(file, inst)
    elif size >= 3 and f_tok.type == "identifier" and (inst[1].type == "operator" and (inst[1].id == "o_attribution" or inst[1].id == "o_operator_atribution")):
        return check_attribution(file, inst)
    elif size >= 3 and f_tok.type == "identifier" and inst[1].type == "delimitor" and inst[1].id == "d_round_1":
        return check_function_call(file, inst)
    elif any((tok.type == "key_word" and tok.id == "k_read") for tok in inst):
        return check_read(file, inst)
    elif any((tok.type == "key_word" and tok.id == "k_print") for tok in inst):
        return check_print(file, inst)
    elif size == 1 and f_tok.type == "key_word" and f_tok.id == "k_error":
        return check_error_message(file, f_tok)
    x_end = max(tok.x_end for tok in inst if tok.y == f_tok.y)
    if x_end == inst[-1].x_end:
        x_end += 1
    raise c15SyntaxError("Unknow instruction", 1, x_end, f_tok.y, file[f_tok.y])
