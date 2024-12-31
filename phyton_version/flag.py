##
## PHYTON PROJECT, 2024
## flag.py
## File description:
## Flag initialisation
##

from error import c15ArgumentError
from pathlib import Path
from os import path

def get_files(path, option):
    extensions = ['.15', '.h15']
    directory_path = Path(path)
    return [option.files.append(str(file)) for ext in extensions for file in directory_path.rglob(f"*{ext}")]

def help_flag(i, arg):
    if i == 1:
        print("Help binary")
    elif arg == "-e":
        print("Help -e")
    elif arg == "-f":
        print("Help -f")
    else:
        print(f"No help for \"{arg}\"")

def help():
    print("Help")
    pass

def chek_arg_nbr(argument, argv, i, n):
    if len(argv) - 1 < i + n:
        raise c15ArgumentError("Invalid number of argument given", argument, argv, i)

def flag(argv, flag, i, option):
    if flag == "-e":
        chek_arg_nbr("binary_name", argv, i, 1)
        option.binary_name = argv[i + 1]
        return 1
    elif flag == "-f":
        chek_arg_nbr("direcroty_path", argv, i, 1)
        if not path.isdir(argv[i + 1]):
            argv.pop(i + 1)
            raise c15ArgumentError("Invalid directory path, can't access", "directory_path", argv, i)
        option.files_dir = argv[i + 1]
        get_files(argv[i + 1], option)
        return 1
    elif flag == "-h":
        help()
        exit()
    elif flag == "-H":
        help_flag(i, argv[i - 1])
        exit()
    return -1
