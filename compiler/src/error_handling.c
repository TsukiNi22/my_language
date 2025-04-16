/**************************************************************\

 ██╗  ██╗ █████╗ ██████╗ ████████╗ █████╗ ███╗   ██╗██╗ █████╗ 
 ╚██╗██╔╝██╔══██╗██╔══██╗╚══██╔══╝██╔══██╗████╗  ██║██║██╔══██╗
  ╚███╔╝ ███████║██████╔╝   ██║   ███████║██╔██╗ ██║██║███████║
  ██╔██╗ ██╔══██║██╔══██╗   ██║   ██╔══██║██║╚██╗██║██║██╔══██║
 ██╔╝ ██╗██║  ██║██║  ██║   ██║   ██║  ██║██║ ╚████║██║██║  ██║
 ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝

Edition:
##  16/04/2025 by Tsukini

File Name:
##  error_handling.c

File Description:
## Handle error from the compiler
## not intern error
\**************************************************************/

#include "define.h"     // STDERR & STDOUT define
#include "write.h"      // my_printf function
#include "my_math.h"    // my_log function
#include "my_string.h"  // string functions
#include "kamion.h"     // compiler_t type
#include "error.h"      // error handling
#include <stddef.h>     // size_t type, NULL define
#include <stdbool.h>    // bool type

/* Syntax error function
----------------------------------------------------------------
 * Handle error from the syntax in the file
----------------------------------------------------------------
##  data -> main data structure
##  to_return -> the return value
##  file -> file where the error is located
##  n -> line of the error
##  type -> type of the error
##  err -> the error message
##  line -> the line where the error have occured
##  start -> the x° char where the error start
##  end -> the x° char where the error end
##  warning -> a bool, true if it's a warning
----------------------------------------------------------------
*/
int err_c15(compiler_t *data, int to_return,
    char const *file, size_t n,
    char const *type, char const *err, char const *line,
    size_t start, size_t end, bool warning)
{
    int ouput = STDERR;
    int res = 0;

    // Check for potential null pointer
    if (!data || !file || (!type && !warning) || !err || !line)
        return err_prog(PTR_ERR, KO, ERR_INFO);

    // setup of the ouput to standart ouput if it's a warging
    if (warning)
        ouput = STDOUT;

    data->err_sys = true;
    data->nb_warning += warning;
    data->nb_error += !warning;

    // Write the error/warning message
    if (data->nb_warning + data->nb_error > 1)
        res += my_putchar(ouput, '\n');
    if (!warning) {
        res += my_printf("%O%C%S[Error n°%d]%R %S%s:%u:%u%R -> %s: %s%R\n", ouput, 205, 0, 0, data->nb_error, file, n, start, type, err);
    } else {
        res += my_printf("%O%C%S[Warging n°%d]%R %S%s:%u:%u%R -> %s: %s%R\n", ouput, 175, 0, 175, data->nb_warning, file, n, start, type, err);
    }
    res += my_printf("%O%C-------------------------------------------%R\n", ouput, 175, 100, 0);
    res += my_printf("%O%C%d | %S%C%.*s%C%.*s%C%s%R\n", ouput,
    175, 100, 0, n,
    0, 125, 0, start - 1, line,
    175 - 30 * warning, 0, 150 * warning, end - (start - 1), &line[start - 1],
    0, 125, 0, &line[end]);
    for (size_t i = 0; i < 3 + my_log(n, 10) + (start - 1); i++)
        res += my_putchar(ouput, ' ');
    for (size_t i = 0; i < end - (start - 1); i++)
        res += my_putchar(ouput, '^');
    res += my_putchar(ouput, '\n');
    res += my_printf("%O%C-------------------------------------------%R\n", ouput, 175, 100, 0);
    if (res != OK)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    return to_return;
}

