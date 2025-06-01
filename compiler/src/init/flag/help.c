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
##  help.c

File Description:
## Display help
\**************************************************************/

#include "write.h"      // my_printf function
#include "file.h"       // get_file function
#include "my_string.h"  // get_fullpath function
#include "error.h"      // error handling

/* Help function
----------------------------------------------------------------
 * A function used to display the help
 * Call when the flag '-h' or '--help' is used
----------------------------------------------------------------
*/
int flag_help(void)
{
    // Display help
    return my_printf(
    "[36mPROJECT\n"
    "\tThis project is a compiler for the language [35m\'c15\'[36m\n"
    "\tThe name of the compiler is [35m\'kamion\'[36m or [35m\'kmc\'\n\n"
    "[32mINFORMATION\n"
    "\t-Multiple flag will overwrite the first!!!\n"
    "\t-At least one file must be given\n\n"
    "[35mUSAGE\n"
    "\tkmc files_path... [-%c%c%c] [-%c binary_name] [-%c directory_path] [-%c directory_path]\n"
    "\tkmc [-%c%c%c] [-%c binary_name] [-%c directory_path] [-%c directory_path]\n"
    "\tkmc -%c\n\n"
    "[0mOPTIONS\n"
    "\t[32m-%c, %s [0m\n"
    "\t\tWrite the informations of the executable\n"
    "\t[32m-%c, %s [31mbinary_name[0m\n"
    "\t\tChange the name of the output executable to the given [31mbinary_name[0m (default: \'[31m%s[0m\')\n"
    "\t[32m-%c, %s [0m\n"
    "\t\tDisplay all the tokens for each file at the end (default: \'[31mFalse[0m\')\n"
    "\t[32m-%c, %s [0m\n"
    "\t\tDisplay the global advencement for each part of the compiler (default: \'[31mFalse[0m\')\n"
    "\t[32m-%c, %s [0m([31mNot Working[0m)\n"
    "\t\tDisplay all the errors at the end and dosen't stop when encounter one error (default: \'[31mFalse[0m\')\n"
    "\t[32m-%c, %s [31mdirectory_path[0m\n"
    "\t\tAdd the files found without recursive in the given [31mdirectory_path[0m in the list of file to compile\n"
    "\t[32m-%c, %s [31mdirectory_path[0m\n"
    "\t\tAdd the files found recursively in the given [31mdirectory_path[0m in the list of file to compile\n"
    // USAGE
    , flags[5], flags[6], flags[2], flags[1], flags[3], flags[4] // taE b d D
    , flags[5], flags[6], flags[2], flags[1], flags[3], flags[4] // taE b d D
    , flags[0] // h
    // OPTIONS
    , flags[0], full_flags[0] // h help
    , flags[1], full_flags[1] // b binary
    , BINARY_NAME
    , flags[5], full_flags[5] // t tokens
    , flags[6], full_flags[6] // a advencement
    , flags[2], full_flags[2] // E Errors
    , flags[3], full_flags[3] // d directory
    , flags[4], full_flags[4] // D DIRECTORY
    );
}
