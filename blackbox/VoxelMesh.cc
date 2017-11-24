#include "VoxelMesh.hh"


/////////////////////////////////////////////////////////////////////////////////////////////////////
// VoxelMesh Implementation
/////////////////////////////////////////////////////////////////////////////////////////////////////

VoxelMesh::VoxelMesh()
  : m_vao{0},
    m_vbo{0},
    m_vertexCount{0} {

  // Initialize VAO/VBO
  glGenVertexArrays(1, &m_vao);
  glBindVertexArray(m_vao);

  glGenBuffers(1, &m_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);

  glVertexAttribPointer(0, 3, GL_FLOAT,         GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
  glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE,  sizeof(Vertex), (void*)offsetof(Vertex, Color));
  glVertexAttribPointer(2, 2, GL_FLOAT,         GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TxtrCoord));

  glBindVertexArray(0);
}

void VoxelMesh::AddCube(const glm::vec3& p_origin, float p_width) {

  float OX, OY, OZ, AX, AY, AZ;
  OX = p_origin.x * p_width;
  OY = p_origin.y * p_width;
  OZ = p_origin.z * p_width;
  AX = OX + p_width;
  AY = OY + p_width;
  AZ = OZ + p_width;

  VertexPosition FRT_LFT_BTM{OX, OY, OZ};
  VertexPosition FRT_RGT_BTM{AX, OY, OZ};
  VertexPosition FRT_LFT_TOP{OX, AY, OZ};
  VertexPosition FRT_RGT_TOP{AX, AY, OZ};
  VertexPosition BAK_LFT_BTM{OX, OY, AZ};
  VertexPosition BAK_RGT_BTM{AX, OY, AZ};
  VertexPosition BAK_LFT_TOP{OX, AY, AZ};
  VertexPosition BAK_RGT_TOP{AX, AY, AZ};

  AddFace(FRT_LFT_TOP, FRT_LFT_BTM, FRT_RGT_BTM, FRT_RGT_TOP); // Front
  AddFace(BAK_RGT_TOP, BAK_RGT_BTM, BAK_LFT_BTM, BAK_LFT_TOP); // Back
  AddFace(BAK_LFT_TOP, BAK_LFT_BTM, FRT_LFT_BTM, FRT_LFT_TOP); // Left
  AddFace(FRT_RGT_TOP, FRT_RGT_BTM, BAK_RGT_BTM, BAK_RGT_TOP); // Right
  AddFace(FRT_LFT_BTM, BAK_LFT_BTM, BAK_RGT_BTM, FRT_RGT_BTM); // Bottom
  AddFace(BAK_LFT_TOP, FRT_LFT_TOP, FRT_RGT_TOP, BAK_RGT_TOP); // Top
}

void VoxelMesh::AddFace(const VertexPosition& p_v1, const VertexPosition& p_v2,
                        const VertexPosition& p_v3, const VertexPosition& p_v4) {

  static VertexTxtrCoord U0V0{0.0f, 0.0f};
  static VertexTxtrCoord U0V1{0.0f, 1.0f};
  static VertexTxtrCoord U1V0{1.0f, 0.0f};
  static VertexTxtrCoord U1V1{1.0f, 1.0f};

  m_mesh.emplace_back(p_v1, U0V1);
  m_mesh.emplace_back(p_v2, U0V0);
  m_mesh.emplace_back(p_v3, U1V0);
  m_mesh.emplace_back(p_v3, U1V0);
  m_mesh.emplace_back(p_v4, U1V1);
  m_mesh.emplace_back(p_v1, U0V1);
}

void VoxelMesh::BufferData() {

  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBufferData(GL_ARRAY_BUFFER, m_mesh.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW); // Orphan the Buffer
  glBufferSubData(GL_ARRAY_BUFFER, 0, m_mesh.size() * sizeof(Vertex), m_mesh.data());      // Buffer the Data
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  m_vertexCount = m_mesh.size();
  m_mesh.clear();
}

void VoxelMesh::Render() {

  glBindVertexArray(m_vao);
  glDrawArrays(GL_TRIANGLES, 0, m_vertexCount);
  glBindVertexArray(0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
