#include "mylib/glerror.hpp"
#include <iostream>
extern "C" 
{
    #include "public/terminal.h"
}

namespace GLError
{
    void error_message(std::string_view error) 
    {
        enableTerminalColor(BRIGHTRED);
        std::cerr << "\nFATAL ERROR: ";
        enableTerminalColor(WHITE);
        std::cerr << error << '\n';
        exit(-1);
    }
} 