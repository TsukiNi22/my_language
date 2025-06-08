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
##  init_regex.c

File Description:
## Initialisation of the regex
\**************************************************************/

#include "kamion.h"     // compiler_t type
#include "error.h"      // error handling
#include <regex.h>      // regex type & function
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
    // Check for potential null pointer
    if (!data)
        return err_prog(PTR_ERR, KO, ERR_INFO);

    // Bool Regex
    if (regcomp(&(data->regex[0]), "^(0|1|true|false)$", REG_EXTENDED | REG_NOSUB) != OK)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    // Bin Regex
    if (regcomp(&(data->regex[1]), "^0b[01]*$", REG_EXTENDED | REG_NOSUB) != OK)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    // Oct Regex
    if (regcomp(&(data->regex[2]), "^0[0-7]*$", REG_EXTENDED | REG_NOSUB) != OK)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    // Hex Regex
    if (regcomp(&(data->regex[3]), "^0x[0-9a-fA-F]*$", REG_EXTENDED | REG_NOSUB) != OK)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    // Int Regex
    if (regcomp(&(data->regex[4]), "^-?[0-9]+$", REG_EXTENDED | REG_NOSUB) != OK)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    // Float Regex
    if (regcomp(&(data->regex[5]), "^-?([0-9]+\\.[0-9]*|\\.[0-9]+)$", REG_EXTENDED | REG_NOSUB) != OK)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    // String Regex
    if (regcomp(&(data->regex[6]), "^\"([^\"\\\\]|\\\\.)*\"$", REG_EXTENDED | REG_NOSUB) != OK)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    // Char Regex
    if (regcomp(&(data->regex[7]), "^'(\\.|[^'\\\\])'$", REG_EXTENDED | REG_NOSUB) != OK)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);
    // Comment Regex
    if (regcomp(&(data->regex[8]), "^@>.*<@$", REG_EXTENDED | REG_NOSUB) != OK)
        return err_prog(UNDEF_ERR, KO, ERR_INFO);

    return OK;
}
