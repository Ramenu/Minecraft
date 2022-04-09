#ifndef RADIANS_HPP
#define RADIANS_HPP

#include <compare>

class Radians
{
    public:
        explicit Radians(float angle) noexcept;
        auto operator<=>(const Radians &r) const = default;
    private:
        float radians;
};

#endif // RADIANS_HPP
