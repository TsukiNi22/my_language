##
## C15 PROGRAMING LANGUAGE PROJECT, 2024
## syntax_checker.py
## File description:
## Check the syntaxe of the file
##

from lexer import instruction_checker
from visualizer import progress_bar
from error import c15SyntaxError

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
        if any((tok.type == "key_word" and tok.id == "k_get") for tok in inst) or any((tok.type == "key_word" and tok.id == "k_from") for tok in inst):
            while i < max and (tokens[i].type == "identifier" or tokens[i].id != "d_instruction_end") and tokens[i].y == inst[0].y:
                progress.actual += 1
                progress_bar(progress.actual, progress.total)
                inst.append(tokens[i])
                i += 1
            if i < max and tokens[i].type == "delimitor" and tokens[i].id == "d_instruction_end":
                raise c15SyntaxError("Can't place a ';' after an import", tokens[i].x_start, tokens[i].x_end, tokens[i].y, file[tokens[i].y])
            return inst, i
    if not i < max:
        raise c15SyntaxError("Invalid instruction, no end detected, probaply forgoten ';'", 1, tokens[-1].x_end, tokens[-1].y, file[tokens[-1].y])
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
    i = 0
    while i < len(instructions):
        instruction_checker(file, instructions, instructions[i], i)
        i += 1
    return instructions
