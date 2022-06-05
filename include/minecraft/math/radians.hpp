#ifndef MC_RADIANS_HPP
#define MC_RADIANS_HPP

#include <compare>
#include "misc/boilerplate/glm_noerr.hpp"

class Radians
{
    private:
        float radians;
    public:
        inline explicit constexpr Radians(float angleInDegrees) noexcept : radians {glm::radians(angleInDegrees)} {}
        inline constexpr float value() const noexcept {return radians;}
        inline constexpr void set(float angleInDegrees) noexcept {radians = glm::radians(angleInDegrees);}
        auto operator<=>(const Radians &r) const = default;
};

#endif // MC_RADIANS_HPP
