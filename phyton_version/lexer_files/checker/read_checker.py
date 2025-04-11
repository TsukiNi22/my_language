##
## PYTHON PROJECT, 2025
## read_checker.py
## File description:
## Checker for read
##

from lexer import is_operation_tok, check_operation
from error import c15SyntaxError

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
    
    if size < 7:
        raise c15SyntaxError("Invalid delimitation of read, less things than needed" + read_declaration, 1, x_end, read_tok.y, file[read_tok.y])
    if sum(1 for tok in inst if (tok.type == "key_word" and tok.id == "k_read")) != 1:
        raise c15SyntaxError("Multiple \'>>>\', only one at the same time" + read_declaration, 1, x_end, read_tok.y, file[read_tok.y])
    if inst[-2] != read_tok:
        raise c15SyntaxError("Invalid positionement of \'>>>\'" + read_declaration, read_tok.x_start, read_tok.x_end , read_tok.y, file[read_tok.y])
    if not (inst[0].type == "delimitor" and inst[0].id == "d_round_1") or sum(1 for tok in inst if (tok.type == "delimitor" and tok.id == "d_comma")) != 1 or not (inst[-3].type == "delimitor" and inst[-3].id == "d_round_2"):
        raise c15SyntaxError("Invalid delimitation of read" + read_declaration, 1, read_tok.x_start - 1, read_tok.y, file[read_tok.y])
    i = 1
    while not (inst[i].type == "delimitor" and inst[i].id == "d_comma") and inst[i] != inst[-3] and is_operation_tok(inst[i]):
        i += 1
    if inst[i] == inst[-3]:
        raise c15SyntaxError("Need a \',\' between \'(\' and \')\'" + read_declaration, inst[1].x_start, x_end, read_tok.y, file[read_tok.y])
    elif not (inst[i].type == "delimitor" and inst[i].id == "d_comma"):
        raise c15SyntaxError("Invalid thing in the operation for the stream value" + print_declaration, inst[i].x_start, inst[i].x_end, inst[i].y, file[inst[i].y])
    check_operation(file, inst[1:i])
    for tok in inst[i + 1:-3]:
        if not is_operation_tok(tok):
            raise c15SyntaxError("Invalid thing in the operation for the nbr_to_read value" + print_declaration, tok.x_start, tok.x_end, tok.y, file[tok.y])
    check_operation(file, inst[i + 1:-3])
    """
    if not (inst[1].type == "literal" and (inst[1].id == "l_integer" or (inst[1].id == "l_binary" and inst[1].value[0] != "0"))) and not inst[1].type == "identifier":
        raise c15SyntaxError("Invalid stream value, stream need to be an integer > 0" + read_declaration, inst[1].x_start, inst[1].x_end, read_tok.y, file[read_tok.y])
    if not (inst[3].type == "literal" and (inst[3].id == "l_integer" or (inst[3].id == "l_binary" and inst[3].value[0] != "0"))) and not inst[3].type == "identifier":
        raise c15SyntaxError("Invalid nbr_to_read value, nbr_to_read need to be an integer >= 0" + read_declaration, inst[3].x_start, inst[3].x_end, read_tok.y, file[read_tok.y])
    """
    if not (inst[-1].type == "literal" and inst[-1].id == "l_string") and not inst[-1].type == "identifier":
        raise c15SyntaxError("Invalid variable to write in, buffer need to be a str variable" + read_declaration, inst[-1].x_start, inst[-1].x_end, read_tok.y, file[read_tok.y])
