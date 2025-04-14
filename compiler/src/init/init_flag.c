/**************************************************************\

 ██╗  ██╗ █████╗ ██████╗ ████████╗ █████╗ ███╗   ██╗██╗ █████╗ 
 ╚██╗██╔╝██╔══██╗██╔══██╗╚══██╔══╝██╔══██╗████╗  ██║██║██╔══██╗
  ╚███╔╝ ███████║██████╔╝   ██║   ███████║██╔██╗ ██║██║███████║
  ██╔██╗ ██╔══██║██╔══██╗   ██║   ██╔══██║██║╚██╗██║██║██╔══██║
 ██╔╝ ██╗██║  ██║██║  ██║   ██║   ██║  ██║██║ ╚████║██║██║  ██║
 ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝

Edition:
##  14/04/2025 by Tsukini

File Name:
##  init_flag.c

File Description:
##  You know, I don t think there are good or bad descriptions,
##  for me, life is all about functions...
\**************************************************************/

#include "memory.h"
#include "my_string.h"
#include "write.h"
#include "kamion.h"
#include "error.h"
#include <stdbool.h>

static int full_flag(compiler_t *data,
    int const argc, char const *argv[], int const i)
{
    if (!data || !argv)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    for (int j = 0; full_flags[j]; j++) {
        if (my_strcmp(argv[i], full_flags[j]) == 0)
            return flag_functions[j](data, argc - i, &(argv[i]));
    }
    return err_system(data, KO, argv[i], "Unrecognized option");
}

static int is_flag_char(char const c, int *index)
{
    if (!index)
        return err_prog(PTR_ERR, false, ERR_INFO);
    for (int i = 0; flags[i]; i++) {
        if (c == flags[i]) {
            *index = i;
            return true;
        }
    }
    return false;
}

static int flag(compiler_t *data,
    int const argc, char const *argv[], int const i)
{
    int index = 0;

    if (!data || !argv)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    for (int j = 1; argv[i][j]; j++) {
        if (!is_flag_char(argv[i][j], &index))
            return err_system(data, KO,
            my_strndup(&argv[i][j], 1), "Invalid option");
        if (flags_argc[index] != 0 && (j > 1 || argv[i][j + 1]))
            return err_system(data, KO,
            my_strndup(&argv[i][j], 1), "Can't be combined with other");
        if (flag_functions[index](data, argc - i, &(argv[i])) == KO)
            return err_prog(UNDEF_ERR, KO, ERR_INFO);
    }
    return OK;
}

int init_flag(compiler_t *data, int const argc, char const *argv[])
{
    if (!data || !argv)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    for (int i = 0; i < argc; i++) {
        if ((argv[i][0] == '-' && argv[i][1] == flags[0] && !argv[i][2])
            || my_strcmp(argv[i], full_flags[0]) == 0) {
            data->help = true;
            return flag_help();
        }
    }
    for (int i = 0; i < argc; i++) {
        if (argv[i][0] != '-')
            continue;
        if (argv[i][1] == '-' && argv[i][2]
            && full_flag(data, argc, argv, i) == KO)
            return err_prog(UNDEF_ERR, KO, ERR_INFO);
        if (argv[i][1] != '-' && argv[i][1]
            && flag(data, argc, argv, i) == KO)
            return err_prog(UNDEF_ERR, KO, ERR_INFO);
    }
    return OK;
}
