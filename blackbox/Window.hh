#ifndef WINDOW_HH
#define WINDOW_HH

/////////////////////////////////////////////////////////////////////////////////////////////////////
// External Headers
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////
// Standard Headers
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>


/////////////////////////////////////////////////////////////////////////////////////////////////////
// Window Interface
/////////////////////////////////////////////////////////////////////////////////////////////////////

class Window {

public:
                         Window(const std::string& p_title, const glm::uvec2& p_size);
                         ~Window();

  void                   BeginRender() const;
  void                   EndRender() const;

  void                   Update();
  void                   ToggleFullscreen();
  void                   Exit() { m_isOpen = false; }

  const bool             IsOpen() const { return m_isOpen; }
  const bool             IsFullscreen() const { return m_isFullscreen; }

  const glm::uvec2       GetSize() const { return m_size; }
  const float            GetAspectRatio() const { return (float)m_size.x / (float)m_size.y; }

private:
  SDL_Window*            m_window;
  SDL_GLContext          m_context;
  std::string            m_title;
  glm::uvec2             m_size;
  bool                   m_isFullscreen;
  bool                   m_isOpen;

  void                   Create();
  void                   Destroy();
};

/////////////////////////////////////////////////////////////////////////////////////////////////////

#endif  // WINDOW
