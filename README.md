# my_language
### My own programming language "c15" with his compiler "kamion" or "kmc" for KaMion Compiler

The name "c15" has nothing to do with the `C` programming language, this is a private joke like the name of the compiler

## How use/install the compiler
Clone the repository:
```sh
git clone https://github.com/TsukiNi22/my_language.git
```

To create a link to the compiler (On Fedora / or use `ln -s absolute_path_to_kamion.py path_of_the_env_var_path`):
```sh
cd my_language/phyton_version
make
```

To use it or for more information use `-h`:
```sh
kmc files_path
```

## Language Description
This language is based on the `C`, with some difference and some other thing in more

The file extension is `.15` and for the header file `.h15`

| File extension | Utility                                                |
| -------------- | ------------------------------------------------------ |
| `.15`          | for the code                                           |
| `.15h`         | for prototype, set, .. (code can also be writen in it) |

## Compiler Advencement

| Task              | State                                                      |
| ----------------- | ---------------------------------------------------------- |
| Lexer             |  Token recuperation done / Check of the syntax in progress |
| Parser            |  Nothing                                                   |
| Semantic Analyzer |  Nothing                                                   |
| Optimizer         |  Nothing                                                   |
| Code Generation   |  Nothing                                                   |
| Linker            |  Nothing                                                   |

# A part of the new Thing/Different than in `C`:
| Comparator | Utility                                               |
| ---------- | ----------------------------------------------------- |
| `~=`       | `a ~= b` This is the same as `a -0.1 <= b <= a + 0.1` |

| Operator | Utility                                                                               |
| -------- | ------------------------------------------------------------------------------------- |
| `?`      | `?(34 + 23)` -> `true` / `1` That take the next thing and transform it into a boolean | 
| `^`      | `a^b` That a power b                                                                  | 
| `->`     | `->a` That retrive the value in a (a need to be a pointer)                            | 
| `<-`     | `<-a` That retrive the adress of the variable a (a need to be a pointer)              | 

| Data Type | Utility                                                                                                                                                        |
| --------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `bin`     | This type is for binary `bin var = 100110001;`                                                                                                                 | 
| `hex`     | This type is for the hexadeciaml `hex var = 0xf12ea8;`                                                                                                         | 
| `ptr`     | This type is for the pointer `ptr var = <-a;` or `ptr var = 0xf9f217423f;`                                                                                     | 
| `array`   | This is for the array `array var[] = [0, "string", 0xf38ea2]` or `array var[3] = {0}` that set every item of the array to the value between `{` and `}`        | 
| `link`    | This is for the linked list, the same declaration as an array but with the `link` type and only ptr in, that can also be initialize with `reversed` or `looped`| 

| Delimitor   | Utility                                                                                                                                                               |
| ----------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `@`         | `@This is a comment` After this anything in that ligne will be inogred by the compiler                                                                                | 
| `@>` / `<@` | `@> This is a comment <@` Anything between the start and the end will be ignored by the compiler, like this where there declaration work `int var @> comment <@ = 2;` | 

| Flow Controler | Utility                                                                                                                                                                                                   |
| -------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `&if`          | `&if (...)` That the same as an if but that also take the last conditon of an `if` or `elif` and add it to his own conditon with an `&&`                                                                  | 
| `error`        | `error "error_message", error_code;` That exit the programme with the error_code as value and an error message defined by the user (for some value it's already defined, can be overwrite)                | 
| `jump`         | `jump 34` or `jump function_name` The programme will go to the line or function to continue it's execution and will be back to the jump after a return or an end of a function `var = jump function_name` | 

| Key Word       | Utility                                                                                                                                               |
| -------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------- |
| `<<<`          | `stream_input <<< (buffer, nbr_to_write)` This is like a write `write(stream_input, buffer, nbr_to_write)`                                            | 
| `>>>`          | `(stream_ouput, nbr_to_read) >>> buffer` This is like a read `read(stream_ouput, buffer, nbr_to_read)`                                                | 
| `set`          | `set PY 3.14` This is like a define `#define PY 3.14`                                                                                                 | 
| `get` / `from` | `get` This is use with `from`, `get * from "exemple.15"` or `get thing_name from "exemple.15"` That will allow you to use something from another file | 
| `@error@`      | `@error@ Here a message error` If an error occur on the ligne where this is write after the ouput error message will be the text after `@error@`      | 
| `none`         | The `none` is write just before a function `none function() ...` to signal a function that will return nothing                                        | 
