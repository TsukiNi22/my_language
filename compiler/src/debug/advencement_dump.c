/**************************************************************\

 ██╗  ██╗ █████╗ ██████╗ ████████╗ █████╗ ███╗   ██╗██╗ █████╗ 
 ╚██╗██╔╝██╔══██╗██╔══██╗╚══██╔══╝██╔══██╗████╗  ██║██║██╔══██╗
  ╚███╔╝ ███████║██████╔╝   ██║   ███████║██╔██╗ ██║██║███████║
  ██╔██╗ ██╔══██║██╔══██╗   ██║   ██╔══██║██║╚██╗██║██║██╔══██║
 ██╔╝ ██╗██║  ██║██║  ██║   ██║   ██║  ██║██║ ╚████║██║██║  ██║
 ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝

Edition:
##  01/06/2025 by Tsukini

File Name:
##  advencement_dump.c

File Description:
##  display global advencement
\**************************************************************/

#include "write.h"      // writing function
#include "kamion.h"     // compiler_t type
#include "error.h"      // error handling
#include <stdio.h>      // file functions
#include <unistd.h>     // file octet handler functions
#include <stddef.h>     // size_t type

/* Setup the advencement
----------------------------------------------------------------
 * A function to get the total size of all file to compile
----------------------------------------------------------------
##  data -> main data structure
----------------------------------------------------------------
*/
int setup_files_advencement(compiler_t *data)
{
    FILE *fs = NULL;
    size_t size = 0;

    // Check for potential null pointer
    if (!data)
        return err_prog(PTR_ERR, KO, ERR_INFO);

    // for each file get the total size (in octet)
    for (size_t i = 0; i < data->files->len; i++) {
        // Set the stream for the file to tokenize
        fs = fopen(data->files->data[i], "r");
        if (!fs)
            return err_prog(UNDEF_ERR, KO, ERR_INFO);

        // Get the size
        fseek(fs, 0, SEEK_END);
        size = ftell(fs);

        data->total_adv += size;       
        fclose(fs);
    }
    return OK;
}

/* Advencement Dump for debug
----------------------------------------------------------------
 * A debuging function to display the global advencement
----------------------------------------------------------------
##  data -> main data structure
----------------------------------------------------------------
*/
int advencement_dump(compiler_t *data)
{
    int res = OK;

    // Check for potential null pointer
    if (!data)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    
    res += my_printf("%u/%u\r", data->actual_adv, data->total_adv);
    if (res != OK)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    return OK;
}
