/**************************************************************\

 ██╗  ██╗ █████╗ ██████╗ ████████╗ █████╗ ███╗   ██╗██╗ █████╗ 
 ╚██╗██╔╝██╔══██╗██╔══██╗╚══██╔══╝██╔══██╗████╗  ██║██║██╔══██╗
  ╚███╔╝ ███████║██████╔╝   ██║   ███████║██╔██╗ ██║██║███████║
  ██╔██╗ ██╔══██║██╔══██╗   ██║   ██╔══██║██║╚██╗██║██║██╔══██║
 ██╔╝ ██╗██║  ██║██║  ██║   ██║   ██║  ██║██║ ╚████║██║██║  ██║
 ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝

Edition:
##  08/06/2025 by Tsukini

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
    float percent = .0;
    size_t size = 0;
    int res = OK;

    // Check for potential null pointer
    if (!data)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    
    // Empty file case
    if (data->total_adv == 0)
        return OK;

    // Setup percent already done
    percent = (float) data->actual_adv / (float) data->total_adv;
    size = percent * ADV_SIZE;

    // Green part
    res += my_putchar(STDOUT, '[');
    res += color_rgb(STDOUT, 0, 255, 0);
    for (size_t i = 0; i < size; i++)
        res += my_putchar(STDOUT, '/');

    // Red part
    res += color_rgb(STDOUT, 255, 0, 0);
    for (size_t i = size; i < ADV_SIZE; i++)
        res += my_putchar(STDOUT, '-');

    // Text part
    res += reset_ouput(STDOUT);
    printf("] %zu/%zu (%.2f%%)\r", data->actual_adv, data->total_adv, percent * 100);
    fflush(stdout);
    
    if (res != OK)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    return OK;
}
