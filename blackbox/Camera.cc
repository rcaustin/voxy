#include "Camera.hh"


/////////////////////////////////////////////////////////////////////////////////////////////////////
// Camera Implementation
/////////////////////////////////////////////////////////////////////////////////////////////////////

Camera::Camera(const glm::vec3& p_position, const glm::vec3& p_upVector, float p_yaw, float p_pitch)
  : m_position{p_position},
    m_frontVector{glm::vec3{0.0f, 0.0f, -1.0f}},
    m_worldUpVector{p_upVector},
    m_yaw{p_yaw},
    m_pitch{p_pitch},
    m_speed{sm_DEFAULT_SPEED},
    m_sensitivity{sm_DEFAULT_SENSITIVITY},
    m_zoom{sm_DEFAULT_ZOOM} {

  UpdateVectors();
}

const glm::mat4 Camera::GetViewMatrix() const {

  return glm::lookAt(m_position, m_position + m_frontVector, m_upVector);
}

void Camera::Move(Direction p_direction, float p_deltaTime) {

  // Local X-Axis Movement
  if (p_direction == Direction::Left)
    m_position -= m_rightVector * m_speed * p_deltaTime;
  if (p_direction == Direction::Right)
    m_position += m_rightVector * m_speed * p_deltaTime;

  // Local Y-Axis Movement
  if (p_direction == Direction::Down)
    m_position -= m_upVector * m_speed * p_deltaTime;
  if (p_direction == Direction::Up)
    m_position += m_upVector * m_speed * p_deltaTime;

  // Local Z-Axis Movement
  if (p_direction == Direction::Backward)
    m_position -= m_frontVector * m_speed * p_deltaTime;
  if (p_direction == Direction::Forward)
    m_position += m_frontVector * m_speed * p_deltaTime;
}

void Camera::Turn(const glm::ivec2& p_xyOffset, float p_deltaTime) {

  m_yaw   += p_xyOffset.x * m_sensitivity * p_deltaTime;
  m_pitch -= p_xyOffset.y * m_sensitivity * p_deltaTime; // += for INVERTED-Y

  if (m_pitch < sm_MINIMUM_PITCH)
    m_pitch = sm_MINIMUM_PITCH;
  if (m_pitch > sm_MAXIMUM_PITCH)
    m_pitch = sm_MAXIMUM_PITCH;

  UpdateVectors();
}

void Camera::Zoom(float p_yOffset, float p_deltaTime) {

  m_zoom -= p_yOffset * p_deltaTime;

  if (m_zoom < sm_MINIMUM_ZOOM)
    m_zoom = sm_MINIMUM_ZOOM;
  if (m_zoom > sm_MAXIMUM_ZOOM)
    m_zoom = sm_MAXIMUM_ZOOM;
}

void Camera::UpdateVectors() {

  float yaw   = glm::radians(m_yaw);
  float pitch = glm::radians(m_pitch);
  glm::vec3 frontVector{cos(yaw) * cos(pitch), sin(pitch), sin(yaw) * cos(pitch)};

  m_frontVector = glm::normalize(frontVector);
  m_rightVector = glm::normalize(glm::cross(m_frontVector, m_worldUpVector));
  m_upVector    = glm::normalize(glm::cross(m_rightVector, m_frontVector));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
