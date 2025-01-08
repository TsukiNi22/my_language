##
## PYTHON PROJECT, 2025
## end_curly_checker.py
## File description:
## Checker for end curly
##

from error import c15SyntaxError

def check_end_curly(file, insts, inst, i):
    print("End Curly")
    insts = insts[:i]
    nbr = 1

    for tok in insts:
        if tok[-1].type == "delimitor" and tok[-1].id == "d_curly_1":
            if nbr == 0:
                raise c15SyntaxError("End of \'}\' without start", inst.x_start, inst.x_end, inst.y, file[inst.y])
            nbr -= 1
        elif len(tok) == 1 and tok[0].type == "delimitor" and tok[0].id == "d_curly_2":
            nbr += 1
