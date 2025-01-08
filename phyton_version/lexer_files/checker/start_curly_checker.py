##
## PYTHON PROJECT, 2025
## start_curly_checker.py
## File description:
## Checker for start curly
##

from error import c15SyntaxError

def check_start_curly(file, insts, f_tok, i):
    print("Start Curly")
    nbr = 1
    
    for inst in insts[i + 1:]:
        if any((tok.type == "delimitor" and tok.id == "d_curly_1") for tok in inst):
            nbr += 1
        if any((tok.type == "delimitor" and tok.id == "d_curly_2") for tok in inst):
            nbr -= 1
        if nbr == 0:
            return
    if nbr != 0:
        raise c15SyntaxError("Start of \'{\' without End \'}\'", f_tok.x_start, f_tok.x_end, f_tok.y, file[f_tok.y])
