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
    print("Init")
    pass

def check_end_curly(file, insts, inst, i):
    print("End Func")
    pass

def check_flow_controler(file, insts, inst, i):
    print("Flow")
    pass

def check_function(file, insts, inst, i):
    print("Func")
    pass

def check_attribution(file, inst):
    print("Attribution")
    pass

def check_function_call(file, inst):
    print("Func Call")
    pass

def check_read(file, inst):
    print("Read")
    read_declaration = ", need to be -> \"(int stream, int nbr_to_read) >>> str buffer\""
    size = len(inst)
    for tok in inst:
        if tok.type == "key_word" and tok.id == "k_read":
            read_tok = tok
            break
    x_end = max(tok.x_end for tok in inst if tok.y == read_tok.y)
    if x_end == inst[-1].x_end:
        x_end += 1
    
    if sum(1 for tok in inst if (tok.type == "key_word" and tok.id == "k_read")) != 1:
        raise c15SyntaxError("Multiple \'>>>\', only one at the same time" + read_declaration, 1, x_end, read_tok.y, file[read_tok.y])
    if inst[5] != read_tok:
        raise c15SyntaxError("Invalid positionement of \'>>>\'" + read_declaration, read_tok.x_start, read_tok.x_end , read_tok.y, file[read_tok.y])
    if not (inst[0].type == "delimitor" and inst[0].id == "d_round_1") or not (inst[2].type == "delimitor" and inst[2].id == "d_comma") or not (inst[4].type == "delimitor" and inst[4].id == "d_round_2"):
        raise c15SyntaxError("Invalid delimitation of read" + read_declaration, 1, read_tok.x_start - 1, read_tok.y, file[read_tok.y])
    if size != 7:
        arg = ", too mutch things"
        if size < 7:
            arg = ", less things than needed"
        raise c15SyntaxError("Invalid delimitation of read" + arg + read_declaration, 1, x_end, read_tok.y, file[read_tok.y])
    if not (inst[1].type == "literal" and (inst[1].id == "l_integer" or (inst[1].id == "l_binary" and inst[1].value[0] != "0"))) and not inst[1].type == "identifier":
        raise c15SyntaxError("Invalid stream value, stream need to be an integer > 0" + read_declaration, inst[1].x_start, inst[1].x_end, read_tok.y, file[read_tok.y])
    if not (inst[3].type == "literal" and (inst[3].id == "l_integer" or (inst[3].id == "l_binary" and inst[3].value[0] != "0"))) and not inst[3].type == "identifier":
        raise c15SyntaxError("Invalid nbr_to_read value, nbr_to_read need to be an integer >= 0" + read_declaration, inst[3].x_start, inst[3].x_end, read_tok.y, file[read_tok.y])
    if not inst[6].type == "identifier":
        raise c15SyntaxError("Invalid variable to write in, buffer need to be a str variable" + read_declaration, inst[6].x_start, inst[6].x_end, read_tok.y, file[read_tok.y])

def check_print(file, inst):
    print("Print")
    pass

def check_error_message(file, token):
    print("Error")
    if token.value.count("@error@") > 1:
        raise c15SyntaxError("Multiple error message defined one a single ligne", token.x_start, token.x_end, token.y, file[token.y])

def instruction_checker(file, insts, inst, i):
    print()
    for tok in inst:
        print(tok)
    f_tok = inst[0]

    if f_tok.type == "key_word" and f_tok.id == "k_get":
        print("Get")
        return
    elif f_tok.type == "delimitor" and f_tok.id == "d_curly_2":
        return check_end_curly(file, insts, inst, i);
    elif any((tok.type == "key_word" and tok.id == "k_read") for tok in inst):
        return check_read(file, inst)
    elif any((tok.type == "key_word" and tok.id == "k_print") for tok in inst):
        return check_print(file, inst)
    elif any((tok.type == "flow_controler") for tok in inst):
        return check_flow_controler(file, insts, inst, i)
    elif any((tok.type == "identifier") for tok in inst):
        if any((tok.type == "data_type") for tok in inst) or any((tok.type == "key_word" and tok.id == "k_none") for tok in inst):
            if any((tok.type == "delimitor" and tok.id == "d_round_1") for tok in inst):
                return check_function(file, insts, inst, i)
            elif not any((tok.type == "key_word" and tok.id == "k_none") for tok in inst):
                return check_initialization(file, inst)
        elif any((tok.type == "delimitor" and tok.id == "d_round_1") for tok in inst):
            return check_function_call(file, inst)
        elif any((tok.type == "operator" and tok.id == "o_attribution") for tok in inst) or any((tok.type == "operator" and tok.id == "o_operator_atribution") for tok in inst):
            return check_attribution(file, inst)
    elif f_tok.type == "key_word" and f_tok.id == "k_error":
        return check_error_message(file, f_tok)
    x_end = max(tok.x_end for tok in inst if tok.y == f_tok.y)
    if x_end == inst[-1].x_end:
        x_end += 1
    raise c15SyntaxError("Unknow instruction", 1, x_end, f_tok.y, file[f_tok.y])
