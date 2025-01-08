##
## PYTHON PROJECT, 2025
## error_message_checker.py
## File description:
## Checker for error message
##

from error import c15SyntaxError

def check_error_message(file, token):
    print("Error")
    if token.value.count("@error@") > 1:
        raise c15SyntaxError("Multiple error message defined one a single ligne", token.x_start, token.x_end, token.y, file[token.y])
