#!/bin/env python3
##
## PHYTON PROJECT, 2024
## kamion.py
## File description:
## Compiler main file
##

from token_extractor import extract_token
from error import UnknowTokenError
from sys import argv

file_tokens = {}

if len(argv) < 2:
    print("No file given")
    exit()

for i in range(len(argv)):
    arg = argv[i]

    if i == 0:
        continue
    try:
        open(arg)
    except:
        print("Invalid Folder")
        exit()
    if not (arg.endswith(".15") or arg.endswith(".h15")):
        print("Invalid Extension, need to be \".15\" or \".h15\"")
        exit()
    try:
        tokens = extract_token(arg)
        file_tokens[arg] = tokens
    except UnknowTokenError as e:
        print(f"Error while extract token of \"{arg}\":\n{e}")
        exit()
for key in file_tokens.keys():
    print(f"{key}:")
    for token in file_tokens[key]:
        print(token)
