#!/bin/env python3
##
## PHYTON PROJECT, 2024
## kamion.py
## File description:
## Compiler main file
##

from lexer import extract_token
from error import c15UnknowTokenError, c15SyntaxeError
from flag import flag
from sys import argv

class Option:

    def __init__(self):
        self.binary_name = "binary"
        self.files_dir = None
        self.files = []

file_tokens = {}
option = Option()
i = 1

if len(argv) < 2:
    print("No file given")
    exit()

def check_file(arg):
    try:
        open(arg)
    except:
        print(f"Invalid folder \"{arg}\"")
        exit()
    if not (arg.endswith(".15") or arg.endswith(".h15")):
        print(f"Invalid extension \"{arg}\", need to be \".15\" or \".h15\"")
        exit()
    try:
        tokens = extract_token(arg)
        file_tokens[arg] = tokens
    except (c15UnknowTokenError, c15SyntaxeError) as e:
        print(f"Error while extract token of \"{arg}\"")
        print(e)
        exit()

while i < len(argv):
    arg = argv[i]

    if arg[0] == "-":
        res = flag(argv, arg, i, option)
        if res < 0:
            print(f"Invalid flag \"{arg}\"")
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
