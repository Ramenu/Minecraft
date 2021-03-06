#ifndef MC_GLERROR_HPP
#define MC_GLERROR_HPP

#include <string_view>

namespace GLError
{
    extern void error_message(std::string_view error) noexcept;
    #ifndef NDEBUG
        extern void enableGLDebugCallBack();
    #endif
}

#endif // MC_GLERROR_HPP
