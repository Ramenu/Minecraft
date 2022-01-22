#include "mylib/graphics/subtexture.hpp"
#include "mylib/graphics/textures.hpp"

/* Default constructor for the sub texture. */
SubTexture::SubTexture() {}

/* Constructor for the sub texture. */
SubTexture::SubTexture(const float& column, const float& row) :
texCoords {column * xPos, row * yPos} {}

/* Destructor for the sub texture. */
SubTexture::~SubTexture()
{

}
