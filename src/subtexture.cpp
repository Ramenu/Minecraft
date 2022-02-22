#include "mylib/gfx/subtexture.hpp"
#include "mylib/gfx/texture.hpp"

/* Default constructor for the sub texture. */
SubTexture::SubTexture() {}

/* Constructor for the sub texture. */
SubTexture::SubTexture(float column, float row) :
texCoords {column * Texture::xPos, row * Texture::yPos} {}


