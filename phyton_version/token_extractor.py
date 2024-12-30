#!/bin/env python3
##
## PHYTON PROJECT, 2024
## token_extractor.py
## File description:
## Extract the token
##

from lexicon_unit import *
from re import fullmatch
from sys import argv

class Token():
    
    def __init__(self, type = "Unknow", id = "Unknow", x_start = -1, x_end = -1, y = -1, value = None):
        self.type = type
        self.id = id
        self.x_start = x_start
        self.x_end = x_end
        self.y = y
        self.value = value

    def __str__(self):
        return f"Type ({self.type:10}), \tId ({self.id:22}), \tValue ({self.value}), \tPosition ({self.x_start}, {self.y}) -> ({self.x_end}, {self.y})"

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
            print(word)
            dif = len(word) - 1
            tokens.append(Token(var.type, var.id, x, x + dif, y, var.value))
            x += dif
            word_l = word_l[-1:]
            var.reset()
        check(word, var)
        last = var.actual

def extract_token(file_path):
    tokens = []
    file = open(file_path).read()
    y = 0

    for line in file.split("\n"):
        eval_ligne(tokens, line, y)
        y += 1
    return tokens

for token in extract_token(argv[1]):
    print(token)
