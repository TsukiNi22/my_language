##
## PHYTON PROJECT, 2024
## flag.py
## File description:
## Flag initialisation
##

from pathlib import Path

def get_files(path, option):
    extensions = ['.15', '.h15']
    directory_path = Path(path)
    return [option.files.append(str(file)) for ext in extensions for file in directory_path.rglob(f"*{ext}")]

def flag(argv, flag, i, option):
    if flag == "-e":
        option.binary_name = argv[i + 1]
        return 1
    elif flag == "-f":
        option.files_dir = argv[i + 1]
        get_files(argv[i + 1], option)
        return 1
    return -1
