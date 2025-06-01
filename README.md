# my_language
### My own programming language "c15" with his compiler "kamion" or "kmc" standing for KaMion Compiler
## Language Description

The name "c15" has nothing to do with the `C` programming language, this is a private joke like the name of the compiler

This language is based on the `C` syntax, with some difference and some other thing in more, i designed it has how i wanted it to be and with what i wanted.

There probably a bunch of bug, if you find one and want to contribute send me someting here (c15.tsukini@gmail.com)

| File extension | Utility                                                |
| -------------- | ------------------------------------------------------ |
| `.15`          | for the code                                           |
| `.15h`         | for prototype, set, ... (code can't be writen in it)   |

## How use/install the compiler
Clone the repository:
```sh
git clone https://github.com/TsukiNi22/my_language.git c15
```

To create a link to the compiler:
```sh
cd c15
make sys_cmd -C compiler
```

To use it or for more information use `-h` or `--help`:
```sh
kmc files_path
```
For language syntax or more information go to the file in the branch `wiki`

## How to customize the compiler

------
### <i>To change the token detection</i>
Open the file `compiler/src/const.c`, you can see it here [const.c](https://github.com/TsukiNi22/my_language/blob/main/compiler/src/const.c)

You will see a list of string like below in the list named `token_str`:
```c
    "=",         // op_eq
```
If you change the `"="` to `"test"` for exemple. The compiler will now compile each file with this string `test` who will be interpreted as `=` in the executable.

<i>The changement of `"@>"` & `"<@"` is not handle for now! or also change the line 260 & 262 (line number can be a little different) in the file `compiler/src/tokenizer/tokenizer.c`, you can also see it here [tokenizer.c](https://github.com/TsukiNi22/my_language/blob/main/compiler/src/tokenizer/tokenizer.c) </i>

------
### <i>To change the default binary name & file extension:</i>
Open the file `compiler/include/kamion.h`, you can see it here [kamion.h](https://github.com/TsukiNi22/my_language/blob/main/compiler/include/kamion.h)

You will see a multiple define like below:
```c
    /* extension */
    #define FILE_EXTENSION ".15"
    #define HEADER_EXTENSION ".15h"

    /* files_name */
    #define BINARY_NAME "15.out"
```
If you want to change the extension of the file just change the two string `".15"` & `".15h"` as you want.

If you want to change the default binary name just change the string `"15.out` as you want.

------
### <i>To change the option name:</i>
Open the file `compiler/src/const.c`, you can see it here [const.c](https://github.com/TsukiNi22/my_language/blob/main/compiler/src/const.c)

You will see a list of string like below in the list named `flags` & `full_flags`:
```c
    'h',
    "--help",
```
The first type of option stored in `flags` like `'h'` can only be a character and can't be `-`.

The second type of option stored in `full_flags` like `"--help"`, they must start with `--`. The other characters can be anything.

---
### <i>Apply the changement:</i>
After the changement are made do this at the root of the project file:
```bash
make fclean sys_cmd -C compiler
```
Or this in the compiler file:
```bash
make fclean sys_cmd
```

### ⚠️ Please note that, if you change any file content in the wrong way you may break the whole compiler!!! ⚠️

## Compiler Advencement made in `C`

| Task              | State        |
| ----------------- | ------------ |
| Lexer             |  Done        |
| Parser            |  In progress |
| Semantic Analyzer |  Nothing     |
| Optimizer         |  Nothing     |
| Code Generation   |  Nothing     |
| Linker            |  Nothing     |
