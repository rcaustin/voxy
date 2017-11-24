#ifndef CAMERA_HH
#define CAMERA_HH

/////////////////////////////////////////////////////////////////////////////////////////////////////
// External Headers
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


/////////////////////////////////////////////////////////////////////////////////////////////////////
// Camera Interface
/////////////////////////////////////////////////////////////////////////////////////////////////////

enum class Direction { Left, Right, Down, Up, Backward, Forward };

class Camera {

public:
                         Camera(const glm::vec3& p_position = glm::vec3{0.0f, 0.0f, 0.0f},
                                const glm::vec3& p_upVector = glm::vec3{0.0f, 1.0f, 0.0f},
                                float p_yaw                 = sm_DEFAULT_YAW,
                                float p_pitch               = sm_DEFAULT_PITCH);

  void                   Move(Direction p_direction, float p_deltaTime);
  void                   Turn(const glm::ivec2& p_xyOffset, float p_deltaTime);
  void                   Zoom(float p_yOffset, float p_deltaTime);

  const glm::mat4        GetViewMatrix() const;
  const glm::vec3        GetPosition() const { return m_position; }
  const float            GetZoom() const { return glm::radians(m_zoom); }

  void                   SetPosition(const glm::vec3& p_position) { m_position = p_position; }
  void                   SetSpeed(float p_speed) { m_speed = p_speed; }
  void                   SetSensitivity(float p_sensitivity) { m_sensitivity = p_sensitivity; }
  void                   SetZoom(float p_zoom) { m_zoom = p_zoom; }

  static constexpr float NEAR_PLANE{0.1f};
  static constexpr float FAR_PLANE{10000.0f};

private:
  glm::vec3              m_position;
  glm::vec3              m_frontVector;
  glm::vec3              m_upVector;
  glm::vec3              m_rightVector;
  glm::vec3              m_worldUpVector;

  float                  m_yaw;
  float                  m_pitch;

  float                  m_speed;
  float                  m_sensitivity;
  float                  m_zoom;

  static constexpr float sm_DEFAULT_YAW{-90.0f};
  static constexpr float sm_DEFAULT_PITCH{0.0f};
  static constexpr float sm_DEFAULT_SPEED{0.0005f};
  static constexpr float sm_DEFAULT_SENSITIVITY{0.02f};
  static constexpr float sm_DEFAULT_ZOOM{45.0f};
  static constexpr float sm_MINIMUM_PITCH{-89.0f};
  static constexpr float sm_MAXIMUM_PITCH{89.0f};
  static constexpr float sm_MINIMUM_ZOOM{1.0f};
  static constexpr float sm_MAXIMUM_ZOOM{45.0f};

  void                   UpdateVectors();
};

/////////////////////////////////////////////////////////////////////////////////////////////////////

#endif  // CAMERA
