#include "Shader.hh"

#include <vector>
#include <fstream>
#include <stdexcept>


Shader::Shader()
  : m_programID{0},
    m_vertexShaderID{0},
    m_fragmentShaderID{0},
    m_attributeCount{0} {

}

void Shader::LoadFromFile(const std::string& p_vertexSource, const std::string& p_fragmentSource) {

  m_programID = glCreateProgram();

  m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
  if (m_vertexShaderID == 0)
    throw std::runtime_error("Shader::LoadFromFile--Failed to Create Vertex Shader");
  CompileShader(p_vertexSource, m_vertexShaderID);

  m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
  if (m_fragmentShaderID == 0)
    throw std::runtime_error("Shader::LoadFromFile--Failed to Create Fragment Shader");
  CompileShader(p_fragmentSource, m_fragmentShaderID);
}

void Shader::LinkProgram() {

  glAttachShader(m_programID, m_vertexShaderID);
  glAttachShader(m_programID, m_fragmentShaderID);
  glLinkProgram(m_programID);

  // Error Checking
  GLint success = GL_FALSE;
  glGetProgramiv(m_programID, GL_LINK_STATUS, (int*)&success);
  if (success == GL_FALSE) {
    GLint maxLength = 0;
    glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &maxLength);
    std::vector<char> errorLog(maxLength);
    glGetProgramInfoLog(m_programID, maxLength, &maxLength, &errorLog[0]);
    glDeleteProgram(m_programID);
    glDeleteShader(m_vertexShaderID);
    glDeleteShader(m_fragmentShaderID);

    std::printf("%s\n", &errorLog[0]);
    throw std::runtime_error("Shader::LinkProgram--Failed to Link Shader Program");
  }

  glDetachShader(m_programID, m_vertexShaderID);
  glDetachShader(m_programID, m_fragmentShaderID);
}

void Shader::AddAttribute(const std::string& p_attributeName) {

  glBindAttribLocation(m_programID, m_attributeCount++, p_attributeName.c_str());
}

void Shader::Enable() {

  glUseProgram(m_programID);
  for (size_t i = 0; i < m_attributeCount; ++i)
    glEnableVertexAttribArray(i);
}

void Shader::Disable() {

  glUseProgram(0);
  for (size_t i = 0; i < m_attributeCount; ++i)
    glDisableVertexAttribArray(i);
}

const GLint Shader::GetUniformLocation(const std::string& p_uniformName) const {

  GLint location = glGetUniformLocation(m_programID, p_uniformName.c_str());
  if (location == GL_INVALID_INDEX)
    throw std::runtime_error("Shader::GetUniformLocation--Failed to Find Uniform in Shader");
  return location;
}

void Shader::CompileShader(const std::string& p_path, const GLuint p_shaderID) const {

  std::ifstream sourceFile(p_path);
  if (sourceFile.fail())
    throw std::runtime_error("Shader::CompileShader--Failed to Open File: " + p_path);

  std::string contents, line;
  while (std::getline(sourceFile, line))
    contents += line + '\n';
  sourceFile.close();
  const char* contentsPtr = contents.c_str();

  glShaderSource(p_shaderID, 1, &contentsPtr, nullptr);
  glCompileShader(p_shaderID);

  // Error Checking
  GLint success = GL_FALSE;
  glGetShaderiv(p_shaderID, GL_COMPILE_STATUS, &success);
  if (success == GL_FALSE) {
    GLint maxLength = 0;
    glGetShaderiv(p_shaderID, GL_INFO_LOG_LENGTH, &maxLength);
    std::vector<char> errorLog(maxLength);
    glGetShaderInfoLog(p_shaderID, maxLength, &maxLength, &errorLog[0]);
    glDeleteShader(p_shaderID);

    std::printf("%s\n", &errorLog[0]);
    throw std::runtime_error("Shader::CompileShader--Failed to Compile Shader: " + p_path);
  }
}
