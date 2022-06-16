#ifndef MC_VOLUME_HPP
#define MC_VOLUME_HPP

#include <concepts>

template<typename T>
requires std::is_arithmetic_v<T>
struct Volume
{
    T width;
    T height;
    T length;
};

#endif // MC_VOLUME_HPP