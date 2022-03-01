#ifndef ATTRIBUTE_HPP
#define ATTRIBUTE_HPP

#include <vector>

extern void setAttributes(const std::vector<intptr_t> &attributeIndices); 
extern void enableVBOAttributes(const uint32_t &buffer, uint32_t upTo);
extern void disableVBOAttributes(const uint32_t &buffer, uint32_t upTo);
extern void enableVAOAttributes(const std::vector<uint32_t> &indices);
extern void disableVAOAttributes(const std::vector<uint32_t> &indices);

#endif // ATTRIBUTE_HPP