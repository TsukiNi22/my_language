##
## PHYTON PROJECT, 2024
## error.py
## File description:
## Error class
##

class c15UnknowTokenError(Exception):

    def __init__(self, x, y, line):
        str = f"[31mUnknwon Token Error: [35mCan't identifie this\n"
        str += "[33m-----------------------------------\n"
        str += f"{y + 1} | "
        str += "[32m"
        str += line[:x]
        str += "[31m"
        str += line[x:]
        str += "\n"
        for i in range(x + len(f"{y + 1} | ")):
            str += " "
        str += "[0m"
        for i in range(len(line) - x):
            str += "^"
        str += "\n"
        str += "[33m-----------------------------------"
        super().__init__(str)

class c15SyntaxeError(Exception):

    def __init__(self, msg, x_start, x_end, y, line):
        str = f"[31mSyntaxe Error: [35m"
        str += msg
        str += "\n"
        str += "[33m-----------------------------------\n"
        str += f"{y + 1} | "
        str += "[32m"
        str += line[:x_start]
        str += "[31m"
        str += line[x_start:x_end]
        str += "[32m"
        str += line[x_end:]
        str += "\n"
        for i in range(x_start + len(f"{y + 1} | ")):
            str += " "
        str += "[0m"
        for i in range(x_end - x_start):
            str += "^"
        str += "\n"
        str += "[33m-----------------------------------"
        super().__init__(str)

class c15ArgumentError(Exception):

    def __init__(self, msg, argument, argv, i):
        size = 0
        str = f"[31mArgument Error: [35m"
        str += msg
        str += "\n"
        str += "[33m-----------------------------------\n"
        str += "[32m"
        for arg in argv[:i]:
            str += arg + " "
            size += len(arg) + 1
        str += "[31m"
        str += argv[i] + " "
        str += "[36m"
        str += argument
        if len(argument) > 0:
            str += " "
        str += "[32m"
        for arg in argv[i + 1:]:
            str += arg + " "
        str += "\n"
        str += "[0m"
        for j in range(size):
            str += " "
        for j in range(len(argv[i]) + len(argument)):
            str += "^"
        if len(argument) > 0:
            str += "^"
        str += "\n"
        str += "[33m-----------------------------------"
        super().__init__(str)


