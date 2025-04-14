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
##  init_data.c

File Description:
## Call of function to init main structure var
\**************************************************************/

#include "kamion.h" // compiler_t type
#include "error.h"  // error handling

/* Init main structure function
----------------------------------------------------------------
 * Call of the function to initialise all var of the
 * main structure and check the init return
----------------------------------------------------------------
##  data -> main data structure
----------------------------------------------------------------
*/
int init_data(compiler_t *data)
{
    // Check for potential null pointer
    if (!data)
        return err_prog(PTR_ERR, KO, ERR_INFO);
    
    // Init global data used in every sub part
    if (init_global(data) == KO)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    return OK;
}
