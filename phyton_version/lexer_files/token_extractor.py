##
## C15 PROGRAMING LANGUAGE PROJECT, 2024
## token_extractor.py
## File description:
## Extract the token of a file
##

from global_class import Token
from visualizer import progress_bar
from error import c15UnknowTokenError, c15SyntaxeError
from .lexicon_unit import *
from re import fullmatch

class Var():

    def __init__(self):
        self.type = "Unknow"
        self.id = "Unknow"
        self.value = None
        self.actual = False

    def reset(self):
        self.type = "Unknow"
        self.id = "Unknow"
        self.value = None
        self.actual = False

def is_key_word(word, var):
    if word in comparator.keys():
        var.type = "comparator"
        var.id = comparator[word]
        return True
    if word in operator.keys():
        var.type = "operator"
        var.id = operator[word]
        return True
    if word in data_type.keys():
        var.type = "data_type"
        var.id = data_type[word]
        return True
    if word in delimitor.keys():
        var.type = "delimitor"
        var.id = delimitor[word]
        return True
    if word in flow_controler.keys():
        var.type = "flow_controler"
        var.id = flow_controler[word]
        return True
    if word in key_word.keys():
        var.type = "key_word"
        var.id = key_word[word]
        return True
    return False

def is_literal(word, var):
    if word == "true" or word == "false":
        var.id = "l_boolean"
        return True
    if fullmatch(r"0x[0-9a-f]*", word):
        var.id = "l_hex"
        return True
    if fullmatch(r"[01]+", word):
        var.id = "l_binary"
        return True
    if fullmatch(r"-?(?:[1-9]\d*|0)?(?:\.\d*)?", word):
        if "." in word:
            var.id = "l_float"
        else:
            var.id = "l_integer"
        return True
    if fullmatch(r'^"([^"\\]*(\\.)?)*"$', word):
        var.id = "l_string"
        return True
    if fullmatch(r"^'(\\.|[^'\\])'$", word):
        var.id = "l_char"
        return True
    return False

def is_identifier(word):
    if fullmatch(r'\b[a-zA-Z_][a-zA-Z0-9_]*\b', word):
        return True
    return False

def check(word, var):
    if is_key_word(word, var):
        var.actual = True
    elif is_literal(word, var):
        var.type = "literal"
        var.value = word
        var.actual = True
    elif is_identifier(word):
        var.type = "identifier"
        var.id = word
        var.actual = True
    return var

def eval_ligne(progress, tokens, comment, line, y):
    word_l = []
    last = False
    x = 1

    var = Var()
    for char in line:
        progress.actual += 1
        progress_bar(progress.actual, progress.total)
        var.actual = False
        word_l.append(char)
        word = "".join(word_l).strip()

        check(word, var)
        if not comment and not var.actual and var.id == "d_comment":
            if line[x - 1:x + 6] == "@error@":
                var.type = "key_word"
                var.id = "k_error"
                var.value = line[x - 1:]
                tokens.append(Token(var.type, var.id, x, x + len(var.value) - 1, y, var.value))
            progress.actual += len(line) - (x - 1) - (2 + word_l.count(" "))
            return False
        elif var.id == "d_comment_start":
            comment = True
        elif var.id == "d_comment_end":
            if not comment:
                raise c15SyntaxeError("End of a comment, but no start has been set", x, x + 1, y, line)    
            comment = False
            word_l.clear()
            continue
        if comment:
            if len(word_l) > 0 and word_l [0] != "<":
                word_l.clear()
            continue
        if last and not var.actual:
            word = word[:-1].strip()
            tokens.append(Token(var.type, var.id, x, x + len(word) - 1, y, var.value))
            x += len(word_l) - 1
            word_l = word_l[-1:]
            word = "".join(word_l).strip()
            var.reset()
        check(word, var)
        last = var.actual
    if comment:
        return True
    if var.actual and word != "<@" and word != "@":
        dif = len(word) - 1
        tokens.append(Token(var.type, var.id, x, x + dif, y, var.value))
    elif len(word_l) != 0 and word != "<@" and word != "@":
        raise c15UnknowTokenError(x - 1, y, line)    
    return False

def extract_token(progress, file_path):
    tokens = []
    file = open(file_path).read()
    comment = False
    y = 0

    for line in file.split("\n"):
        comment = eval_ligne(progress, tokens, comment, line, y)
        y += 1
    progress_bar(progress.actual, progress.total)
    return tokens
