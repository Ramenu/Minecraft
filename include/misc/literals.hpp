#ifndef LITERALS_HPP
#define LITERALS_HPP

#include <cstdint>

inline constexpr std::int8_t operator"" _i8(unsigned long long n) {return static_cast<std::int8_t>(n);}
inline constexpr std::uint8_t operator"" _u8(unsigned long long n) {return static_cast<std::uint8_t>(n);}
inline constexpr std::int16_t operator"" _i16(unsigned long long n) {return static_cast<std::int16_t>(n);}
inline constexpr std::uint16_t operator"" _u16(unsigned long long n) {return static_cast<std::uint16_t>(n);}
inline constexpr std::int32_t operator"" _i32(unsigned long long n) {return static_cast<std::int32_t>(n);}
inline constexpr std::uint32_t operator"" _u32(unsigned long long n) {return static_cast<std::uint32_t>(n);}
inline constexpr std::int64_t operator "" _i64(unsigned long long n) {return static_cast<std::int64_t>(n);}
inline constexpr std::uint64_t operator"" _u64(unsigned long long n) {return n;}

#endif // LITERALS_HPP
