##
## PYTHON PROJECT, 2025
## print_checker.py
## File description:
## Checker for print
##

from error import c15SyntaxError

def check_print(file, inst):
    print("Print")
    print_declaration = ", need to be -> \"int stream <<< (buffer, int nbr_to_print)\""
    size = len(inst)
    for tok in inst:
        if tok.type == "key_word" and tok.id == "k_print":
            print_tok = tok
            break
    x_end = max(tok.x_end for tok in inst if tok.y == print_tok.y)
    if x_end == inst[-1].x_end:
        x_end += 1
    
    if size != 7:
        arg = ", too mutch things"
        if size < 7:
            arg = ", less things than needed"
        raise c15SyntaxError("Invalid delimitation of print" + arg + print_declaration, 1, x_end, print_tok.y, file[print_tok.y])
    if sum(1 for tok in inst if (tok.type == "key_word" and tok.id == "k_print")) != 1:
        raise c15SyntaxError("Multiple \'<<<\', only one at the same time" + print_declaration, 1, x_end, print_tok.y, file[print_tok.y])
    if inst[1] != print_tok:
        raise c15SyntaxError("Invalid positionement of \'<<<\'" + print_declaration, print_tok.x_start, print_tok.x_end , print_tok.y, file[print_tok.y])
    if not (inst[2].type == "delimitor" and inst[2].id == "d_round_1") or not (inst[4].type == "delimitor" and inst[4].id == "d_comma") or not (inst[6].type == "delimitor" and inst[6].id == "d_round_2"):
        raise c15SyntaxError("Invalid delimitation of print" + print_declaration, 1, print_tok.x_start - 1, print_tok.y, file[print_tok.y])
    if not (inst[0].type == "literal" and (inst[0].id == "l_integer" or (inst[0].id == "l_binary" and inst[0].value[0] != "0"))) and not inst[0].type == "identifier":
        raise c15SyntaxError("Invalid stream value, stream need to be an integer > 0" + print_declaration, inst[0].x_start, inst[0].x_end, print_tok.y, file[print_tok.y])
    if not (inst[5].type == "literal" and (inst[3].id == "l_integer" or (inst[5].id == "l_binary" and inst[5].value[0] != "0"))) and not inst[5].type == "identifier":
        raise c15SyntaxError("Invalid nbr_to_print value, nbr_to_print need to be an integer >= 0" + print_declaration, inst[5].x_start, inst[5].x_end, print_tok.y, file[print_tok.y])
    if not inst[3].type == "identifier":
        raise c15SyntaxError("Invalid variable to write in, buffer need to be a str variable" + print_declaration, inst[3].x_start, inst[3].x_end, print_tok.y, file[print_tok.y])
