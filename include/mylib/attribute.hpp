#ifndef ATTRIBUTE_HPP
#define ATTRIBUTE_HPP

#include <vector>
#include <cstdint>

extern void setAttributes(std::vector<intptr_t>&& attributeIndices); 
extern void enableVBOAttributes(unsigned int& buffer,  const unsigned int upTo);
extern void disableVBOAttributes(unsigned int& buffer, const unsigned int upTo);
extern void enableVAOAttributes(std::vector<unsigned int>&& indices);
extern void disableVAOAttributes(std::vector<unsigned int>&& indices);

#endif // ATTRIBUTE_HPP