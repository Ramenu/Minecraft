#ifndef GLERROR_HPP
#define GLERROR_HPP

#include <string_view>

namespace GLError
{
    extern void error_message(std::string_view error) noexcept;
}

#endif // GLERROR_HPP
