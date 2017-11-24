#ifndef TEXTURE_HH
#define TEXTURE_HH

#include <GL/glew.h>

#include <string>


class Texture {

public:
                         Texture();
                         ~Texture();

  bool                   LoadFromFile(const std::string& p_path);

  const GLuint           GetID() const { return m_textureID; }

private:
  GLuint                 m_textureID;
};

#endif  // TEXTURE
