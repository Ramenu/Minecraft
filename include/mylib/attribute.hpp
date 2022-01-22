#ifndef ATTRIBUTE_HPP
#define ATTRIBUTE_HPP

extern void setAttributes(const unsigned int& posAttrLocation, const unsigned int& textureAttrLocation); 
extern void enableAttributes(unsigned int& buffer, const unsigned int& upTo);
extern void disableAttributes(unsigned int& buffer, const unsigned int& upTo);

#endif