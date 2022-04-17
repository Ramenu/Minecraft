#ifndef LITERALS_HPP
#define LITERALS_HPP

#include <cstdint>

inline constexpr int8_t operator"" _i8(size_t n) {return static_cast<int8_t>(n);}
inline constexpr uint8_t operator"" _u8(size_t n) {return static_cast<uint8_t>(n);}
inline constexpr int16_t operator"" _i16(size_t n) {return static_cast<int16_t>(n);}
inline constexpr uint16_t operator"" _u16(size_t n) {return static_cast<uint16_t>(n);}
inline constexpr int32_t operator"" _i32(size_t n) {return static_cast<int32_t>(n);}
inline constexpr uint32_t operator"" _u32(size_t n) {return static_cast<uint32_t>(n);}
inline constexpr int64_t operator "" _i64(size_t n) {return static_cast<int64_t>(n);}
inline constexpr uint64_t operator"" _u64(uint64_t n) {return n;}

#endif // LITERALS_HPP
