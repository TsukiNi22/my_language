##
## PYTHON PROJECT, 2025
## read_checker.py
## File description:
## Checker for read
##

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
    
    if size != 7:
        arg = ", too mutch things"
        if size < 7:
            arg = ", less things than needed"
        raise c15SyntaxError("Invalid delimitation of read" + arg + read_declaration, 1, x_end, read_tok.y, file[read_tok.y])
    if sum(1 for tok in inst if (tok.type == "key_word" and tok.id == "k_read")) != 1:
        raise c15SyntaxError("Multiple \'>>>\', only one at the same time" + read_declaration, 1, x_end, read_tok.y, file[read_tok.y])
    if inst[5] != read_tok:
        raise c15SyntaxError("Invalid positionement of \'>>>\'" + read_declaration, read_tok.x_start, read_tok.x_end , read_tok.y, file[read_tok.y])
    if not (inst[0].type == "delimitor" and inst[0].id == "d_round_1") or not (inst[2].type == "delimitor" and inst[2].id == "d_comma") or not (inst[4].type == "delimitor" and inst[4].id == "d_round_2"):
        raise c15SyntaxError("Invalid delimitation of read" + read_declaration, 1, read_tok.x_start - 1, read_tok.y, file[read_tok.y])
    if not (inst[1].type == "literal" and (inst[1].id == "l_integer" or (inst[1].id == "l_binary" and inst[1].value[0] != "0"))) and not inst[1].type == "identifier":
        raise c15SyntaxError("Invalid stream value, stream need to be an integer > 0" + read_declaration, inst[1].x_start, inst[1].x_end, read_tok.y, file[read_tok.y])
    if not (inst[3].type == "literal" and (inst[3].id == "l_integer" or (inst[3].id == "l_binary" and inst[3].value[0] != "0"))) and not inst[3].type == "identifier":
        raise c15SyntaxError("Invalid nbr_to_read value, nbr_to_read need to be an integer >= 0" + read_declaration, inst[3].x_start, inst[3].x_end, read_tok.y, file[read_tok.y])
    if not inst[6].type == "identifier":
        raise c15SyntaxError("Invalid variable to write in, buffer need to be a str variable" + read_declaration, inst[6].x_start, inst[6].x_end, read_tok.y, file[read_tok.y])
