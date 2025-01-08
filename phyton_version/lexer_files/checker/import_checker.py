##
## PYTHON PROJECT, 2025
## import_checker.py
## File description:
## Checker for import
##

from constant import EXT_SOURCE, EXT_HEADER
from error import c15SyntaxError

def check_import(file, inst):
    print("Import")
    import_declaration = ", need to be \"get * from \"file_name\"\" or \"get [thing_name]+ from \"file_name\"\""
    get_everything = False
    size = len(inst)
    get_tok = None
    for tok in inst:
        if tok.type == "key_word" and tok.id == "k_get":
            get_tok = tok
            break
    from_tok = None
    for tok in inst:
        if tok.type == "key_word" and tok.id == "k_from":
            from_tok = tok
            break
    x_end = max(tok.x_end for tok in inst if tok.y == inst[0].y)

    if not get_tok:
        raise c15SyntaxError("Need a \'get\' in a import instruction" + import_declaration, 1, x_end , from_tok.y, file[from_tok.y])
    if not from_tok:
        raise c15SyntaxError("Need a \'from\' in a import instruction" + import_declaration, 1, x_end , get_tok.y, file[get_tok.y])
    if sum(1 for tok in inst if (tok.type == "key_word" and tok.id == "k_get")) != 1:
        raise c15SyntaxError("Multiple \'get\', only one at the same time" + read_declaration, 1, x_end, get_tok.y, file[get_tok.y])
    if sum(1 for tok in inst if (tok.type == "key_word" and tok.id == "k_get")) != 1:
        raise c15SyntaxError("Multiple \'from\', only one at the same time" + read_declaration, 1, x_end, from_tok.y, file[from_tok.y])
    if size < 4:
        raise c15SyntaxError("Invalid declaration of an import, less things than needed" + import_declaration, 1, x_end, get_tok.y, file[get_tok.y])
    if inst[0] != get_tok:
        raise c15SyntaxError("Invalid positionement of \'get\'" + import_declaration, get_tok.x_start, get_tok.x_end, get_tok.y, file[get_tok.y])
    if any((not (tok.type == "literal" and tok.id == "l_string")) for tok in inst[inst.index(from_tok) + 1:]):
        raise c15SyntaxError("Only a file_name can be given after \'from\'" + import_declaration, from_tok.x_end + 1, x_end, get_tok.y, file[get_tok.y])
    if sum(1 for tok in inst[inst.index(from_tok) + 1:] if (tok.type == "literal" and tok.id == "l_string")) > 1:
        raise c15SyntaxError("Only 1 file_name can be given at the same time" + import_declaration, from_tok.x_end + 1, x_end, get_tok.y, file[get_tok.y])
    if inst[-2] != from_tok:
        raise c15SyntaxError("Invalid positionement of \'from\'" + import_declaration, from_tok.x_start, from_tok.x_end, from_tok.y, file[from_tok.y])
    tok_to_import = inst[1:-2]
    for tok in tok_to_import:
        if tok.type == "operator" and tok.id == "o_multiplie":
            if get_everything:
                raise c15SyntaxError("Can't import everything with \'*\' and other at the same time", tok.x_start, from_tok.x_start - 1, get_tok.y, file[get_tok.y])
            get_everything = True
        elif tok.type == "identifier":
            if get_everything:
                raise c15SyntaxError("Can't import everything with \'*\' and other at the same time", tok.x_start, from_tok.x_start - 1, get_tok.y, file[get_tok.y])
        else:
            raise c15SyntaxError("Invalid thing to import", tok.x_start, tok.x_end, get_tok.y, file[get_tok.y])
    str = inst[-1].value[1:-1]
    if str == "" or str == EXT_SOURCE or str == EXT_HEADER:
        raise c15SyntaxError("Invalid folder in the import", inst[-1].x_start, x_end, get_tok.y, file[get_tok.y])
    if not (str.endswith(EXT_SOURCE) or str.endswith(EXT_HEADER)):
        raise c15SyntaxError("Invalid folder extention in the import", inst[-1].x_start, x_end, get_tok.y, file[get_tok.y])
