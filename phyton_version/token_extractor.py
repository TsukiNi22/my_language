##
## PHYTON PROJECT, 2024
## token_extractor.py
## File description:
## Extract the token
##

from lexicon_unit import *
from global_class import Token
from error import UnknowTokenError
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
        var.id = "l_number"
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

def eval_ligne(tokens, line, y):
    word_l = []
    last = False
    x = 0

    var = Var()
    for char in line:
        var.actual = False
        word_l.append(char)
        word = "".join(word_l).strip()

        check(word, var)
        if last and not var.actual:
            word = word[:-1].strip()
            dif = len(word)
            tokens.append(Token(var.type, var.id, x, x + dif - 1, y, var.value))
            x += dif
            word_l = word_l[-1:]
            word = "".join(word_l).strip()
            var.reset()
        check(word, var)
        last = var.actual
    if var.actual:
        dif = len(word) - 1
        tokens.append(Token(var.type, var.id, x, x + dif, y, var.value))
    elif len(word_l) != 0:
        raise UnknowTokenError(x, y, line)    

def extract_token(file_path):
    tokens = []
    file = open(file_path).read()
    y = 0

    for line in file.split("\n"):
        eval_ligne(tokens, line, y)
        y += 1
    return tokens
