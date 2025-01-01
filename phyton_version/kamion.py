#!/bin/env python3
##
## PHYTON PROJECT, 2024
## kamion.py
## File description:
## Compiler main file
##

from lexer import extract_token
from error import c15UnknowTokenError, c15SyntaxeError, c15ArgumentError
from flag import flag, flag_help
from sys import argv
from os import path

class Option:

    def __init__(self):
        self.binary_name = "binary"
        self.files_dir = None
        self.files = []

file_tokens = {}
option = Option()
i = 1

argv[0] = "kmc"

try:
    if len(argv) < 2:
        raise c15ArgumentError("Invalid number of argument given", "files_path", argv, 0)
except c15ArgumentError as e:
    print(f"Call of compiler error")
    print(e)
    exit()

def check_file(arg):
    try:
        if not path.isfile(arg):
             raise c15ArgumentError("Invalid file path, can't acess", "", argv, i)
        if not (arg.endswith(".15") or arg.endswith(".h15")):
             raise c15ArgumentError(f"Invalid extension, need to be \".15\" or \".h15\"", "", argv, i)
    except c15ArgumentError as e:
        print(f"Invalid folder \"{arg}\"")
        print(e)
        exit()
    try:
        tokens = extract_token(arg)
        file_tokens[arg] = tokens
    except (c15UnknowTokenError, c15SyntaxeError) as e :
        print(f"Error while extract token of \"{arg}\"")
        print(e)
        exit()

for i in range(len(argv)):
    if argv[i][0] == "-":
        flag_help(argv[i], argv, i)

while i < len(argv):
    arg = argv[i]

    if arg[0] == "-":
        try:
            res = flag(argv, arg, i, option)
            if res < 0:
                raise c15ArgumentError("Unknow flag given", "", argv, i)
        except c15ArgumentError as e:
            print(f"Error while init flag \"{arg}\"")
            print(e)
            exit()
        i += 1 + res
        continue
    check_file(arg)
    i += 1

for file in option.files:
    check_file(file)

for key in file_tokens.keys():
    print(f"{key}:")
    for token in file_tokens[key]:
        print(token)
