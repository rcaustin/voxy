#ifndef VOXELMESH_HH
#define VOXELMESH_HH

/////////////////////////////////////////////////////////////////////////////////////////////////////
// External Headers
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include <GL/glew.h>
#include <glm/glm.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////
// Standard Headers
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

/////////////////////////////////////////////////////////////////////////////////////////////////////
// Vertex Components
/////////////////////////////////////////////////////////////////////////////////////////////////////

struct VertexPosition {

  VertexPosition()
    :X{0.0f}, Y{0.0f}, Z{0.0f} {}
  VertexPosition(GLfloat p_x, GLfloat p_y, GLfloat p_z)
    : X{p_x}, Y{p_y}, Z{p_z} {}

  GLfloat X, Y, Z;
};

struct VertexColor {

  VertexColor()
    : R{255}, G{255}, B{255}, A{255} {}
  VertexColor(GLubyte p_r, GLubyte p_g, GLubyte p_b, GLubyte p_a)
    : R{p_r}, G{p_g}, B{p_b}, A{p_a} {}

  GLubyte R, G, B, A;
};

struct VertexTxtrCoord {

  VertexTxtrCoord()
    : U{0.0f}, V{0.0f} {}
  VertexTxtrCoord(GLfloat p_u, GLfloat p_v)
    : U{p_u}, V{p_v} {}

  GLfloat U, V;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////
// Vertex Data Structure
/////////////////////////////////////////////////////////////////////////////////////////////////////

struct Vertex {

  Vertex() {}
  Vertex(VertexPosition p_vp, VertexTxtrCoord p_vtc)
    : Position{p_vp}, Color{}, TxtrCoord{p_vtc} {}
  Vertex(VertexPosition p_vp, VertexColor p_vc, VertexTxtrCoord p_vtc)
    : Position{p_vp}, Color{p_vc}, TxtrCoord{p_vtc} {}

  VertexPosition  Position;
  VertexColor     Color;
  VertexTxtrCoord TxtrCoord;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////
// VoxelMesh Interface
/////////////////////////////////////////////////////////////////////////////////////////////////////

class VoxelMesh {

public:
                         VoxelMesh();

  void                   AddCube(const glm::vec3& p_origin, float p_width);
  void                   AddFace(const VertexPosition& p_v1, const VertexPosition& p_v2,
                                 const VertexPosition& v_p3, const VertexPosition& p_v4);
  void                   BufferData();
  void                   Render();

private:
  GLuint                 m_vao;
  GLuint                 m_vbo;
  std::vector<Vertex>    m_mesh;
  std::size_t            m_vertexCount;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////

#endif  // VOXELMESH
