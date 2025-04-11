##
## PYTHON PROJECT, 2025
## print_checker.py
## File description:
## Checker for print
##

from lexer import is_operation_tok, check_operation
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
    
    if size < 7:
        raise c15SyntaxError("Invalid delimitation of print, less things than needed" + print_declaration, 1, x_end, print_tok.y, file[print_tok.y])
    if sum(1 for tok in inst if (tok.type == "key_word" and tok.id == "k_print")) != 1:
        raise c15SyntaxError("Multiple \'<<<\', only one at the same time" + print_declaration, 1, x_end, print_tok.y, file[print_tok.y])
    i = 0
    while inst[i] != print_tok and is_operation_tok(inst[i]):
        i += 1
    check_operation(inst[:i])
    if inst[i] != print_tok:
        raise c15SyntaxError("Invalid thing in the operation for the stream value" + print_declaration, inst[i].x_start, inst[i].x_end, inst[i].y, file[inst[i].y])
    i += 1
    if not (inst[i].type == "delimitor" and inst[i].id == "d_round_1") or sum(1 for tok in inst if (tok.type == "delimitor" and tok.id == "d_comma")) != 1 or not (inst[-1].type == "delimitor" and inst[-1].id == "d_round_2"):
        raise c15SyntaxError("Invalid delimitation of print" + print_declaration, 1, print_tok.x_start - 1, print_tok.y, file[print_tok.y])
    
    """
    if not (inst[0].type == "literal" and (inst[0].id == "l_integer" or (inst[0].id == "l_binary" and inst[0].value[0] != "0"))) and not inst[0].type == "identifier":
        raise c15SyntaxError("Invalid stream value, stream need to be an integer > 0" + print_declaration, inst[0].x_start, inst[0].x_end, print_tok.y, file[print_tok.y])
    if not (inst[5].type == "literal" and (inst[5].id == "l_integer" or (inst[5].id == "l_binary" and inst[5].value[0] != "0"))) and not inst[5].type == "identifier":
        raise c15SyntaxError("Invalid nbr_to_print value, nbr_to_print need to be an integer >= 0" + print_declaration, inst[5].x_start, inst[5].x_end, print_tok.y, file[print_tok.y])
    """

    if not (inst[3].type == "literal" and inst[3].id == "l_string") and not inst[3].type == "identifier":
        raise c15SyntaxError("Invalid variable to write in, buffer need to be a str variable" + print_declaration, inst[3].x_start, inst[3].x_end, print_tok.y, file[print_tok.y])
