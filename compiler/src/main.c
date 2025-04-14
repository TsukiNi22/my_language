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
##  main.c

File Description:
##  You know, I don t think there are good or bad descriptions,
##  for me, life is all about functions...
\**************************************************************/

#include "kamion.h"
#include "write.h"
#include "error.h"
#include <stdbool.h>

int main(int const argc, char const *argv[])
{
    compiler_t data = {0};
    int res = 0;

    if (!argv)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    data.exe_name = argv[0];
    data.help = false;
    data.err_sys = false;
    res = kamion(argc, argv, &data);
    if (res == KO || res == FATAL_ERR) {
        if (res != FATAL_ERR)
            free_data(&data);
        if (!data.err_sys)
            my_printf("%O%s: An error has occurred, execution has been interrupted.\n", STDERR, data.exe_name);
        return KO;
    }
    return free_data(&data);
}
