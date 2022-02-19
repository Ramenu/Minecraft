#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <cstdint>

extern void loadVertexBuffer(uint32_t& buffer, uint32_t size, const void* data);
extern void loadElementBuffer(uint32_t& buffer, uint32_t size, const void* data);

#endif // BUFFER_HPP