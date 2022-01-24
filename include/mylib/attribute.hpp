#ifndef ATTRIBUTE_HPP
#define ATTRIBUTE_HPP

#include <vector>
#include <cstdint>

extern void setAttributes(const std::vector<intptr_t>& attributeIndices); 
extern void enableVBOAttributes(unsigned int& buffer, const unsigned int& upTo);
extern void disableVBOAttributes(unsigned int& buffer, const unsigned int& upTo);
extern void enableVAOAttributes(const std::vector<unsigned int>& indices);
extern void disableVAOAttributes(const std::vector<unsigned int>& indices);

#endif