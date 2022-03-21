#include "minecraft/glerror.hpp"
#include <iostream>
extern "C" 
{
    #include "color.h"
}

namespace GLError
{
    /**
     * Prints an error message to stderr before
     * terminating the program. This function
     * should only be called if the program 
     * cannot recover from the error in any way.
     */
    void error_message(std::string_view error) noexcept
    {
        std::cerr << COLOR_RED << "\nFATAL ERROR: " << COLOR_RESET << error << '\n';
        exit(EXIT_FAILURE);
    }
} 