#include "mylib/gfx/subtexture.hpp"
#include "mylib/gfx/texture.hpp"

/* Default constructor for the sub texture. */
SubTexture::SubTexture() {}

/* Constructor for the sub texture. */
SubTexture::SubTexture(const float column, const float row) :
texCoords {column * xPos, row * yPos} {}

/* Destructor for the sub texture. */
SubTexture::~SubTexture()
{

}
