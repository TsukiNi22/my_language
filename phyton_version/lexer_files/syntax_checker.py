##
## C15 PROGRAMING LANGUAGE PROJECT, 2024
## syntax_checker.py
## File description:
## Check the syntaxe of the file
##

from lexer import instruction_checker
from visualizer import progress_bar
from error import c15SyntaxError

def is_import(file, inst):
    get_everything = False
    size = len(inst)
    
    if size < 4 or inst[0].type == "identifier" or inst[0].id != "k_get":
        return -1
    i = 1
    while i < size - 1 and (inst[i].type == "identifier" or inst[i].id == "o_multiplie"):        
        i += 1
        if (inst[i - 1].type != "identifier" and inst[i - 1].id == "o_multiplie"):
            get_everything = True
    if (size > 4 or inst[i].type == "identifier" or inst[i].id != "k_from" or not i + 1 < size) and get_everything:
        raise c15SyntaxError("Can't import everything with \'*\' and other at the same time", inst[1].x_start, inst[i - 1].x_end, inst[1].y, file[inst[1].y])
    if not i < size - 1 or inst[i].type == "identifier" or inst[i].id != "k_from":
        return -1
    str = inst[i + 1].value[:-1]
    if not (str.endswith(".15") or str.endswith(".h15")):
        token = inst[-1]
        raise c15SyntaxError("Invalid folder extention in the import", token.x_start, token.x_end, token.y, file[token.y])
    return 0

def get_inst(progress, file, tokens, start, max):
    inst = []
    i = start

    if tokens[i].type != "identifier" and tokens[i].id == "k_error":
        progress.actual += 1
        progress_bar(progress.actual, progress.total)
        inst.append(tokens[i])
        return inst, i + 1

    while i < max and (tokens[i].type == "identifier" or tokens[i].id != "d_instruction_end"):
        progress.actual += 1
        progress_bar(progress.actual, progress.total)
        inst.append(tokens[i])
        i += 1
        if is_import(file, inst) == 0:
            if i < max and tokens[i].type == "delimitor" and tokens[i].id == "d_instruction_end":
                i += 1
                progress.actual += 1
            return inst, i
    if not i < max:
        is_import(file, inst)
        token = tokens[-1]
        raise c15SyntaxError("Invalid instruction, no end detected, probaply forgoten ';'", 1, token.x_end, token.y, file[token.y])
    progress.actual += 1
    return inst, i + 1

def check_syntax(progress, file, tokens):
    instructions = []
    token_nbr = len(tokens)
    i = 0

    while i < token_nbr:
        instruction, i = get_inst(progress, file, tokens, i, token_nbr);
        instructions.append(instruction)
    progress_bar(progress.actual, progress.total)
    for i in range(len(instructions)):
        instruction_checker(file, instructions, instructions[i], i)
    return instructions
