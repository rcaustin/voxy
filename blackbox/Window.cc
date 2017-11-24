#include "Window.hh"

/////////////////////////////////////////////////////////////////////////////////////////////////////
// Standard Headers
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdexcept>


/////////////////////////////////////////////////////////////////////////////////////////////////////
// Window Implementation
/////////////////////////////////////////////////////////////////////////////////////////////////////

Window::Window(const std::string& p_title, const glm::uvec2& p_size)
  : m_window{nullptr},
    m_context{nullptr},
    m_title{p_title},
    m_size{p_size},
    m_isFullscreen{false},
    m_isOpen{true} {

  SDL_Init(SDL_INIT_EVERYTHING);
  Create();
}

Window::~Window() {

  Destroy();
}

void Window::BeginRender() const {

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::EndRender() const {

  SDL_GL_SwapWindow(m_window);
}

void Window::Update() {

  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      m_isOpen = false;
      break;
    default:
      break;
    }
  }
}

void Window::ToggleFullscreen() {

  m_isFullscreen = !m_isFullscreen;
  Destroy();
  Create();
}

void Window::Create() {

  if (m_window == nullptr) {

    Uint32 windowSettings = SDL_WINDOW_OPENGL;
    if (m_isFullscreen)
      windowSettings |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    else
      windowSettings |= SDL_WINDOW_RESIZABLE;

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    m_window = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                m_size.x, m_size.y, windowSettings);
    if (m_window == nullptr)
      throw std::runtime_error("Window::Create--Failed to Initialize SDL Window");

    m_context = SDL_GL_CreateContext(m_window);
    if (m_context == nullptr)
      throw std::runtime_error("Window::Create--Failed to Initialize OpenGL Context");

    if (glewInit() != GLEW_OK)
      throw std::runtime_error("Window::Create--Failed to Initialize GLEW");

    SDL_GL_SetSwapInterval(1);

    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);
  } else
    throw std::runtime_error("Window::Create--Window.Create() Called with an Existing Window");
}

void Window::Destroy() {

  if (m_window != nullptr) {
    SDL_GL_DeleteContext(m_context);
    m_context = nullptr;
    SDL_DestroyWindow(m_window);
    m_window = nullptr;
    m_isOpen = false;
  } else
    throw std::runtime_error("Window::Destroy--Window.Destroy() Called with No Existing Window");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
