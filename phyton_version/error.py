#!/bin/env python3
##
## PHYTON PROJECT, 2024
## error.py
## File description:
## Error class
##

class UnknowTokenError(Exception):

    def __init__(self, x, y, line):
        str = f"[35mCan't identifie token:\n"
        str += "[33m-----------------------------------\n"
        str += f"{y + 1} | "
        str += "[32m"
        str += line[:x]
        str += "[31m"
        str += line[x:]
        str += "\n"
        for i in range(x + len(f"{y + 1} | ")):
            str += " "
        str += "[0m^"
        for i in range(len(line) - x - 2):
            str += "-"
        str += "^\n"
        str += "[33m-----------------------------------"
        super().__init__(str)
