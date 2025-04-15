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
##  const.c

File Description:
## Constant used in flag initialisation and other thing
\**************************************************************/

#include "kamion.h" // compiler_t type

// Flag that are with '-'
char const flags[] = {
    'h',
    'b',
    'E',
    'd',
    'D'
};

// Flag that are with '--'
char const *full_flags[] = {
    "--help",
    "--binary",
    "--Errors",
    "--directory",
    "--Directory"
};

// Used for the number of arg of a flag (-1 for those who can't be conbined)
int const flags_argc[] = {
    -1, // help
    1,  // binary
    0,  // Errors
    1,  // directory
    1   // Directory
};

// Function call at the detection of  a flag
int (* const flag_functions[])(compiler_t *, int const, char const *[]) = {
    &flag_null, // help
    &flag_binary, // binary
    &flag_Errors, // Errors
    &flag_directory, // directory
    &flag_Directory  // Directory
};
