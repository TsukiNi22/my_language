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
#include "kamion.h"     // compiler_t type
#include "error.h"      // error handling
#include <stddef.h>     // size_t type
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

    data->nb_warning += warning;
    data->nb_error += !warning;

    // Write the error/warning message
    if (data->nb_warning + data->nb_error > 1)
        res += my_putchar(ouput, '\n');
    if (!warning) {
        res += my_printf("%OError n°%d during the check of the file '%S%s:%u:%u%R'.\n", ouput, data->nb_error, file, n, start);
        res += my_printf("%O%C%s:%R %C%s.%R\n", ouput, 205, 0, 0, type, 150, 0, 150, err);
    } else {
        res += my_printf("%OWarging n°%d in the file '%S%s:%u:%u%R': %C%s%R\n", ouput, data->nb_warning, file, n, start, 150, 0, 150, err);
    }
    res += my_printf("%O%C-------------------------------------------%R\n", ouput, 175, 100, 0);
    res += my_printf("%O%C%d | %C%.*s%C%.*s%R%C%s%R\n", ouput,
    175, 100, 0, n,
    0, 125, 0, start - 1, line,
    205 - 55 * warning, 0, 150 * warning, end - (start - 1), &line[start - 1],
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
