##
## C15 PROGRAMING LANGUAGE PROJECT, 2024
## class.py
## File description:
## File for class
##

class Option:

    def __init__(self):
        self.binary_name = "binary"
        self.multiple_error = False
        self.files_dir = None
        self.files = []

class Progress:

    def __init__(self):
        self.actual = 0
        self.total = 0
        self.for_start = 0

    def reset(self):
        print()
        self.actual = 0
        self.total = 0

class Token():
    
    def __init__(self, type = "Unknow", id = "Unknow", x_start = -1, x_end = -1, y = -1, value = None):
        self.type = type
        self.id = id
        self.x_start = x_start
        self.x_end = x_end
        self.y = y
        self.value = value

    def __str__(self):
        return f"Type ({self.type:14}), \tId ({self.id:22}), \tValue ({self.value}), \tPosition ({self.x_start}, {self.y}) -> ({self.x_end}, {self.y})"
