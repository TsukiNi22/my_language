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
##  is_valid_dir.c

File Description:
## Check if the given path is a valid directory
\**************************************************************/

#include "kamion.h"     // compiler_t type
#include "error.h"      // error handling
#include <string.h>     // strerror function
#include <unistd.h>     // access function
#include <sys/stat.h>   // lstat function
#include <errno.h>      // errno global var
#include <stdbool.h>    // bool type

/* Is a valid directory function
----------------------------------------------------------------
 * Determine if the given path is a valid directory
 * and if it's possible to read it
----------------------------------------------------------------
##  data -> main data structure
##  path -> directory path
----------------------------------------------------------------
*/
bool is_valid_dir(compiler_t *data, char const *path, bool err)
{
    struct stat st = {0};

    // Check for potential null pointer
    if (!data || !path)
        return err_prog(PTR_ERR, false, ERR_INFO);

    // Check if the path exist
    if (access(path, F_OK) != 0)
        return err_system(data, false, path, "The given path does not point to any existing thing");
    // Check if the path can be read
    if (access(path, R_OK) != 0)
        return err_system(data, false, path, "Can't read the given file or directory");

    // Get stat and Check the type of file
    if (lstat(path, &st) != 0)
        return err_system(data, false, path, strerror(errno));
    if (!S_ISDIR(st.st_mode)) {
        if (!err)
            return false;
        return err_system(data, false, path, "The given path is definitly not a directory");
    }
    return true;
}
