/**************************************************************\

 ██╗  ██╗ █████╗ ██████╗ ████████╗ █████╗ ███╗   ██╗██╗ █████╗ 
 ╚██╗██╔╝██╔══██╗██╔══██╗╚══██╔══╝██╔══██╗████╗  ██║██║██╔══██╗
  ╚███╔╝ ███████║██████╔╝   ██║   ███████║██╔██╗ ██║██║███████║
  ██╔██╗ ██╔══██║██╔══██╗   ██║   ██╔══██║██║╚██╗██║██║██╔══██║
 ██╔╝ ██╗██║  ██║██║  ██║   ██║   ██║  ██║██║ ╚████║██║██║  ██║
 ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝

Edition:
##  14/06/2025 by Tsukini

File Name:
##  init_regex.c

File Description:
## Initialisation of the regex
\**************************************************************/

#include "kamion.h"     // compiler_t type
#include "error.h"      // error handling
#include <pcre.h>       // regex function
#include <stddef.h>     // NULL define

/* Regex initialisation function
----------------------------------------------------------------
 * Initialisation of the regex to optimize the execution
----------------------------------------------------------------
##  data -> main data structure
----------------------------------------------------------------
*/
int init_regex(compiler_t *data)
{
    const char *error = NULL;
    int erroffset = 0;

    // Check for potential null pointer
    if (!data)
        return err_prog(PTR_ERR, KO, ERR_INFO);

    for (int i = 0; i < REGEX_NUMBER; i++) {
        data->regex[i] = pcre_compile(patterns[i], 0, &error, &erroffset, NULL);
        if (!data->regex[i])
            return err_custom(error, KO, ERR_INFO);

        // Only for optimisation
        data->study[i] = pcre_study(data->regex[i], 0, &error);
    }

    return OK;
}
