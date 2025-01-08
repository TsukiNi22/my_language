#!/bin/env python3
##
## C15 PROGRAMING LANGUAGE PROJECT, 2024
## kamion.py
## File description:
## Compiler main file
##

from lexer import extract_token, check_syntax
from flag import flag, flag_help
from visualizer import display_file_info, display_error
from global_class import Option, Progress
from error import c15UnknowTokenError, c15SyntaxError, c15ArgumentError
from constant import OK, KO, COMPILER_NAME, EXT_SOURCE, EXT_HEADER
from sys import argv, stdout
from os import path

files_info = {}
error_message = {}
option = Option()
progress = Progress()

argv[0] = COMPILER_NAME

try:
    if len(argv) < 2:
        raise c15ArgumentError("Invalid number of argument given", "files_path", argv, 0)
except c15ArgumentError as e:
    print(f"Call of compiler error")
    print(e)
    exit(KO)

def check_file(file, i):
    try:
        if not path.isfile(file):
            if path.isdir(file):
                raise c15ArgumentError("This is a directory, a file is required", "", argv, i)
            raise c15ArgumentError("Invalid file path, can't acess", "", argv, i)
        if not (file.endswith(EXT_SOURCE) or file.endswith(EXT_HEADER)):
             raise c15ArgumentError(f"Invalid extension, need to be \"{EXT_SOURCE}\" or \"{EXT_HEADER}\"", "", argv, i)
    except c15ArgumentError as e:
        print(f"[33m[FATAL ERROR][0m Invalid file \"{file}\"")
        print(e)
        exit(KO)

def init():
    """ Flag For Help """
    for i in range(len(argv)):
        if argv[i][0] == "-":
            flag_help(argv[i], argv, i)
    
    """ Flag Initialisation + Check Given File """
    i = 1
    while i < len(argv):
        arg = argv[i]

        if arg[0] == "-":
            try:
                res = flag(argv, arg, i, option)
                if res < 0:
                    raise c15ArgumentError("Unknow flag given", "", argv, i)
            except c15ArgumentError as e:
                print(f"[33m[FATAL ERROR][0m Error while init flag \"{arg}\"")
                print(e)
                exit(KO)
            except PermissionError as e:
                i += 1 + (arg == "-d" or arg == "--directory" or arg == "-D" or arg == "--DIRECTORY")
                continue
            i += 1 + res
            continue
        check_file(arg, i)
        option.files.append(arg)
        i += 1

def kamion():
    """ Set Progress Bar """
    for file in option.files:
        try:
            for line in open(file).read().split("\n"):
                progress.total += len(line)
        except UnicodeDecodeError as e:
            print(f"[33m[FATAL ERROR][0m Error while reading \"{file}\"[31m")
            print(e)
            exit(KO)

    """ Token Extraction """
    for file in option.files:
        files_info[file] = {}
        files_info[file]["Content"] = open(file).read().split("\n")
        progress.for_start = progress.actual
        try:
            tokens = extract_token(progress, file)
            files_info[file]["Tokens"] = tokens
        except (c15UnknowTokenError, c15SyntaxError) as e :
            if option.multiple_error:
                progress.actual += sum(len(line) for line in files_info[file]["Content"]) - (progress.actual - progress.for_start)
                stdout.write('\033[F')
                error_message[file] = [f"Error while extract token of \"{file}\"", e]
            else:
                print(f"Error while extract token of \"{file}\"")
                print(e)
                exit(KO)

    """ Set Progress Bar """
    progress.reset()
    for key in files_info.keys() - error_message.keys():
        progress.total += len(files_info[key]["Tokens"])

    """ Syntax Check """
    for key in files_info.keys() - error_message.keys():
        file_info = files_info[key]
        progress.for_start = progress.actual
        try:
            instructions = check_syntax(progress, file_info["Content"], file_info["Tokens"])
            files_info[key]["Instructions"] = instructions
        except c15SyntaxError as e :
            if option.multiple_error:
                progress.actual += len(files_info[key]["Tokens"]) - (progress.actual - progress.for_start)
                stdout.write('\033[F')
                error_message[key] = [f"Error during the check of syntax for \"{key}\"", e]
            else:
                print(f"Error during the check of syntax for \"{key}\"")
                print(e)
                exit(KO)

if __name__ == "__main__":
    
    try:
        init()
        kamion()
    except KeyboardInterrupt:
        print()
        exit(KO)

    print()
    display_file_info(files_info, error_message.keys())
    if option.multiple_error:
        display_error(error_message)
exit(OK)
