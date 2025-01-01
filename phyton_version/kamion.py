#!/bin/env python3
##
## C15 PROGRAMING LANGUAGE PROJECT, 2024
## kamion.py
## File description:
## Compiler main file
##

from lexer import extract_token, check_syntax
from flag import flag, flag_help
from visualizer import display_tokens
from error import c15UnknowTokenError, c15SyntaxeError, c15ArgumentError
from sys import argv
from os import path

class Option:

    def __init__(self):
        self.binary_name = "binary"
        self.files_dir = None
        self.files = []

class Progress:

    def __init__(self):
        self.actual = 0
        self.total = 0

files_tokens = {}
option = Option()
progress = Progress()

argv[0] = "kmc"

try:
    if len(argv) < 2:
        raise c15ArgumentError("Invalid number of argument given", "files_path", argv, 0)
except c15ArgumentError as e:
    print(f"Call of compiler error")
    print(e)
    exit()

def check_file(file):
    try:
        if not path.isfile(file):
             raise c15ArgumentError("Invalid file path, can't acess", "", argv, i)
        if not (file.endswith(".15") or file.endswith(".h15")):
             raise c15ArgumentError(f"Invalid extension, need to be \".15\" or \".h15\"", "", argv, i)
    except c15ArgumentError as e:
        print(f"Invalid file \"{file}\"")
        print(e)
        exit()

i = 1
for i in range(len(argv)):
    if argv[i][0] == "-":
        flag_help(argv[i], argv, i)

i = 1
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
    option.files.append(arg)
    i += 1

for file in option.files:
    for line in open(file).read().split("\n"):
        progress.total += len(line)

for file in option.files:
    try:
        tokens = extract_token(progress, file)
        files_tokens[file] = tokens
    except (c15UnknowTokenError, c15SyntaxeError) as e :
        print(f"Error while extract token of \"{file}\"")
        print(e)
        exit()
    try:
        check_syntax(open(file).read().split("\n"), tokens)
    except c15SyntaxeError as e :
        print(f"Error during the check of syntax for \"{file}\"")
        print(e)
        exit()

print()
display_tokens(files_tokens)
