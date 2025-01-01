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
    for key in files_tokens.keys():
        print(f"{key}:")
        for token in files_tokens[key]:
            print(token)
        if key != list(files_tokens.keys())[-1]:
            print()
