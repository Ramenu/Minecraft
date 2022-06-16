#ifndef MC_AREA_HPP
#define MC_AREA_HPP

#include <concepts>

template<typename T> 
requires std::is_arithmetic_v<T>
struct Area
{
    T width;
    T height;
};


#endif // MC_AREA_HPP