/* Argument error function
----------------------------------------------------------------
 * Handle error from the argument at the execution
----------------------------------------------------------------
##  data -> main data structure
##  to_return -> the return value
##  type -> type of the error
##  err -> the error message
##  arg -> argument where the error have occured
##  warning -> a bool, true if it's a warning
----------------------------------------------------------------
*/
int err_kmc_arg(compiler_t *data, int to_return,
    char const *type, char const *err,
    char const *arg, char const *should,
    bool warning)
{
    int lens[3] = {0};
    int ouput = STDERR;
    int res = 0;
    int index = 0;

    // Check for potential null pointer
    if (!data || (!type && !warning) || !err)
        return err_prog(PTR_ERR, KO, ERR_INFO);

    // setup of the ouput to standart ouput if it's a warning
    if (warning)
        ouput = STDOUT;

    lens[0] = my_strlen(arg);
    lens[1] = my_strlen(should);
    lens[2] = 0;
    if ((arg && lens[0] == KO) || (should && lens[1] == KO))
        return err_prog(UNDEF_ERR, KO, ERR_INFO);

    data->err_sys = true;
    data->nb_warning += warning;
    data->nb_error += !warning;

    // Write the error/warning message
    if (data->nb_warning + data->nb_error > 1)
        res += my_putchar(ouput, '\n');
    if (!warning) {
        res += my_printf("%O%C%S[Error n°%d]%R %s: %s.\n", ouput, 205, 0, 0, data->nb_error, type, err);
    } else {
        res += my_printf("%O%C%S[Warging n°%d]%R %s: %s.\n", ouput, 175, 0, 175, data->nb_warning, type, err);
    }
    res += my_printf("%O%C-------------------------------------------%R\n", ouput, 175, 100, 0);
    if (!should && arg) {
        res += my_putchar(ouput, ' ');
        res += color_rgb(ouput, 0, 125, 0);
        for (index = 0; data->argv[index] != arg; index++) {
            res += my_putstr(ouput, data->argv[index]);
            res += my_putchar(ouput, ' ');
            lens[2] += my_strlen(data->argv[index]) + 1;
        }
        res += my_printf("%O%C%s", ouput, 175 * !warning, 150 * warning, 150 * warning, arg);
        res += color_rgb(ouput, 0, 125, 0);
        for (index += 1; data->argv[index]; index++) {
            res += my_putchar(ouput, ' ');
            res += my_putstr(ouput, data->argv[index]);
        }
        res += reset_ouput(ouput);
        res += my_putchar(ouput, '\n');
        for (long int i = 0; i < 1 + lens[2]; i++)
            res += my_putchar(ouput, ' ');
        for (int i = 0; i < lens[0]; i++)
            res += my_putchar(ouput, '^');
    } else if (should && arg) {
        res += my_putchar(ouput, ' ');
        res += color_rgb(ouput, 0, 125, 0);
        for (index = 0; data->argv[index]; index++) {
            res += my_putstr(ouput, data->argv[index]);
            res += my_putchar(ouput, ' ');
            lens[2] += my_strlen(data->argv[index]) + 1;
            if (data->argv[index] == arg)
                break;
        }
        res += my_printf("%O%C%s", ouput, 175 * !warning, 150 * warning, 150 * warning, should);
        res += color_rgb(ouput, 0, 125, 0);
        for (index += 1; data->argv[index]; index++) {
            res += my_putchar(ouput, ' ');
            res += my_putstr(ouput, data->argv[index]);
        }
        res += reset_ouput(ouput);
        res += my_putchar(ouput, '\n');
        for (long int i = 0; i < 1 + lens[2]; i++)
            res += my_putchar(ouput, ' ');
        for (int i = 0; i < lens[1]; i++)
            res += my_putchar(ouput, '^');
    } else if (!should && !arg) {
        res += strong(ouput);
        res += color_rgb(ouput, 175 * !warning, 150 * warning, 150 * warning);
        for (int i = 0; data->argv[i]; i++) {
            res += my_putchar(ouput, ' ');
            res += my_putstr(ouput, data->argv[i]);
            lens[2] += my_strlen(data->argv[i]) + 1;
        }
        res += reset_ouput(ouput);
        res += my_putchar(ouput, '\n');
        res += my_putchar(ouput, ' ');
        for (int i = 0; i < lens[2] - 1; i++)
            res += my_putchar(ouput, '^');
    }
    res += my_putchar(ouput, '\n');
    res += my_printf("%O%C-------------------------------------------%R\n", ouput, 175, 100, 0);
    if (res != OK)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    return to_return;
}
