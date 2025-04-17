/**************************************************************\

 ██╗  ██╗ █████╗ ██████╗ ████████╗ █████╗ ███╗   ██╗██╗ █████╗ 
 ╚██╗██╔╝██╔══██╗██╔══██╗╚══██╔══╝██╔══██╗████╗  ██║██║██╔══██╗
  ╚███╔╝ ███████║██████╔╝   ██║   ███████║██╔██╗ ██║██║███████║
  ██╔██╗ ██╔══██║██╔══██╗   ██║   ██╔══██║██║╚██╗██║██║██╔══██║
 ██╔╝ ██╗██║  ██║██║  ██║   ██║   ██║  ██║██║ ╚████║██║██║  ██║
 ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝

Edition:
##  15/04/2025 by Tsukini

File Name:
##  directory.c

File Description:
## Handle the directory flag option
\**************************************************************/

#include "my_string.h"  // get_fullpath, my_strcmp function
#include "array.h"      // add_array function
#include "kamion.h"     // compiler_t type
#include "error.h"      // error handling
#include <string.h>     // strerror function
#include <stdio.h>      // dir function
#include <stdlib.h>     // free function
#include <dirent.h>     // dir struct
#include <errno.h>      // errno global var

/* Directory function
----------------------------------------------------------------
 * That will extract the file in the given directory
 * and use them in the compilation
----------------------------------------------------------------
##  data -> main data structure
##  argc -> number of argument given to the binary
##  argv -> arguments given to the binary
----------------------------------------------------------------
*/
int flag_directory(compiler_t *data, int const argc, char const *argv[])
{
    struct dirent *entry = NULL;
    DIR *dir = NULL;
    char *path = NULL;
    char *ptr = NULL;
    size_t before = 0;

    // Check for potential null pointer
    if (!data || !argv)
        return err_prog(PTR_ERR, KO, ERR_INFO);

    // Check argument
    if (argc < 2 || argv[1][0] == '-')
        return err_kmc_arg(data, KO, "Argument", "Insufficient argument, need a 'directory_path'", *argv, "directory_path", false);
    if (!is_valid_dir(data, argv[1], false))
        return err_kmc_arg(data, KO, "Argument", "Invalid directory given", argv[1], NULL, false);

    // Open the directory to read it's content
    dir = opendir(argv[1]);
    if (!dir)
        return err_system(data, KO, argv[1], strerror(errno));

    // Get the file with end in .15 and .15h in the given path
    before = data->files->len;
    while ((entry = readdir(dir))) {
        // Check if the file end with .15 or .15h
        ptr = NULL;
        for (int i = 0; entry->d_name[i]; i++) {
            if (entry->d_name[i] == '.')
                ptr = &entry->d_name[i];
        }
        if (my_strcmp(ptr, ".15") != 0 && my_strcmp(ptr, ".15h") != 0)
            continue;

        // Set the file in the array
        path = get_full_path(argv[1], entry->d_name);
        if (is_valid_file(data, path, false)) {
            if (add_array(data->files, path) == KO)
                return err_prog(UNDEF_ERR, KO, ERR_INFO);
        } else
            free(path);
    }
    if (before == data->files->len)
        err_kmc_arg(data, KO, "Argument", "No file in '.15' or '.15h' find in the given path", argv[1], NULL, true);

    closedir(dir);
    return OK;
}
