#ifndef GLERROR_HPP
#define GLERROR_HPP

#define MC_DEBUG_BUILD

#include <string_view>

namespace GLError
{
    extern void error_message(std::string_view error) noexcept;
    #ifdef MC_DEBUG_BUILD
        extern void enableGLDebugCallBack();
    #endif
}

#endif // GLERROR_HPP
