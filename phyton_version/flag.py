##
## PHYTON PROJECT, 2024
## flag.py
## File description:
## Flag initialisation
##

from error import c15ArgumentError
from pathlib import Path
from os import path

def get_files(path, option, rec = True):
    extensions = ['.15', '.h15']
    directory_path = Path(path)
    for ext in extensions:
        if rec:
            files = directory_path.rglob(f"*{ext}");
        else:
            files = directory_path.glob(f"*{ext}");
        for file in files:
            if not file in option.files:
                option.files.append(str(file))

def chek_arg_nbr(argument, argv, i, n):
    if len(argv) - 1 < i + n:
        raise c15ArgumentError("Invalid number of argument given", argument, argv, i)

def flag(argv, flag, i, option):
    if flag == "-b":
        chek_arg_nbr("binary_name", argv, i, 1)
        option.binary_name = argv[i + 1]
        return 1
    elif flag == "-d" or flag == "--directory" or flag == "-D" or flag == "--DIRECTORY":
        chek_arg_nbr("direcroty_path", argv, i, 1)
        if not path.isdir(argv[i + 1]):
            raise c15ArgumentError("Invalid directory path, can't access", "", argv, i + 1)
        option.files_dir = argv[i + 1]
        get_files(argv[i + 1], option, (flag == "-F"))
        return 1
    return -1

def help_flag(i, arg):
    if i == 1:
        str = "[32mINFORMATION:\n"
        str += "\tThat the compiler for program write in c15\n"
        str += "[35mUSAGE:\n"
        str += "\tkmc files_path\n"
        str += "\tkmc -h"
        print(str)
    elif arg == "-b" or flag == "--binary":
        str = "[32mINFORMATION:\n"
        str += "\tThat will change the name of the output binary to the given name\n\n"
        str += "[35mUSAGE:\n"
        str += "\t-b binary_name"
        print(str)
    elif arg == "-d" or flag == "--directory":
        str = "[32mINFORMATION:\n"
        str += "\tThat will add the files found without recursive in the given directory\n"
        str += "\tpath with [35m\".15\"[32m or [35m\".h15\"[32m in the list of file to compile\n\n"
        str += "[35mUSAGE:\n"
        str += "\t-d directory_path"
        print(str)
    elif arg == "-D" or flag == "--DIRECTORY":
        str = "[32mINFORMATION:\n"
        str += "\tThat will add the files found recursively in the given directory\n"
        str += "\tpath with [35m\".15\"[32m or [35m\".h15\"[32m in the list of file to compile\n\n"
        str += "[35mUSAGE:\n"
        str += "\t-D directory_path"
        print(str)
    else:
        print(f"No help for \"{arg}\"")

def help():
    str = "[36mPROJECT\n"
    str += "\tThis project is a compiler for the language [35m\'c15\'[36m\n"
    str += "\tThe name of the compiler is [35m\'kamion\'[36m or [35m\'kmc\'\n\n"
    str += "[32mINFORMATION\n"
    str += "\t-Multiple flag will overwrite the first!!!\n"
    str += "\t-At least one file_path must be given or use the [35m\'-f\'[32m / [35m\'-F\'\n\n"
    str += "[35mUSAGE\n"
    str += "\tkmc [files_path] [-b binary_name] [-d directory_path] [-D directory_path]\n"
    str += "\tkmc -h\n"
    str += "\tkmc [option] -H\n\n"
    str += "[0mOPTIONS\n"
    str += "\t[32m-h, --help[0m\n"
    str += "\t\tWrite the informations of the executable\n"
    str += "\t[[31moption[0m] [32m-H, -HELP[0m\n"
    str += "\t\tWrite all the informations about the [31moption\n"
    str += "\t[32m-b, --binary [31mbinary_name[0m\n"
    str += "\t\tChange the name of the output executable to the given [31mbinary_name[0m (default: \'[31mbinary[0m\')\n"
    str += "\t[32m-d, --directory [31mdirectory_path[0m\n"
    str += "\t\tAdd the files found without recursive in the given [31mdirectory_path[0m in the list of file to compile\n"
    str += "\t[32m-D, --DIRECTORY [31mdirectory_path[0m\n"
    str += "\t\tAdd the files found recursively in the given [31mdirectory_path[0m in the list of file to compile"
    print(str)
    pass

def flag_help(flag, argv, i):
    if flag == "-h" or flag == "--help":
        help()
        exit()
    elif flag == "-H" or flag == "--HELP":
        help_flag(i, argv[i - 1])
        exit()
