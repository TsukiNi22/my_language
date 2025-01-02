##
## C15 PROGRAMING LANGUAGE PROJECT, 2024
## visualizer.py
## File description:
## visualizer
##

from sys import stdout

def progress_bar(actual, total):
    size = 100
    percent = actual / total
    block = int(size * percent)
    bar = "[32m" + "/" * block + "[31m" + "-" * (size - block) + "[0m"
    stdout.write(f"\r[{bar}] {actual}/{total} ({percent * 100:.2f}%)")
    stdout.flush()

def display_tokens(files_tokens):
    for token in files_tokens:
        print(token)

def display_inst(files_inst):
    for insts in files_inst:
        for inst in insts:
            print(inst)
        if insts != files_inst[-1]:
            print()

def display_file_info(files_info):
    for key in files_info.keys():
        print("-" * 125)
        print(f"{key}:")
        print()
        display_inst(files_info[key]["Instructions"])
