#ifndef ATTRIBUTE_HPP
#define ATTRIBUTE_HPP

extern void setAttributes(const unsigned int& posAttrLocation, const unsigned int& textureAttrLocation); 
extern void enableVBOAttributes(unsigned int& buffer, const unsigned int& upTo);
extern void disableVBOAttributes(unsigned int& buffer, const unsigned int& upTo);
extern void enableVAOAttributes(const unsigned int& upTo);
extern void disableVAOAttributes(const unsigned int& upTo);

#endif