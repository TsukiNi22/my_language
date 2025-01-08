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

from lexer import check_import, check_initialization, check_attribution
from lexer import check_function, check_function_call
from lexer import check_read, check_print
from lexer import check_flow_controler, check_end_curly, check_error_message
from constant import EXT_SOURCE, EXT_HEADER
from error import c15SyntaxError

def instruction_checker(file, instructions, instruction, i):
    inst = instruction
    for i in range(len(inst)):
        tok = inst[i]
        if tok.type == "delimitor" and tok.id == "d_curly_1":
            instruction_checker(file, instructions, instruction[:i], i)
            instruction_checker(file, instructions, instruction[i + 1:], i)
            instructions.pop(i)
            instructions.insert(i, instruction[i + 1:])
            instructions.insert(i, instruction[:i])
            return instructions, i + 1
    print()
    """for tok in inst:
        print(tok)"""
    f_tok = inst[0]

    if any((tok.type == "key_word" and tok.id == "k_get") for tok in inst) or any((tok.type == "key_word" and tok.id == "k_from") for tok in inst):
        check_import(file, instruction);
        return instructions, i
    elif any((tok.type == "key_word" and tok.id == "k_read") for tok in inst):
        check_read(file, instruction)
        return instructions, i
    elif any((tok.type == "key_word" and tok.id == "k_print") for tok in inst):
        check_print(file, instruction)
        return instructions, i
    elif any((tok.type == "flow_controler") for tok in inst):
        check_flow_controler(file, instructions, instruction, i)
        return instructions, i
    elif any((tok.type == "identifier") for tok in inst):
        if any((tok.type == "data_type") for tok in inst) or any((tok.type == "key_word" and tok.id == "k_none") for tok in inst):
            if any((tok.type == "delimitor" and tok.id == "d_round_1") for tok in inst):
                check_function(file, instructions, instruction, i)
                return instructions, i
            elif not any((tok.type == "key_word" and tok.id == "k_none") for tok in inst):
                check_initialization(file, instruction)
                return instructions, i
        elif any((tok.type == "delimitor" and tok.id == "d_round_1") for tok in inst):
            check_function_call(file, instruction)
            return instructions, i
        elif any((tok.type == "operator" and tok.id == "o_attribution") for tok in inst) or any((tok.type == "operator" and tok.id == "o_operator_atribution") for tok in inst):
            check_attribution(file, instruction)
            return instructions, i
    elif len(inst) == 1 and f_tok.type == "delimitor" and f_tok.id == "d_curly_2":
        check_end_curly(file, instructions, i);
        return instructions, i
    elif len(inst) == 1 and f_tok.type == "key_word" and f_tok.id == "k_error":
        check_error_message(file, f_tok)
        return instructions, i
    x_end = max(tok.x_end for tok in inst if tok.y == f_tok.y)
    if x_end == inst[-1].x_end:
        x_end += 1
    raise c15SyntaxError("Unknow instruction", 1, x_end, f_tok.y, file[f_tok.y])
