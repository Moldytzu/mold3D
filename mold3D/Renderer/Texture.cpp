#include <mold3D/3D.h>

using namespace mold::render;

uint32_t texture::UseTexture(texture::Texture texture)
{
    // Create Texture
    glBindTexture(GL_TEXTURE_2D, render::GlobalTextures[LastTextureIndex++]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //scale linearly when image smalled than texture
    glTexImage2D(GL_TEXTURE_2D, 0, 3, texture.Width, texture.Height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture.PixelData);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); //wrapping stretches the texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    return LastTextureIndex - 1; //return the index
}