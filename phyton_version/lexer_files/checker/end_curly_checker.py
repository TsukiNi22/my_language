##
## PYTHON PROJECT, 2025
## end_curly_checker.py
## File description:
## Checker for end curly
##

from error import c15SyntaxError

def check_end_curly(file, insts, f_tok, i):
    print("End Curly")
    nbr = 1
    
    for inst in reversed(insts[:i]):
        if any((tok.type == "delimitor" and tok.id == "d_curly_1") for tok in inst):
            nbr -= 1
        if any((tok.type == "delimitor" and tok.id == "d_curly_2") for tok in inst):
            nbr += 1
        if nbr == 0:
            return
    if nbr != 0:
        raise c15SyntaxError("End of \'}\' without Start \'{\'", f_tok.x_start, f_tok.x_end, f_tok.y, file[f_tok.y])
