#include "Texture.hh"

#include <SOIL2.h>


Texture::Texture()
  : m_textureID{0} {

}

Texture::~Texture() {

  if (m_textureID != 0)
    glDeleteTextures(1, &m_textureID);
}

bool Texture::LoadFromFile(const std::string& p_path) {

  m_textureID = SOIL_load_OGL_texture(p_path.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
                                      SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);

  return m_textureID != 0;
}
