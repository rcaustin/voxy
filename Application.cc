#include "Application.hh"

/////////////////////////////////////////////////////////////////////////////////////////////////////
// External Headers
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////
// Standard Headers
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>

/////////////////////////////////////////////////////////////////////////////////////////////////////
// Engine Headers
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Input.hh"


/////////////////////////////////////////////////////////////////////////////////////////////////////
// Application Implementation
/////////////////////////////////////////////////////////////////////////////////////////////////////

Application::Application()
  : m_window{"Voxy", {1280, 720}} {

  m_shader.LoadFromFile("shaders/Default.vert", "shaders/Default.frag");
  m_shader.AddAttribute("vertexPosition");
  m_shader.AddAttribute("vertexColor");
  m_shader.AddAttribute("vertexCoord");
  m_shader.LinkProgram();
  m_texture.LoadFromFile("textures/Block1.png");
}

void Application::Launch() {

  m_chunk1 = new Chunk{{0, 0, 0}};
  m_chunk2 = new Chunk{{0, 0, 1}};

  while (m_window.IsOpen()) {
    m_timer.BeginFrame();

    while (m_timer.Tick()) {
      HandleInput();
      UpdateState();
      m_timer.Tock();
    }

    RenderFrame();
    m_timer.EndFrame();
  }
}

void Application::HandleInput() {

  if (Keyboard::IsKeyPressed(Keyboard::Key::Escape))
    m_window.Exit();

  if (Keyboard::IsKeyPressed(Keyboard::Key::W))
    m_camera.Move(Direction::Forward, m_timer.GetDeltaTime());
  if (Keyboard::IsKeyPressed(Keyboard::Key::S))
    m_camera.Move(Direction::Backward, m_timer.GetDeltaTime());
  if (Keyboard::IsKeyPressed(Keyboard::Key::A))
    m_camera.Move(Direction::Left, m_timer.GetDeltaTime());
  if (Keyboard::IsKeyPressed(Keyboard::Key::D))
    m_camera.Move(Direction::Right, m_timer.GetDeltaTime());
  if (Keyboard::IsKeyPressed(Keyboard::Key::C))
    m_camera.Move(Direction::Down, m_timer.GetDeltaTime());
  if (Keyboard::IsKeyPressed(Keyboard::Key::Space))
    m_camera.Move(Direction::Up, m_timer.GetDeltaTime());

  m_camera.Turn(Mouse::GetRelativePosition(), m_timer.GetDeltaTime());
}

void Application::UpdateState() {

  m_window.Update();
  m_chunk1->Update();
  m_chunk2->Update();
}

void Application::RenderFrame() {

  m_window.BeginRender();
  m_shader.Enable();

  // Bind Texture
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, m_texture.GetID());

  // Get Uniform Data
  glm::mat4 viewMatrix = m_camera.GetViewMatrix();
  glm::mat4 projMatrix = glm::perspective(m_camera.GetZoom(), m_window.GetAspectRatio(),
                                          Camera::NEAR_PLANE, Camera::FAR_PLANE);

  // Get Uniform Locations
  GLint txtrLocation = m_shader.GetUniformLocation("sampler");
  GLint viewLocation = m_shader.GetUniformLocation("viewMatrix");
  GLint projLocation = m_shader.GetUniformLocation("projectionMatrix");

  // Pass Uniforms to Shader
  glUniform1i(txtrLocation, 0);
  glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
  glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(projMatrix));

  // Perform Rendering
  m_chunk1->Render();
  m_chunk2->Render();

  // Unbind Texture
  glBindTexture(GL_TEXTURE_2D, 0);

  m_shader.Disable();
  m_window.EndRender();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
