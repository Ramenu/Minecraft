#ifndef RADIANS_HPP
#define RADIANS_HPP

class Radians
{
    public:
        explicit Radians(float angle) noexcept;
        bool operator>(Radians r) const noexcept {return radians > r.radians;}
        bool operator<(Radians r) const noexcept {return radians < r.radians;}
        bool operator>=(Radians r) const noexcept {return radians >= r.radians;}
        bool operator<=(Radians r) const noexcept {return radians <= r.radians;}
        bool operator==(Radians r) const noexcept {return radians == r.radians;}
        bool operator!=(Radians r) const noexcept {return radians == r.radians;}
    private:
        float radians;
};

#endif // RADIANS_HPP
